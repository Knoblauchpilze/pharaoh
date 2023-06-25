
#include "Runner.hh"
#include "PathFinder.hh"
#include <maths_utils/Vector2.hh>

namespace pharaoh::services {
constexpr auto ARRIVAL_THRESHOLD = 0.01f;

Runner::Runner(const citizen::Type type)
  : utils::CoreObject(citizen::str(type))
  , m_type(type)
{
  setService("pharaoh");
}

void Runner::run(const citizens::Data &data) const
{
  if (data.citizen.type != m_type)
  {
    error("Can't simulate " + data.citizen.str(), "Expected type " + citizen::str(m_type));
  }

  simulate(data);
}

bool Runner::goTo(const citizens::Data &data, const MapPointf &dest, const float speed) const
{
  if (!data.citizen.destination)
  {
    if (!determinePath(data, dest))
    {
      warn(data.citizen.str() + " failed to find a path to " + dest.str());
      data.citizen.kill();
    }
  }

  if (moveOnPath(data, speed))
  {
    if (data.citizen.path.empty())
    {
      return true;
    }

    data.citizen.path.pop();
  }

  return false;
}

bool Runner::determinePath(const citizens::Data &data, const MapPointf &dest) const
{
  PathFinder finder(data.city);
  finder.setStart(data.citizen.pos);
  finder.setEnd(dest);

  const auto path = finder.find({});

  if (!path)
  {
    return false;
  }

  data.citizen.destination = dest;
  for (const auto &pos : *path)
  {
    data.citizen.path.push(pos);
  }

  const auto goal = data.citizen.path.top();
  if (utils::fuzzyEqual(goal.x, dest.x) && utils::fuzzyEqual(goal.y, dest.y))
  {
    data.citizen.path.pop();
  }

  return true;
}

bool Runner::moveOnPath(const citizens::Data &data, const float speed) const
{
  auto target = *data.citizen.destination;
  if (!data.citizen.path.empty())
  {
    target = data.citizen.path.top();
  }

  utils::Vector2f targetV2f{target.x, target.y};
  utils::Vector2f pos{data.citizen.pos.x, data.citizen.pos.y};
  utils::Vector2f dir = targetV2f - pos;

  const auto d = dir.length();
  dir.normalize();

  pos += dir * std::min(speed, d);

  data.citizen.pos.x = pos.x();
  data.citizen.pos.y = pos.y();

  return d <= ARRIVAL_THRESHOLD;
}

} // namespace pharaoh::services
