
#include "PathFinder.hh"

namespace pharaoh {

PathFinder::PathFinder(const Map &city) noexcept
  : utils::CoreObject("path")
  , m_city(city)
{
  setService("pharaoh");
}

void PathFinder::setStart(const MapPointf &start) noexcept
{
  m_start = start;
}

void PathFinder::setEnd(const MapPointf &end) noexcept
{
  m_end = end;
}

auto PathFinder::find(const path::Options & /*options*/) -> std::optional<std::vector<MapPointf>>
{
  std::vector<MapPointf> out;

  if (!m_start || !m_end)
  {
    error("Can't find path", "Start or end point not set");
  }

  out.push_back(*m_end);

  return {out};
}

} // namespace pharaoh
