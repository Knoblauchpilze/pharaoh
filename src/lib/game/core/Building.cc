
#include "Building.hh"

namespace pharaoh {
namespace building {
auto str(const Type t) noexcept -> std::string
{
  switch (t)
  {
    case Type::RUIN:
      return "ruin";
    case Type::ROAD:
      return "road";
    case Type::HOUSE:
      return "house";
    case Type::GRANARY:
      return "granary";
    case Type::FARM_FIG:
      return "fig_farm";
    case Type::BAZAAR:
      return "bazaar";
    default:
      return "unknown";
  }
}

bool isBuildableOnFloodablePlain(const Type t) noexcept
{
  switch (t)
  {
    case Type::FARM_FIG:
      return true;
    case Type::RUIN:
    case Type::ROAD:
    case Type::HOUSE:
    case Type::GRANARY:
    case Type::BAZAAR:
    default:
      return false;
  }
}

auto cost(const Type t) noexcept -> int
{
  // http://www.drislink.com/slink/pharaoh/pharaoh1.htm
  // https://pharaoh.heavengames.com/buildings/
  switch (t)
  {
    case Type::FARM_FIG:
      return 40;
    case Type::ROAD:
      return 4;
    case Type::HOUSE:
      return 10;
    case Type::GRANARY:
      return 250;
    case Type::BAZAAR:
      return 40;
    case Type::RUIN:
    default:
      return 0;
  }
}

auto workforce(const Type t) noexcept -> int
{
  // https://pharaoh.heavengames.com/buildings/
  switch (t)
  {
    case Type::FARM_FIG:
      return 10;
    case Type::GRANARY:
      return 12;
    case Type::BAZAAR:
      return 5;
    case Type::RUIN:
    case Type::ROAD:
    case Type::HOUSE:
    default:
      return 0;
  }
}

auto minimumHousesToGetWorkforce(const Type t) noexcept -> int
{
  switch (t)
  {
    case Type::GRANARY:
    case Type::FARM_FIG:
    case Type::BAZAAR:
      return 1;
    default:
      return 0;
  }
}

auto maxCitizensFor(const Type /*t*/) noexcept -> int
{
  return 1;
}

} // namespace building

auto newBuilding(const building::Type type, const int x, const int y) noexcept -> Building
{
  return Building{.type = type, .x = x, .y = y, .xSpawn = 1.0f * x, .ySpawn = 1.0f * y};
}

} // namespace pharaoh
