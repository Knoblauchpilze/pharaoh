
#include "Map.hh"

namespace pharaoh {
constexpr auto WIDTH  = 10;
constexpr auto HEIGHT = 8;

Map::Map()
  : utils::CoreObject("map")
  , m_coords(WIDTH, HEIGHT)
{
  setService("pharaoh");
  initialize();
}

auto Map::w() const noexcept -> int
{
  return m_coords.w();
}

auto Map::h() const noexcept -> int
{
  return m_coords.h();
}

auto Map::at(const int x, const int y) const -> const Tile &
{
  if (!m_coords.valid(x, y))
  {
    error("Failed to get tile " + m_coords.str(x, y), "Dimensions are " + m_coords.str());
  }

  return m_tiles.at(m_coords.linear(x, y));
}

auto Map::building(const Index id) const -> const Building &
{
  if (id >= asIndex(m_buildings.size()))
  {
    error("Failed to get building " + std::to_string(id),
          "Only " + std::to_string(m_buildings.size()) + " building(s) defined");
  }

  return m_buildings.at(id);
}

auto Map::spawn(const int x, const int y, const building::Type &type) -> Index
{
  auto &tile = at(x, y);
  if (tile.isBuilding())
  {
    warn("Didn't place " + building::toString(type), "Already a building at " + m_coords.str(x, y));
    return INVALID_INDEX;
  }

  tile.buildingId = asIndex(m_buildings.size());
  auto b          = newBuilding(type);
  m_buildings.push_back(b);

  return tile.buildingId;
}

auto Map::at(const int x, const int y) -> Tile &
{
  if (!m_coords.valid(x, y))
  {
    error("Failed to get tile " + m_coords.str(x, y), "Dimensions are " + m_coords.str());
  }

  return m_tiles.at(m_coords.linear(x, y));
}

void Map::initialize()
{
  m_tiles.resize(m_coords.count(), Tile{});

  // Base terrain.
  for (auto y = 0; y < HEIGHT; ++y)
  {
    for (auto x = 0; x < 1; ++x)
    {
      at(x, y) = newTile(terrain::Type::WATER);
    }

    if (y % 2 == 0)
    {
      at(1, y) = newTile(terrain::Type::WATER);
    }
    else
    {
      at(1, y) = newFloodablePlain();
    }

    for (auto x = 2; x < 3; ++x)
    {
      at(x, y) = newFloodablePlain();
    }

    if (y % 2 == 0)
    {
      at(3, y) = newFloodablePlain();
    }
  }

  // Buildings.
  spawn(3, 4, building::Type::BAZAAR);
  spawn(4, 3, building::Type::FARM_FIG);
  spawn(4, 4, building::Type::GRANARY);
  spawn(4, 5, building::Type::HOUSE);
  spawn(5, 6, building::Type::ROAD);
  spawn(5, 7, building::Type::RUIN);
}

} // namespace pharaoh
