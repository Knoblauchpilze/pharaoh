
#pragma once

#include <maths_utils/Point2.hh>
#include <vector>

namespace astar {

/// @brief - Forward declaration of the node class.
class Node;

/// @brief - A liste of nodes.
using Nodes = std::vector<Node>;

/// @brief - Enumeration describing the position of a node
/// relatively to its neighbots.
enum Neighbor
{
  North,
  East,
  South,
  West,
  Count
};

/// @brief - Convenience structure to define an opened node.
class Node
{
  public:
  /// @brief - Generate a new node with the specified position and cost and
  /// heuristic.
  /// @param p - the position of the node.
  /// @param c - the cost to reach this node.
  /// @param h - the heuristic to the target node.
  Node(const utils::Point2i &p = utils::Point2i(), float c = 0.0f, float h = 0.0f) noexcept;

  auto p() const noexcept -> const utils::Point2i &;

  auto cost() const noexcept -> float;

  auto heuristic() const noexcept -> float;

  /// @brief - Whether or not the node contains the point. Typically an
  /// equality check between the point attached to the node and the input
  /// coordinate.
  /// @param p - the point to check.
  /// @return - `true` in case the point is in the node.
  bool contains(const utils::Point2i &p) const noexcept;

  /// @brief - Generate neighbors for this node.
  /// @param target - target, used to compute the heuristic of each neighbor.
  /// @return - the list of neighboring nodes.
  auto generateNeighbors(const utils::Point2i &target) const noexcept -> Nodes;

  private:
  /// @brief - The position of the node.
  utils::Point2i m_p;

  /// @brief - The cost to reach this node.
  float m_c;

  /// @brief - The heuristic for this node. The larger this value the farther
  /// away from the goal.
  float m_h;
};

/// @brief - Use a basic string transformation to do a conversion of the input
/// coordinates to a single string.
/// @param p - the coordinates to hash.
/// @return - the mapped string for this node.
auto hash(const utils::Point2i &p) noexcept -> std::string;

/// @brief - Used to invert the hash provided as input to a set of coordinates.
/// @param hash - the value to invert.
/// @return - the normalized coordinates computed from the hash.
auto unhash(const std::string &hash) noexcept -> utils::Point2i;

} // namespace astar
