
#pragma once

#include <string>
#include <utility>

namespace pharaoh {

class Coordinate
{
  public:
  explicit Coordinate(int width, int height) noexcept;

  auto w() const noexcept -> int;
  auto h() const noexcept -> int;
  auto count() const noexcept -> int;

  bool valid(int x, int y) const noexcept;
  bool valid(int index) const noexcept;
  auto linear(int x, int y) const noexcept -> int;
  auto to2d(int linear) const noexcept -> std::pair<int, int>;

  auto str() const noexcept -> std::string;
  auto str(int x, int y) const noexcept -> std::string;

  private:
  int m_width;
  int m_height;
};

} // namespace pharaoh