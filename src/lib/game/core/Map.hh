
#pragma once

#include "Building.hh"
#include "Coordinate.hh"
#include "Tile.hh"
#include <core_utils/CoreObject.hh>
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
  auto spawn(const int x, const int y, const building::Type &type) -> Index;

  private:
  Coordinate m_coords;
  std::vector<Tile> m_tiles{};

  std::vector<Building> m_buildings{};

  auto at(const int x, const int y) -> Tile &;
  void initialize();
};

} // namespace pharaoh
