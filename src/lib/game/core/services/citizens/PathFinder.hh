
#pragma once

#include "Map.hh"
#include "MapPoint.hh"
#include <core_utils/CoreObject.hh>
#include <optional>

namespace pharaoh {
namespace path {
struct Options
{};
} // namespace path

class PathFinder : public utils::CoreObject
{
  public:
  PathFinder(const Map &city) noexcept;

  void setStart(const MapPointf &start) noexcept;
  void setEnd(const MapPointf &end) noexcept;

  auto find(const path::Options &options) -> std::optional<std::vector<MapPointf>>;

  private:
  const Map &m_city;

  std::optional<MapPointf> m_start{};
  std::optional<MapPointf> m_end{};
};

} // namespace pharaoh
