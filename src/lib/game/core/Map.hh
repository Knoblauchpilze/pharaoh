
#pragma once

#include "Building.hh"
#include "Citizen.hh"
#include "Coordinate.hh"
#include "RoadNetwork.hh"
#include "Tile.hh"
#include <core_utils/CoreObject.hh>
#include <map>
#include <vector>

namespace pharaoh {

class Map : public utils::CoreObject
{
  public:
  explicit Map();

  auto w() const noexcept -> int;
  auto h() const noexcept -> int;
  auto at(const int x, const int y) const -> const Tile &;

  auto building(const Index id) const -> const Building &;
  auto spawn(const building::Type type, const int x, const int y) -> Index;
  bool demolish(const int x, const int y);
  bool isBuildingConnectedToRoad(const Index id) const;

  auto citizen(const Index id) const -> const Citizen &;
  auto spawn(const citizen::Type type, const int x, const int y) -> Index;

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
};

} // namespace pharaoh
