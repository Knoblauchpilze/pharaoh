
#include "Tile.hh"

namespace pharaoh {

bool Tile::isBuilding() const noexcept
{
  return buildingId != INVALID_INDEX;
}

auto newTile(const terrain::Type type) noexcept -> Tile
{
  return Tile{.type = type};
}

auto newFloodablePlain() noexcept -> Tile
{
  auto tile      = newTile(terrain::Type::LAND);
  tile.floodable = true;
  return tile;
}

auto newBuilding(const Index &id) noexcept -> Tile
{
  auto tile       = newTile(terrain::Type::LAND);
  tile.buildingId = id;

  return tile;
}

} // namespace pharaoh
