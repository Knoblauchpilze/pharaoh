
#pragma once

#include <string>

namespace pharaoh {
namespace building {
/// @brief - The type of a building.
enum class Type
{
  RUIN,
  ROAD,
  HOUSE,
  GRANARY,
  FARM_FIG,
  BAZAAR,
};

auto str(const Type t) noexcept -> std::string;

bool isBuildableOnFloodablePlain(const Type t) noexcept;

auto cost(const Type t) noexcept -> int;

} // namespace building

struct Building
{
  building::Type type{building::Type::ROAD};
};

auto newBuilding(const building::Type type) noexcept -> Building;

} // namespace pharaoh
