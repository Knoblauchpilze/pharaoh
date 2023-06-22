
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
  if (!m_buildings.contains(id))
  {
    error("Failed to get building " + std::to_string(id));
  }

  return m_buildings.at(id);
}

auto Map::spawn(const building::Type type, const int x, const int y) -> Index
{
  auto &tile = at(x, y);
  if (tile.type == terrain::Type::WATER)
  {
    warn("Can't build " + building::str(type), m_coords.str(x, y) + " is water");
    return INVALID_INDEX;
  }
  if (tile.isBuilding())
  {
    warn("Can't build " + building::str(type), m_coords.str(x, y) + " already has a building");
    return INVALID_INDEX;
  }
  if (tile.floodable && !building::isBuildableOnFloodablePlain(type))
  {
    warn("Can't build " + building::str(type), m_coords.str(x, y) + " is floodable");
    return INVALID_INDEX;
  }

  tile.buildingId              = m_nextBuildingId;
  auto b                       = newBuilding(type, x, y);
  b.employees                  = building::workforce(type);
  m_buildings[tile.buildingId] = b;
  ++m_nextBuildingId;

  handleBuildingSpawned(b);

  return tile.buildingId;
}

bool Map::demolish(const int x, const int y)
{
  auto &tile = at(x, y);
  if (!tile.isBuilding())
  {
    warn("Nothing to demolish at " + m_coords.str(x, y));
    return false;
  }

  const Building b = m_buildings.at(tile.buildingId);
  if (auto removed = m_buildings.erase(tile.buildingId); removed != 1)
  {
    warn("Removed " + std::to_string(removed) + " building(s) with id "
         + std::to_string(tile.buildingId));
  }

  tile.buildingId = INVALID_INDEX;

  handleBuildingDemolished(b);

  return true;
}

bool Map::isBuildingConnectedToRoad(const Index id) const
{
  if (!m_buildings.contains(id))
  {
    error("Failed to assert building " + std::to_string(id) + " connectivity");
  }

  const auto &b = m_buildings.at(id);

  return m_roadNewtork.isConnectedToRoad(b.x, b.y);
}

auto Map::spawnPointForBuilding(const Index id) const noexcept -> utils::Point2f
{
  if (!m_buildings.contains(id))
  {
    error("Failed to find building " + std::to_string(id) + " spawn point");
  }

  const auto &b = m_buildings.at(id);

  return utils::Point2f{1.0f * b.x, 1.0f * b.y};
}

void Map::process(const BuildingProcess &process)
{
  for (auto &b : m_buildings)
  {
    process(b.first, b.second, *this);
  }
}

auto Map::citizen(const Index id) const -> const Citizen &
{
  if (!m_citizens.contains(id))
  {
    error("Failed to get citizen " + std::to_string(id));
  }

  return m_citizens.at(id);
}

auto Map::spawn(const citizen::Type type, const float x, const float y) -> Index
{
  auto id        = m_nextCitizenId;
  auto c         = newCitizen(type, x, y);
  m_citizens[id] = c;
  ++m_nextCitizenId;

  return id;
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
  spawn(building::Type::BAZAAR, 3, 4);
  spawn(building::Type::FARM_FIG, 4, 3);
  spawn(building::Type::GRANARY, 4, 4);
  spawn(building::Type::HOUSE, 4, 5);
  spawn(building::Type::ROAD, 5, 6);
  spawn(building::Type::RUIN, 5, 7);
}

void Map::handleBuildingSpawned(const Building &b) noexcept
{
  if (b.type == building::Type::ROAD)
  {
    m_roadNewtork.addToNetwork(b.x, b.y);
  }
}

void Map::handleBuildingDemolished(const Building &b) noexcept
{
  if (b.type == building::Type::ROAD)
  {
    m_roadNewtork.removeFromNetwork(b.x, b.y);
  }
}

} // namespace pharaoh
