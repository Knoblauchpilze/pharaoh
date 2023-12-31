
#include "App.hh"

namespace pge {
const auto CURSOR_COLOR = olc::Pixel{255, 255, 0, alpha::SemiOpaque};

constexpr auto TEXTURE_PIXELS_SIZE = 64;

inline auto spriteIdFromTerrain(const pharaoh::Tile &tile) noexcept -> int
{
  switch (tile.type)
  {
    case pharaoh::terrain::Type::WATER:
      return 0;
    case pharaoh::terrain::Type::LAND:
      return tile.floodable ? 2 : 1;
    default:
      return 1;
  }
}

inline auto spriteIdFromBuilding(const pharaoh::Building &b) noexcept -> olc::vi2d
{
  switch (b.type)
  {
    case pharaoh::building::Type::ROAD:
      return olc::vi2d{1, 0};
    case pharaoh::building::Type::HOUSE:
      return olc::vi2d{0, b.population > 0 ? 1 : 0};
    case pharaoh::building::Type::FARM:
      return olc::vi2d{2, b.workforce > 0 ? 1 : 0};
    default:
      return olc::vi2d{1, 1};
  }
}

inline auto spriteIdFromCitizen(const pharaoh::citizen::Type &type) noexcept -> int
{
  switch (type)
  {
    case pharaoh::citizen::Type::IMMIGRANT:
    default:
      return 0;
  }
}

App::App(const AppDesc &desc)
  : PGEApp(desc)
  , m_game(nullptr)
  , m_state(nullptr)
  , m_menus()
  , m_packs(std::make_shared<sprites::TexturePack>())
{}

bool App::onFrame(float fElapsed)
{
  // Handle case where no game is defined.
  if (m_game == nullptr)
  {
    return false;
  }

  if (!m_game->step(fElapsed))
  {
    info("This is game over");
  }

  return m_game->terminated();
}

void App::onInputs(const controls::State &c, const CoordinateFrame &cf)
{
  // Handle case where no game is defined.
  if (m_game == nullptr)
  {
    return;
  }

  // Handle menus update and process the
  // corresponding actions.
  std::vector<ActionShPtr> actions;
  bool relevant = false;

  for (unsigned id = 0u; id < m_menus.size(); ++id)
  {
    menu::InputHandle ih = m_menus[id]->processUserInput(c, actions);
    relevant             = (relevant || ih.relevant);
  }

  if (m_state != nullptr)
  {
    menu::InputHandle ih = m_state->processUserInput(c, actions);
    relevant             = (relevant || ih.relevant);
  }

  for (unsigned id = 0u; id < actions.size(); ++id)
  {
    actions[id]->apply(*m_game);
  }

  bool lClick = (c.buttons[controls::mouse::Left] == controls::ButtonState::Released);
  if (lClick && !relevant)
  {
    olc::vf2d it;
    olc::vi2d tp = cf.pixelsToTilesAndIntra(olc::vi2d(c.mPosX, c.mPosY), &it);

    m_game->performAction(tp.x + it.x, tp.y + it.y);
  }

  if (c.keys[controls::keys::P])
  {
    m_game->togglePause();
  }
}

void App::loadData()
{
  // Create the game and its state.
  m_game = std::make_shared<Game>();
}

void App::loadResources()
{
  // Assign a specific tint to the regular drawing layer so that we have a built
  // in transparency.
  // We can't do it directly when drawing in the rendering function because as the
  // whole layer will be drawn as one quad in opengl with an opaque alpha, we will
  // lose this info.
  // This means that everything is indeed transparent but that's the only way for
  // now to achieve it.
  setLayerTint(Layer::Draw, olc::Pixel(255, 255, 255, alpha::SemiOpaque));

  sprites::PackDesc packTerrain;
  packTerrain.file   = "data/tiles/terrain.png";
  packTerrain.sSize  = {TEXTURE_PIXELS_SIZE, TEXTURE_PIXELS_SIZE};
  packTerrain.layout = {3, 1};
  m_terrainPackId    = m_packs->registerPack(packTerrain);

  sprites::PackDesc packBuilding;
  packBuilding.file   = "data/tiles/building.png";
  packBuilding.sSize  = {TEXTURE_PIXELS_SIZE, TEXTURE_PIXELS_SIZE};
  packBuilding.layout = {3, 2};
  m_buildingPackId    = m_packs->registerPack(packBuilding);

  sprites::PackDesc packCitizen;
  packCitizen.file   = "data/tiles/citizen.png";
  packCitizen.sSize  = {TEXTURE_PIXELS_SIZE, TEXTURE_PIXELS_SIZE};
  packCitizen.layout = {2, 1};
  m_citizenPackId    = m_packs->registerPack(packCitizen);
}

void App::loadMenuResources()
{
  // Generate the game state.
  m_state = std::make_shared<GameState>(olc::vi2d(ScreenWidth(), ScreenHeight()), Screen::Game);

  m_menus = m_game->generateMenus(ScreenWidth(), ScreenHeight());
  m_game->togglePause();
}

void App::cleanResources()
{
  if (m_packs != nullptr)
  {
    m_packs.reset();
  }
}

void App::cleanMenuResources()
{
  m_menus.clear();
}

void App::drawDecal(const RenderDesc &res)
{
  // Clear rendering target.
  SetPixelMode(olc::Pixel::ALPHA);
  Clear(olc::VERY_DARK_GREY);

  // In case we're not in the game screen, do nothing.
  if (m_state->getScreen() != Screen::Game)
  {
    SetPixelMode(olc::Pixel::NORMAL);
    return;
  }

  renderMap(res.cf);
  if (hasCursor())
  {
    renderCursor(res);
  }

  SetPixelMode(olc::Pixel::NORMAL);
}

void App::draw(const RenderDesc & /*res*/)
{
  // Clear rendering target.
  SetPixelMode(olc::Pixel::ALPHA);
  Clear(olc::Pixel(255, 255, 255, alpha::Transparent));

  // In case we're not in game mode, just render the state.
  if (m_state->getScreen() != Screen::Game)
  {
    m_state->render(this);
    SetPixelMode(olc::Pixel::NORMAL);
    return;
  }

  SetPixelMode(olc::Pixel::NORMAL);
}

void App::drawUI(const RenderDesc & /*res*/)
{
  // Clear rendering target.
  SetPixelMode(olc::Pixel::ALPHA);
  Clear(olc::Pixel(255, 255, 255, alpha::Transparent));

  // In case we're not in game mode, just render the state.
  if (m_state->getScreen() != Screen::Game)
  {
    m_state->render(this);
    SetPixelMode(olc::Pixel::NORMAL);
    return;
  }

  // Render the game menus.
  for (unsigned id = 0u; id < m_menus.size(); ++id)
  {
    m_menus[id]->render(this);
  }

  SetPixelMode(olc::Pixel::NORMAL);
}

void App::drawDebug(const RenderDesc &res)
{
  // Clear rendering target.
  SetPixelMode(olc::Pixel::ALPHA);
  Clear(olc::Pixel(255, 255, 255, alpha::Transparent));

  // In case we're not in game mode, just render the state.
  if (m_state->getScreen() != Screen::Game)
  {
    m_state->render(this);
    SetPixelMode(olc::Pixel::NORMAL);
    return;
  }

  // Draw cursor's position.
  olc::vi2d mp = GetMousePos();
  olc::vf2d it;
  olc::vi2d mtp = res.cf.pixelsToTilesAndIntra(mp, &it);

  int h       = GetDrawTargetHeight();
  int dOffset = 15;
  DrawString(olc::vi2d(0, h / 2), "Mouse coords      : " + mp.str(), olc::CYAN);
  DrawString(olc::vi2d(0, h / 2 + 1 * dOffset), "World cell coords : " + mtp.str(), olc::CYAN);
  DrawString(olc::vi2d(0, h / 2 + 2 * dOffset), "Intra cell        : " + it.str(), olc::CYAN);

  SetPixelMode(olc::Pixel::NORMAL);
}

inline void App::renderCursor(const RenderDesc &res)
{
  olc::vf2d it;
  const auto mouseTilePosition = res.cf.pixelsToTilesAndIntra(GetMousePos(), &it);

  SpriteDesc s;
  s.radius      = 1.0f;
  s.x           = mouseTilePosition.x;
  s.y           = mouseTilePosition.y;
  s.sprite.tint = CURSOR_COLOR;
  drawWarpedRect(s, res.cf);
}

inline void App::drawSprite(const SpriteDesc &t, const CoordinateFrame &cf)
{
  olc::vf2d p = cf.tilesToPixels(t.x, t.y);

  m_packs->draw(this, t.sprite, p, t.radius * cf.tileSize());
}

inline void App::drawWarpedSprite(const SpriteDesc &t, const CoordinateFrame &cf)
{
  auto p0 = cf.tilesToPixels(t.x, t.y + t.radius);
  auto p1 = cf.tilesToPixels(t.x, t.y);
  auto p2 = cf.tilesToPixels(t.x + t.radius, t.y);
  auto p3 = cf.tilesToPixels(t.x + t.radius, t.y + t.radius);

  auto p = std::array<olc::vf2d, 4>{p0, p1, p2, p3};
  m_packs->draw(this, t.sprite, p);
}

inline void App::drawRect(const SpriteDesc &t, const CoordinateFrame &cf)
{
  olc::vf2d p = cf.tilesToPixels(t.x, t.y);
  FillRectDecal(p, t.radius * cf.tileSize(), t.sprite.tint);
}

inline void App::drawWarpedRect(const SpriteDesc &t, const CoordinateFrame &cf)
{
  auto p0 = cf.tilesToPixels(t.x, t.y + t.radius);
  auto p1 = cf.tilesToPixels(t.x, t.y);
  auto p2 = cf.tilesToPixels(t.x + t.radius, t.y);
  auto p3 = cf.tilesToPixels(t.x + t.radius, t.y + t.radius);

  // See: FillRectDecal(const olc::vf2d& pos, const olc::vf2d& size, const olc::Pixel col)
  // in the pixel game engine file.
  auto p = std::array<olc::vf2d, 4>{p0, p1, p2, p3};
  std::array<olc::vf2d, 4> uvs;
  uvs.fill({0, 0});

  std::array<olc::Pixel, 4> colors;
  colors.fill(t.sprite.tint);

  DrawExplicitDecal(nullptr, p.data(), uvs.data(), colors.data());
}

inline void App::renderMap(const CoordinateFrame &cf)
{
  renderTerrain(cf);
  renderBuildings(cf);
  renderCitizens(cf);
}

inline void App::renderTerrain(const CoordinateFrame &cf)
{
  const auto renderTile =
    [this, &cf](const pharaoh::MapPoint &pos, const pharaoh::Tile &t, const pharaoh::Map & /*m*/) {
      SpriteDesc s;
      s.radius      = 1.0f;
      s.sprite.pack = m_terrainPackId;
      s.sprite.tint = olc::WHITE;

      s.x = pos.x;
      s.y = pos.y;

      s.sprite.sprite.x = spriteIdFromTerrain(t);
      s.sprite.sprite.y = 0;

      drawWarpedSprite(s, cf);
    };

  auto &city = m_game->map();
  city.process(renderTile);
}

inline void App::renderBuildings(const CoordinateFrame &cf)
{
  const auto renderBuilding = [this, &cf](const pharaoh::Index /*id*/,
                                          const pharaoh::Building &b,
                                          const pharaoh::Map & /*m*/) {
    SpriteDesc s;
    s.radius      = 1.0f;
    s.sprite.pack = m_buildingPackId;
    s.sprite.tint = olc::WHITE;

    s.x = b.pos.x;
    s.y = b.pos.y;

    const auto sp     = spriteIdFromBuilding(b);
    s.sprite.sprite.x = sp.x;
    s.sprite.sprite.y = sp.y;

    drawWarpedSprite(s, cf);
  };

  auto &city = m_game->map();
  city.process(renderBuilding);
}

inline void App::renderCitizens(const CoordinateFrame &cf)
{
  const auto renderCitizen = [this, &cf](const pharaoh::Index /*id*/,
                                         const pharaoh::Citizen &c,
                                         const pharaoh::Map & /*m*/) {
    SpriteDesc s;
    s.radius      = 1.0f;
    s.sprite.pack = m_citizenPackId;
    s.sprite.tint = olc::WHITE;

    s.x = c.pos.x;
    s.y = c.pos.y;

    s.sprite.sprite.x = spriteIdFromCitizen(c.type);
    s.sprite.sprite.y = 0;

    drawWarpedSprite(s, cf);
  };

  auto &city = m_game->map();
  city.process(renderCitizen);
}

} // namespace pge
