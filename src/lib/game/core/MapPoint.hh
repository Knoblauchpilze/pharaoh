
#pragma once

#include <string>

namespace pharaoh {

template<typename Coordinate>
struct MapPointGeneric
{
  Coordinate x;
  Coordinate y;

  auto str() const noexcept -> std::string
  {
    return std::to_string(x) + "x" + std::to_string(y);
  }
};

using MapPoint  = MapPointGeneric<int>;
using MapPointf = MapPointGeneric<float>;

} // namespace pharaoh
