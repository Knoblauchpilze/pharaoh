
#pragma once

#include <string>

namespace pharaoh {

struct MapPoint
{
  int x;
  int y;

  auto str() const noexcept -> std::string
  {
    return std::to_string(x) + "x" + std::to_string(y);
  }
};

} // namespace pharaoh
