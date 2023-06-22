
#include "CitizenGenerator.hh"

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

auto citizenFor(const building::Type t) noexcept -> std::optional<citizen::Type>
{
  switch (t)
  {
    case building::Type::HOUSE:
      return {citizen::Type::WALKER};
    case building::Type::GRANARY:
      return {citizen::Type::GRANARY};
    case building::Type::BAZAAR:
      return {citizen::Type::BAZAAR};
    case building::Type::FARM_FIG:
      return {citizen::Type::FARMER};
    default:
      return {};
  }
}

CitizenGenerator::CitizenGenerator()
  : utils::CoreObject("generator")
{
  setService("pharaoh");
}

void CitizenGenerator::generate(Map &city) const noexcept
{
  city.process([this](const Index id, Building &b, Map &m) {
    b.hasRoadAccess = m.isBuildingConnectedToRoad(id);
    const auto p    = m.spawnPointForBuilding(id);
    b.xSpawn        = p.x();
    b.ySpawn        = p.y();
  });

  city.process([this](const Index /*id*/, Building &b, Map &m) {
    const auto citizen = citizenFor(b.type);
    if (!citizen)
    {
      return;
    }

    const auto task = determineTaskFor(b, m);
    if (shouldSpawnFor(b, task, m))
    {
      m.spawn(*citizen, b.xSpawn, b.ySpawn);
    }
  });
}

auto CitizenGenerator::determineTaskFor(const Building &b, const Map & /*m*/) const
  -> std::optional<BuildingTask>
{
  if (!isBuildingWithTask(b.type))
  {
    return {};
  }

  return {};
}

bool CitizenGenerator::shouldSpawnFor(const Building & /*b*/,
                                      const std::optional<BuildingTask> & /*task*/,
                                      const Map & /*m*/) const
{
  return false;
}

} // namespace pharaoh
