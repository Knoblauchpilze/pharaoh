
#include "Path.hh"

namespace astar {

Path::Path() noexcept
  : utils::CoreObject("path")
{
  setService("astar");
}

Path::Path(const utils::Point2i &start) noexcept
  : utils::CoreObject("path")
{
  setService("astar");

  add(start, false);
}

void Path::add(const utils::Point2i &p, bool duplicate) noexcept
{
  if (empty())
  {
    m_points.push_back(p);
    return;
  }

  const utils::Point2i &l = m_points.back();
  if (!duplicate && l == p)
  {
    return;
  }

  m_points.push_back(p);
}

auto Path::operator[](unsigned id) const -> const utils::Point2i &
{
  if (id > m_points.size())
  {
    error("Failed to access point at " + std::to_string(id),
          "Path only defines " + std::to_string(m_points.size()) + " value(s)");
  }

  return m_points[id];
}

void Path::clear() noexcept
{
  m_points.clear();
}

void Path::reverse() noexcept
{
  std::reverse(m_points.begin(), m_points.end());
}

auto Path::begin() const -> const utils::Point2i &
{
  if (empty())
  {
    error("Failed to get starting point of the path", "Path is empty");
  }

  return m_points.front();
}

auto Path::end() const -> const utils::Point2i &
{
  if (empty())
  {
    error("Failed to get ending point of the path", "Path is empty");
  }

  return m_points.back();
}

auto Path::size() const noexcept -> std::size_t
{
  return m_points.size();
}

bool Path::empty() const noexcept
{
  return m_points.empty();
}

auto Path::advance() -> utils::Point2i
{
  if (empty())
  {
    error("Failed to advance on path", "Path is empty");
  }

  utils::Point2i p = m_points.front();
  m_points.pop_front();

  return p;
}

} // namespace astar
