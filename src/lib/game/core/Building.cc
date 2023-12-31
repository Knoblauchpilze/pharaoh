
#include "Building.hh"

namespace pharaoh {
namespace building {
auto str(const Type t) noexcept -> std::string
{
  switch (t)
  {
    case Type::ROAD:
      return "road";
    case Type::HOUSE:
      return "house";
    case Type::FARM:
      return "farm";
    default:
      return "unknown";
  }
}

bool isBuildableOnFloodablePlain(const Type t) noexcept
{
  switch (t)
  {
    case Type::ROAD:
    case Type::FARM:
      return true;
    case Type::HOUSE:
    default:
      return false;
  }
}

auto cost(const Type t) noexcept -> int
{
  // https://pharaoh.heavengames.com/buildings/
  switch (t)
  {
    case Type::ROAD:
      return 4;
    case Type::HOUSE:
      return 10;
    case Type::FARM:
      return 40;
    default:
      return 0;
  }
}

auto workforce(const Type t) noexcept -> int
{
  // https://pharaoh.heavengames.com/buildings/
  switch (t)
  {
    case Type::FARM:
      return 10;
    default:
      return 0;
  }
}

bool traversable(const Type t) noexcept
{
  switch (t)
  {
    case Type::ROAD:
      return true;
    default:
      return false;
  }
}

} // namespace building

auto Building::str() const noexcept -> std::string
{
  return building::str(type) + "-" + pos.str();
}

auto newBuilding(const building::Type type, const MapPoint &pos) noexcept -> Building
{
  return Building{.type = type, .pos = pos};
}

} // namespace pharaoh
