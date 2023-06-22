
#include "RoadNetwork.hh"

namespace pharaoh {
RoadNetwork::RoadNetwork() noexcept
  : utils::CoreObject("road_network")
{
  setService("pharaoh");
}

void RoadNetwork::addToNetwork(const int x, const int y)
{
  const auto in = std::make_pair(x, y);
  if (m_network.contains(in))
  {
    error("Can't add road to network",
          std::to_string(x) + "x" + std::to_string(y) + " is already part of a network");
  }

  m_network.insert(in);
}

void RoadNetwork::removeFromNetwork(const int x, const int y)
{
  const auto in = std::make_pair(x, y);
  if (m_network.erase(in) != 1)
  {
    error("Can't remove road from network",
          std::to_string(x) + "x" + std::to_string(y) + " is already part of a network");
  }
}

bool RoadNetwork::isConnectedToRoad(const int x, const int y) const noexcept
{
  for (auto i = y - 1; i <= y + 1; ++i)
  {
    for (auto j = x - 1; j <= x + 1; ++j)
    {
      const auto cur = std::make_pair(j, i);
      if (m_network.contains(cur))
      {
        return true;
      }
    }
  }
  return false;
}

} // namespace pharaoh
