
#pragma once

#include <maths_utils/Point2.hh>
#include <vector>

namespace astar {

class Locator
{
  public:
  /// @brief - Interface method allowing to determine whether the input
  /// position is occupied or not.
  /// @param p - the coordinates to check for obstruction.
  /// @return - true if the location is occupied.
  virtual bool obstructed(const utils::Point2i &p) const noexcept = 0;
};

} // namespace astar
