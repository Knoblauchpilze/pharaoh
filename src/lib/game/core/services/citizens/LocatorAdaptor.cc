
#include "LocatorAdaptor.hh"

namespace pharaoh::services {

LocatorAdaptor::LocatorAdaptor(const Map &city, const bool useFloodablePlains) noexcept
  : Locator()
  , m_city(city)
  , m_useFloodablePlains(useFloodablePlains)
{}

bool LocatorAdaptor::obstructed(const utils::Point2i &p) const noexcept
{
  MapPoint pos{p.x(), p.y()};

  if (!m_city.valid(pos))
  {
    return true;
  }

  const auto &t = m_city.at(pos);
  return isTileObstructed(t);
}

inline bool LocatorAdaptor::isTileObstructed(const Tile &t) const noexcept
{
  if (t.type == terrain::Type::WATER)
  {
    return true;
  }
  if (!m_useFloodablePlains && t.floodable)
  {
    return true;
  }
  if (!t.isBuilding())
  {
    return false;
  }

  const auto &b = m_city.building(t.buildingId);
  return !building::traversable(b.type);
}

} // namespace pharaoh::services
