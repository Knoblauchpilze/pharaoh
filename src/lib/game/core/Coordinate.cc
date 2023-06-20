
#include "Coordinate.hh"
#include <algorithm>

namespace pharaoh {

Coordinate::Coordinate(int width, int height) noexcept
  : m_width(std::max(1, width))
  , m_height(std::max(1, height))
{}

auto Coordinate::w() const noexcept -> int
{
  return m_width;
}

auto Coordinate::h() const noexcept -> int
{
  return m_height;
}

auto Coordinate::count() const noexcept -> int
{
  return w() * h();
}

bool Coordinate::valid(int x, int y) const noexcept
{
  return x >= 0 && y >= 0 && x < w() && y < h();
}

bool Coordinate::valid(int index) const noexcept
{
  const auto [x, y] = to2d(index);
  return valid(x, y);
}

auto Coordinate::linear(int x, int y) const noexcept -> int
{
  return y * w() + x;
}

auto Coordinate::to2d(int linear) const noexcept -> std::pair<int, int>
{
  return std::make_pair(linear % w(), linear / w());
}

auto Coordinate::str() const noexcept -> std::string
{
  return std::to_string(w()) + "x" + std::to_string(h());
}

auto Coordinate::str(int x, int y) const noexcept -> std::string
{
  return std::to_string(x) + "x" + std::to_string(y);
}

} // namespace pharaoh
