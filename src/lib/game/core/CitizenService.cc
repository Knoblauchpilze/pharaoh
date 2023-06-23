
#include "CitizenService.hh"

namespace pharaoh {
bool isBuildingWithTask(const building::Type t) noexcept
{
  switch (t)
  {
    case building::Type::GRANARY:
    case building::Type::BAZAAR:
    case building::Type::FARM_FIG:
      return true;
    default:
      return false;
  }
}

CitizenService::CitizenService()
  : utils::CoreObject("generator")
{
  setService("pharaoh");
}

void CitizenService::generate(Map &city) const noexcept
{
  city.process([this](const Index id, Building &b, Map &m) {
    b.hasRoadAccess = m.isBuildingConnectedToRoad(id);
    const auto p    = m.spawnPointForBuilding(id);
    b.xSpawn        = p.x();
    b.ySpawn        = p.y();
  });

  city.process([this](const Index id, Building &b, Map &m) {
    const auto task = determineTaskFor(b, m);
    if (const auto citizen = shouldSpawnFor(b, task, m))
    {
      m.spawn(*citizen, b.xSpawn, b.ySpawn, {id});
      log("Spawned " + citizen::str(*citizen) + " for " + building::str(b.type) + " at "
          + std::to_string(b.x) + "x" + std::to_string(b.y));
    }
  });
}

auto CitizenService::determineTaskFor(const Building &b, const Map & /*m*/) const noexcept
  -> std::optional<BuildingTask>
{
  if (!isBuildingWithTask(b.type))
  {
    return {};
  }

  return {};
}

auto CitizenService::shouldSpawnFor(const Building &b,
                                    const std::optional<BuildingTask> & /*task*/,
                                    const Map & /*m*/) const noexcept
  -> std::optional<citizen::Type>
{
  if (static_cast<int>(b.workers.size()) >= building::maxCitizensFor(b.type))
  {
    return {};
  }

  if (needsLaborSeeker(b))
  {
    return {citizen::Type::LABOR_SEEKER};
  }

  return {};
}

bool CitizenService::needsLaborSeeker(const Building &b) const noexcept
{
  return b.housesInReach < building::minimumHousesToGetWorkforce(b.type);
}

} // namespace pharaoh
