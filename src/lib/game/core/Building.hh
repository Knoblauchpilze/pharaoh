
#pragma once

#include "Index.hh"
#include <string>
#include <unordered_set>

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
auto workforce(const Type t) noexcept -> int;
auto minimumHousesToGetWorkforce(const Type t) noexcept -> int;
auto maxCitizensFor(const Type t) noexcept -> int;

} // namespace building

struct Building
{
  building::Type type{building::Type::ROAD};
  int employees{0};
  int x;
  int y;

  /// The variables below are updated during each tick of the game.
  bool hasRoadAccess{false};
  float xSpawn;
  float ySpawn;
  int population{0};
  int housesInReach{0};
  std::unordered_set<Index> workers{};
};

auto newBuilding(const building::Type type, const int x, const int y) noexcept -> Building;

} // namespace pharaoh
