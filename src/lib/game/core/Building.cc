
#include "Building.hh"

namespace pharaoh {
namespace building {
auto toString(const Type &t) noexcept -> std::string
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
} // namespace building

auto newBuilding(const building::Type type) noexcept -> Building
{
  return Building{.type = type};
}

} // namespace pharaoh