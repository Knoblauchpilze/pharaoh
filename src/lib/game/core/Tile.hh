
#pragma once

#include "Index.hh"
#include "Terrain.hh"

namespace pharaoh {

template<typename T>
auto asIndex(const T &val) -> Index
{
  return static_cast<Index>(val);
}

struct Tile
{
  terrain::Type type{terrain::Type::LAND};
  bool floodable{false};
  Index buildingId{INVALID_INDEX};

  bool isBuilding() const noexcept;
};

auto newTile(const terrain::Type type) noexcept -> Tile;
auto newFloodablePlain() noexcept -> Tile;
auto newBuilding(const Index id) noexcept -> Tile;

} // namespace pharaoh
