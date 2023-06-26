
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

bool Map::valid(const MapPoint &pos) const noexcept
{
  return m_coords.valid(pos);
}

auto Map::at(const MapPoint &pos) const -> const Tile &
{
  if (!m_coords.valid(pos))
  {
    error("Failed to get tile " + pos.str(), "Dimensions are " + m_coords.str());
  }

  return m_tiles.at(m_coords.linear(pos));
}

bool Map::existsBuilding(const Index id) const noexcept
{
  return m_buildings.contains(id);
}

auto Map::building(const Index id) const -> const Building &
{
  if (!existsBuilding(id))
  {
    error("Failed to get building " + std::to_string(id));
  }

  return m_buildings.at(id);
}

auto Map::spawn(const building::Type type,
                const MapPoint &pos,
                const std::optional<BuildingInit> &init) -> Index
{
  auto &tile = at(pos);
  if (tile.type == terrain::Type::WATER)
  {
    warn("Can't build " + building::str(type), pos.str() + " is water");
    return INVALID_INDEX;
  }
  if (tile.isBuilding())
  {
    warn("Can't build " + building::str(type), pos.str() + " already has a building");
    return INVALID_INDEX;
  }
  if (tile.floodable && !building::isBuildableOnFloodablePlain(type))
  {
    warn("Can't build " + building::str(type), pos.str() + " is floodable");
    return INVALID_INDEX;
  }

  tile.buildingId = m_nextBuildingId;
  auto b          = newBuilding(type, pos);
  if (init)
  {
    (*init)(b);
  }
  m_buildings[tile.buildingId] = b;
  ++m_nextBuildingId;

  handleBuildingSpawned(b);

  return tile.buildingId;
}

bool Map::demolish(const MapPoint &pos)
{
  auto &tile = at(pos);
  if (!tile.isBuilding() || !existsBuilding(tile.buildingId))
  {
    warn("Nothing to demolish at " + pos.str());
    return false;
  }

  const Building b = building(tile.buildingId);
  if (const auto removed = m_buildings.erase(tile.buildingId); removed != 1)
  {
    warn("Removed " + std::to_string(removed) + " building(s) with id "
         + std::to_string(tile.buildingId));
  }

  tile.buildingId = INVALID_INDEX;

  handleBuildingDemolished(b);

  return true;
}

bool Map::existsCitizen(const Index id) const noexcept
{
  return m_citizens.contains(id);
}

auto Map::citizen(const Index id) const -> const Citizen &
{
  if (!existsCitizen(id))
  {
    error("Failed to get citizen " + std::to_string(id));
  }

  return m_citizens.at(id);
}

auto Map::spawn(const citizen::Type type,
                const MapPointf &pos,
                const std::optional<Index> &homeBuilding,
                const std::optional<CitizenInit> &init) -> Index
{
  auto id        = m_nextCitizenId;
  auto c         = newCitizen(type, pos);
  c.homeBuilding = homeBuilding;
  if (homeBuilding)
  {
    if (!existsBuilding(*homeBuilding))
    {
      error("Failed to spawn " + c.str(), "Invalid home building " + std::to_string(*homeBuilding));
    }
    auto &b = m_buildings.at(*homeBuilding);
    b.citizens.insert(id);
  }
  if (init)
  {
    (*init)(c);
  }
  m_citizens[id] = c;
  ++m_nextCitizenId;

  return id;
}

bool Map::kill(const Index id)
{
  if (!existsCitizen(id))
  {
    warn("No citizen found with id " + std::to_string(id));
    return false;
  }

  const Citizen c = citizen(id);
  if (const auto removed = m_citizens.erase(id); removed != 1)
  {
    warn("Removed " + std::to_string(removed) + " citizen(s) with id " + std::to_string(id));
  }

  auto count = 0;
  process([&id, &count](const Index /*id*/, Building &b, const Map & /*city*/) {
    count += b.citizens.erase(id);
  });
  log("Removed citizen " + c.str() + " from " + std::to_string(count) + " building(s)");

  return true;
}

auto Map::entryPoint() const noexcept -> MapPoint
{
  return m_entryPoint;
}

auto Map::exitPoint() const noexcept -> MapPoint
{
  return m_exitPoint;
}

void Map::process(const TileProcess &process)
{
  for (auto id = 0u; id < m_tiles.size(); ++id)
  {
    process(m_coords.to2d(id), m_tiles[id], *this);
  }
}

void Map::process(const Index id, const BuildingProcess &process)
{
  if (!existsBuilding(id))
  {
    error("Failed to get building " + std::to_string(id));
  }

  auto &b = m_buildings.at(id);
  process(id, b, *this);
}

void Map::process(const BuildingProcess &process)
{
  for (auto &b : m_buildings)
  {
    process(b.first, b.second, *this);
  }
}

void Map::process(const CitizenProcess &process)
{
  for (auto &c : m_citizens)
  {
    process(c.first, c.second, *this);
  }
}

auto Map::at(const MapPoint &pos) -> Tile &
{
  if (!m_coords.valid(pos))
  {
    error("Failed to get tile " + pos.str(), "Dimensions are " + m_coords.str());
  }

  return m_tiles.at(m_coords.linear(pos));
}

void Map::initialize()
{
  m_tiles.resize(m_coords.count(), Tile{});

  // Base terrain.
  for (auto y = 0; y < HEIGHT; ++y)
  {
    for (auto x = 0; x < 1; ++x)
    {
      at(MapPoint{x, y}) = newTile(terrain::Type::WATER);
    }

    if (y % 2 == 0)
    {
      at(MapPoint{1, y}) = newTile(terrain::Type::WATER);
    }
    else
    {
      at(MapPoint{1, y}) = newFloodablePlain();
    }

    for (auto x = 2; x < 3; ++x)
    {
      at(MapPoint{x, y}) = newFloodablePlain();
    }

    if (y % 2 == 0)
    {
      at(MapPoint{3, y}) = newFloodablePlain();
    }
  }

  for (auto x = 0; x < 8; ++x)
  {
    at(MapPoint{x, 2}) = newTile(terrain::Type::WATER);
  }
  at(MapPoint{4, 4}) = newTile(terrain::Type::WATER);
  at(MapPoint{5, 4}) = newTile(terrain::Type::WATER);
  at(MapPoint{5, 5}) = newTile(terrain::Type::WATER);

  // Entry points.
  m_entryPoint = {7, 0};
  m_exitPoint  = {7, 7};

  // Buildings.
  spawn(building::Type::HOUSE, MapPoint{4, 5}, {});
  spawn(building::Type::ROAD, MapPoint{5, 6}, {});
}

void Map::handleBuildingSpawned(const Building &b) noexcept
{
  info("Spawned " + b.str());
}

void Map::handleBuildingDemolished(const Building &b) noexcept
{
  info("Demolished " + b.str());
}

} // namespace pharaoh
