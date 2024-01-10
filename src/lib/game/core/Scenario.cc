
#include "Scenario.hh"
#include "Citizens.hh"
#include "Figures.hh"
#include "Migrants.hh"
#include <maths_utils/Point2.hh>

namespace pharaoh {
constexpr auto ALLOWED_OVERDRAFT = -150;
enum Tick
{
  TICK_MIGRANT_UPDATE   = 0, // 23
  TICK_CITIZEN_GENERATE = 1, // 31
};

Scenario::Scenario()
  : utils::CoreObject("scenario")
{
  setService("pharaoh");
  initializeServices();
}

auto Scenario::name() const noexcept -> std::string
{
  return m_name;
}

auto Scenario::map() noexcept -> Map &
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

  const auto service = m_services.find(m_date.t());
  if (service == m_services.end())
  {
    info("No service for tick " + std::to_string(m_date.t()));
  }
  else
  {
    service->second->run(m_map);
  }

  simulateCitizens();

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

  MapPoint pos{static_cast<int>(x), static_cast<int>(y)};
  auto id = m_map.spawn(type, pos, {});
  if (id != INVALID_INDEX)
  {
    m_gold -= cost;
    info("Used " + std::to_string(cost) + " for " + building::str(type));
  }
}

void Scenario::demolish(float x, float y)
{
  MapPoint pos{static_cast<int>(x), static_cast<int>(y)};
  if (m_map.demolish(pos))
  {
    debug("Demolished at " + pos.str());
  }
}

void Scenario::initializeServices()
{
  m_services[TICK_MIGRANT_UPDATE]   = std::make_unique<services::Migrants>();
  m_services[TICK_CITIZEN_GENERATE] = std::make_unique<services::Figures>();
}

namespace {
auto removeDeadCitizens(Map &city) -> int
{
  std::vector<Index> citizensToRemove;
  city.process([&citizensToRemove](const Index id, Citizen &c, const Map & /*city*/) {
    if (c.state == citizen::State::DEAD)
    {
      citizensToRemove.push_back(id);
    }
  });

  for (const auto &id : citizensToRemove)
  {
    city.kill(id);
  }

  return citizensToRemove.size();
}
} // namespace

void Scenario::simulateCitizens() noexcept
{
  services::Citizens citizens;
  citizens.run(m_map);

  if (const auto removed = removeDeadCitizens(m_map); removed > 0)
  {
    debug("Cleaned " + std::to_string(removed) + " citizen(s)");
  }
}

} // namespace pharaoh
