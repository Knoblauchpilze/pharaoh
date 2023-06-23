
#include "Scenario.hh"
#include "CitizenService.hh"
#include <maths_utils/Point2.hh>

namespace pharaoh {
constexpr auto ALLOWED_OVERDRAFT = -150;
enum Tick
{
  CITIZEN_GENERATION_TICK = 0,
};

Scenario::Scenario()
  : utils::CoreObject("scenario")
{
  setService("pharaoh");
}

auto Scenario::name() const noexcept -> std::string
{
  return m_name;
}

auto Scenario::map() const noexcept -> const Map &
{
  return m_map;
}

auto Scenario::date() const noexcept -> const Calendar &
{
  return m_date;
}

auto Scenario::gold() const noexcept -> int
{
  return m_gold;
}

void Scenario::step()
{
  info("Processing tick " + m_date.str());
  CitizenService cg{};

  switch (m_date.t())
  {
    case CITIZEN_GENERATION_TICK:
      cg.generate(m_map);
      break;
    default:
      break;
  }

  m_date.tick();
}

void Scenario::spawn(const building::Type type, float x, float y)
{
  const auto cost           = building::cost(type);
  const auto plannedBalance = m_gold - cost;
  if (plannedBalance < ALLOWED_OVERDRAFT)
  {
    warn("Can't spawn " + building::str(type),
         "Balance would reach " + std::to_string(plannedBalance) + ", less than allowed "
           + std::to_string(ALLOWED_OVERDRAFT));
    return;
  }

  utils::Point2i pos{static_cast<int>(x), static_cast<int>(y)};
  auto id = m_map.spawn(type, pos.x(), pos.y());
  if (id != INVALID_INDEX)
  {
    info("Used " + std::to_string(cost) + " for " + building::str(type));

    m_gold -= cost;
  }
}

void Scenario::demolish(float x, float y)
{
  utils::Point2i pos{static_cast<int>(x), static_cast<int>(y)};
  if (m_map.demolish(pos.x(), pos.y()))
  {
    log("Demolished at " + pos.toString());
  }
}

} // namespace pharaoh