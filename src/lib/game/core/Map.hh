
#pragma once

#include "Building.hh"
#include "Citizen.hh"
#include "Coordinate.hh"
#include "MapPoint.hh"
#include "Tile.hh"
#include <core_utils/CoreObject.hh>
#include <functional>
#include <map>
#include <maths_utils/Point2.hh>
#include <optional>
#include <vector>

namespace pharaoh {

class Map;
using TileProcess     = std::function<void(const MapPoint &pos, Tile &, Map &)>;
using BuildingProcess = std::function<void(const Index, Building &, Map &)>;
using CitizenProcess  = std::function<void(const Index, Citizen &, Map &)>;

using BuildingInit = std::function<void(Building &)>;
using CitizenInit  = std::function<void(Citizen &)>;

class Map : public utils::CoreObject
{
  public:
  explicit Map();

  auto w() const noexcept -> int;
  auto h() const noexcept -> int;
  bool valid(const MapPoint &pos) const noexcept;

  auto at(const MapPoint &pos) const -> const Tile &;

  bool existsBuilding(const Index id) const noexcept;
  auto building(const Index id) const -> const Building &;
  auto spawn(const building::Type type, const MapPoint &pos, const std::optional<BuildingInit> &init)
    -> Index;
  bool demolish(const MapPoint &pos);

  bool existsCitizen(const Index id) const noexcept;
  auto citizen(const Index id) const -> const Citizen &;
  auto spawn(const citizen::Type type,
             const MapPointf &pos,
             const std::optional<Index> &homeBuilding,
             const std::optional<CitizenInit> &init) -> Index;
  bool kill(const Index id);

  auto entryPoint() const noexcept -> MapPoint;
  auto exitPoint() const noexcept -> MapPoint;

  void process(const TileProcess &process);
  void process(const Index id, const BuildingProcess &process);
  void process(const BuildingProcess &process);
  void process(const CitizenProcess &process);

  private:
  Coordinate m_coords;
  std::vector<Tile> m_tiles{};

  MapPoint m_entryPoint{};
  MapPoint m_exitPoint{};

  Index m_nextBuildingId{};
  std::map<Index, Building> m_buildings{};

  Index m_nextCitizenId{};
  std::map<Index, Citizen> m_citizens{};

  auto at(const MapPoint &pos) -> Tile &;
  void initialize();

  void handleBuildingSpawned(const Building &b) noexcept;
  void handleBuildingDemolished(const Building &b) noexcept;
};

} // namespace pharaoh
