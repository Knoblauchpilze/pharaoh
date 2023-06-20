
#pragma once

#include <string>

namespace pharaoh::terrain {

/// @brief - The type of a tile of terrain.
enum class Type
{
  LAND,
  WATER,
};

auto toString(const Type &t) noexcept -> std::string;

} // namespace pharaoh::terrain
