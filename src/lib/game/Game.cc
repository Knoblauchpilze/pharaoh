
#include "Game.hh"
#include "Menu.hh"
#include <cxxabi.h>

namespace pge {
constexpr auto DEFAULT_BOARD_DIMS                 = 32;
constexpr auto TOP_BAR_HEIGHT_IN_PIXELS           = 30;
constexpr auto CONSTRUCTION_MENU_WIDTH_IN_PIXELS  = 130;
constexpr auto CONSTRUCTION_MENU_HEIGHT_IN_PIXELS = 400;
constexpr auto STATUS_BAR_WIDTH_IN_PIXELS         = 80;
constexpr auto STATUS_BAR_HEIGHT_IN_PIXELS        = 30;

constexpr auto DEFAULT_GAME_FINISHED_ALERT_DURATION_IN_MS = 3000;
constexpr auto CALENDAR_UPDATE_IN_MS                      = 1000;

namespace {
auto generateMenu(const olc::vi2d &pos,
                  const olc::vi2d &size,
                  const std::string &text,
                  const std::string &name,
                  bool clickable                 = false,
                  const pge::menu::Layout layout = pge::menu::Layout::Horizontal,
                  olc::Pixel bgColor             = olc::VERY_DARK_GREEN) -> pge::MenuShPtr
{
  pge::menu::MenuContentDesc fd = pge::menu::newMenuContent(text, "", size);
  const auto hsl                = RGBToHSL(bgColor);
  fd.color                      = hsl.b > 127 ? olc::BLACK : olc::WHITE;
  fd.hColor                     = modulate(fd.color, 0.5f);

  fd.align = pge::menu::Alignment::Center;

  return std::make_shared<pge::Menu>(pos,
                                     size,
                                     name,
                                     pge::menu::newColoredBackground(bgColor),
                                     fd,
                                     layout,
                                     clickable,
                                     false);
}

} // namespace

Game::Game()
  : utils::CoreObject("game")
  , m_state(State{
      true,  // paused
      true,  // disabled
      false, // terminated
    })
{
  setService("game");
}

Game::~Game() {}

std::vector<MenuShPtr> Game::generateMenus(float width, float height)
{
  std::vector<MenuShPtr> out;

  auto menus = generateTopBar(width, height);
  out.insert(out.end(), menus.begin(), menus.end());

  menus = generateConstructionMenu(width, height);
  out.insert(out.end(), menus.begin(), menus.end());

  menus = generateStatusBar(width, height);
  out.insert(out.end(), menus.begin(), menus.end());

  return out;
}

void Game::performAction(float x, float y)
{
  // Only handle actions when the game is not disabled.
  if (m_state.disabled)
  {
    log("Ignoring action while menu is disabled");
    return;
  }

  if (!m_gameState.action.has_value())
  {
    return;
  }

  if (m_gameState.action == game::Action::DEMOLISH)
  {
    m_scenario.demolish(x, y);
    return;
  }
  if (m_gameState.action == game::Action::BUILD)
  {
    m_scenario.spawn(*m_gameState.building, x, y);
    return;
  }
}

bool Game::step(float tDelta)
{
  // When the game is paused it is not over yet.
  if (m_state.paused)
  {
    return true;
  }

  if (m_gameState.time.step(tDelta))
  {
    m_scenario.step();
  }

  updateUI();

  return true;
}

void Game::togglePause()
{
  if (m_state.paused)
  {
    resume();
  }
  else
  {
    pause();
  }

  enable(!m_state.paused);
}

void Game::pause()
{
  // Do nothing in case the game is already paused.
  if (m_state.paused)
  {
    return;
  }

  info("Game is now paused");
  m_state.paused = true;
  m_menus.status->setText("paused");
}

void Game::resume()
{
  // Do nothing in case the game is already running.
  if (!m_state.paused)
  {
    return;
  }

  info("Game is now resumed");
  m_state.paused = false;
  m_menus.status->setText("play");
}

auto Game::map() noexcept -> pharaoh::Map &
{
  return m_scenario.map();
}

void Game::registerAction(const game::Action action,
                          const std::optional<pharaoh::building::Type> &building) noexcept
{
  if (m_state.paused)
  {
    warn("Ignoring action request, game is paused");
    return;
  }

  m_gameState.action   = action;
  m_gameState.building = building;
}

void Game::enable(bool enable)
{
  m_state.disabled = !enable;

  if (m_state.disabled)
  {
    log("Disabled game UI", utils::Level::Verbose);
  }
  else
  {
    log("Enabled game UI", utils::Level::Verbose);
  }
}

void Game::updateUI()
{
  m_menus.gold->setText(std::to_string(m_scenario.gold()));
  m_menus.calendar->setText(m_scenario.date().str());
}

auto Game::generateTopBar(float width, float /*height*/) -> std::vector<MenuShPtr>
{
  auto iWidth = static_cast<int>(width);
  auto topBar = generateMenu({}, {iWidth, TOP_BAR_HEIGHT_IN_PIXELS}, "", "top_bar");

  m_menus.name = generateMenu({}, {iWidth, TOP_BAR_HEIGHT_IN_PIXELS}, m_scenario.name(), "name");
  topBar->addMenu(m_menus.name);

  m_menus.gold = generateMenu({},
                              {iWidth, TOP_BAR_HEIGHT_IN_PIXELS},
                              std::to_string(m_scenario.gold()),
                              "gold");
  topBar->addMenu(m_menus.gold);

  m_menus.calendar = generateMenu({},
                                  {iWidth, TOP_BAR_HEIGHT_IN_PIXELS},
                                  m_scenario.date().str(),
                                  "calendar");
  topBar->addMenu(m_menus.calendar);

  std::vector<MenuShPtr> out;
  out.push_back(topBar);

  return out;
}

auto Game::generateConstructionMenu(float width, float height) -> std::vector<MenuShPtr>
{
  auto iWidth = static_cast<int>(width);
  auto y      = TOP_BAR_HEIGHT_IN_PIXELS
           + static_cast<int>((height - CONSTRUCTION_MENU_HEIGHT_IN_PIXELS
                               - TOP_BAR_HEIGHT_IN_PIXELS - STATUS_BAR_HEIGHT_IN_PIXELS)
                              / 2.0f);
  auto construction = generateMenu({iWidth - CONSTRUCTION_MENU_WIDTH_IN_PIXELS, y},
                                   {CONSTRUCTION_MENU_WIDTH_IN_PIXELS,
                                    CONSTRUCTION_MENU_HEIGHT_IN_PIXELS},
                                   "",
                                   "construction",
                                   false,
                                   pge::menu::Layout::Vertical);

  olc::vi2d dummySize{10, 10};
  auto menu = generateMenu({}, dummySize, "Road", "road", true);
  menu->setSimpleAction(
    [](Game &g) { g.registerAction(game::Action::BUILD, {pharaoh::building::Type::ROAD}); });
  construction->addMenu(menu);

  menu = generateMenu({}, dummySize, "House", "house", true);
  menu->setSimpleAction(
    [](Game &g) { g.registerAction(game::Action::BUILD, {pharaoh::building::Type::HOUSE}); });
  construction->addMenu(menu);

  menu = generateMenu({},
                      dummySize,
                      "Demolish",
                      "demolish",
                      true,
                      pge::menu::Layout::Horizontal,
                      olc::VERY_DARK_RED);
  menu->setSimpleAction([](Game &g) { g.registerAction(game::Action::DEMOLISH, {}); });
  construction->addMenu(menu);

  std::vector<MenuShPtr> out;
  out.push_back(construction);

  return out;
}

auto Game::generateStatusBar(float width, float height) -> std::vector<MenuShPtr>
{
  auto iWidth    = static_cast<int>(width);
  auto iHeight   = static_cast<int>(height);
  m_menus.status = generateMenu({iWidth - STATUS_BAR_WIDTH_IN_PIXELS,
                                 iHeight - STATUS_BAR_HEIGHT_IN_PIXELS},
                                {STATUS_BAR_WIDTH_IN_PIXELS, STATUS_BAR_HEIGHT_IN_PIXELS},
                                "paused",
                                "status_bar");

  std::vector<MenuShPtr> out;
  out.push_back(m_menus.status);

  return out;
}

bool Game::TimedMenu::update(bool active) noexcept
{
  // In case the menu should be active.
  if (active)
  {
    if (!wasActive)
    {
      // Make it active if it's the first time that
      // we detect that it should be active.
      date      = utils::now();
      wasActive = true;
      menu->setVisible(true);
    }
    else if (utils::now() > date + utils::toMilliseconds(duration))
    {
      // Deactivate the menu in case it's been active
      // for too long.
      menu->setVisible(false);
    }
    else
    {
      // Update the alpha value in case it's active
      // for not long enough.
      olc::Pixel c = menu->getBackgroundColor();

      float d = utils::diffInMs(date, utils::now()) / duration;
      c.a     = static_cast<uint8_t>(std::clamp((1.0f - d) * pge::alpha::Opaque, 0.0f, 255.0f));
      menu->setBackground(pge::menu::newColoredBackground(c));
    }
  }
  // Or if the menu shouldn't be active anymore and
  // it's the first time we detect that.
  else if (wasActive)
  {
    // Deactivate the menu.
    menu->setVisible(false);
    wasActive = false;
  }

  return menu->visible();
}

} // namespace pge
