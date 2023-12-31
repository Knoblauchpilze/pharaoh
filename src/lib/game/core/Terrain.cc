
#include "Terrain.hh"

namespace pharaoh::terrain {

auto str(const Type t) noexcept -> std::string
{
  switch (t)
  {
    case Type::LAND:
      return "land";
    case Type::WATER:
      return "water";
    default:
      return "unknown";
  }
}

} // namespace pharaoh::terrain
