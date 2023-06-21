
#pragma once

#include "Building.hh"
#include "Coordinate.hh"
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

  private:
  Coordinate m_coords;
  std::vector<Tile> m_tiles{};

  Index m_nextBuildingId{};
  std::map<Index, Building> m_buildings{};

  auto at(const int x, const int y) -> Tile &;
  void initialize();
};

} // namespace pharaoh
