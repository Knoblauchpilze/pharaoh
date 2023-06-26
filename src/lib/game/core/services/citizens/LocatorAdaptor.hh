
#pragma once

#include "Locator.hh"
#include "Map.hh"

namespace pharaoh::services {

class LocatorAdaptor : public astar::Locator
{
  public:
  LocatorAdaptor(const Map &city, const bool useFloodablePlains) noexcept;

  bool obstructed(const utils::Point2i &p) const noexcept override;

  private:
  const Map &m_city;
  bool m_useFloodablePlains{false};

  bool isTileObstructed(const Tile &t) const noexcept;
};

} // namespace pharaoh::services
