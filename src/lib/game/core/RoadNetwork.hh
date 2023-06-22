
#pragma once

#include <core_utils/CoreObject.hh>
#include <set>

namespace pharaoh {
class RoadNetwork : public utils::CoreObject
{
  public:
  RoadNetwork() noexcept;

  void addToNetwork(const int x, const int y);
  void removeFromNetwork(const int x, const int y);

  bool isConnectedToRoad(const int x, const int y) const noexcept;

  private:
  using Point   = std::pair<int, int>;
  using Network = std::set<Point>;

  Network m_network{};
};

} // namespace pharaoh
