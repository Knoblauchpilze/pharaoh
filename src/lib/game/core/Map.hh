
#pragma once

#include "Building.hh"
#include "Citizen.hh"
#include "Coordinate.hh"
#include "RoadNetwork.hh"
#include "Tile.hh"
#include <core_utils/CoreObject.hh>
#include <functional>
#include <map>
#include <maths_utils/Point2.hh>
#include <vector>

namespace pharaoh {

class Map;
using BuildingProcess = std::function<void(const Index, Building &, Map &)>;

class Map : public utils::CoreObject
{
  public:
  explicit Map();

  auto w() const noexcept -> int;
  auto h() const noexcept -> int;
  auto at(const int x, const int y) const -> const Tile &;
  auto citizensBegin() const noexcept -> std::map<Index, Citizen>::const_iterator;
  auto citizensEnd() const noexcept -> std::map<Index, Citizen>::const_iterator;

  auto building(const Index id) const -> const Building &;
  auto spawn(const building::Type type, const int x, const int y) -> Index;
  bool demolish(const int x, const int y);
  bool isBuildingConnectedToRoad(const Index id) const;
  auto spawnPointForBuilding(const Index id) const noexcept -> utils::Point2f;
  void process(const BuildingProcess &process);

  auto citizen(const Index id) const -> const Citizen &;
  auto spawn(const citizen::Type type, const float x, const float y) -> Index;

  private:
  Coordinate m_coords;
  std::vector<Tile> m_tiles{};

  Index m_nextBuildingId{};
  std::map<Index, Building> m_buildings{};

  RoadNetwork m_roadNewtork{};

  Index m_nextCitizenId{};
  std::map<Index, Citizen> m_citizens{};

  auto at(const int x, const int y) -> Tile &;
  void initialize();

  void handleBuildingSpawned(const Building &b) noexcept;
  void handleBuildingDemolished(const Building &b) noexcept;
};

} // namespace pharaoh
