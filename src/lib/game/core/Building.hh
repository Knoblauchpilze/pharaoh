
#pragma once

#include "Index.hh"
#include "MapPoint.hh"
#include <string>
#include <unordered_set>

namespace pharaoh {
namespace building {
/// @brief - The type of a building.
enum class Type
{
  ROAD,
  HOUSE,
};

auto str(const Type t) noexcept -> std::string;

bool isBuildableOnFloodablePlain(const Type t) noexcept;
auto cost(const Type t) noexcept -> int;

} // namespace building

struct Building
{
  building::Type type{building::Type::ROAD};
  MapPoint pos;

  /// The variables below are updated during each tick of the game.
  int population{0};

  auto str() const noexcept -> std::string;
};

auto newBuilding(const building::Type type, const MapPoint &pos) noexcept -> Building;

} // namespace pharaoh
