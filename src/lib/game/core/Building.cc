
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
      return "fig farm";
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
} // namespace building

auto newBuilding(const building::Type type) noexcept -> Building
{
  return Building{.type = type};
}

} // namespace pharaoh
