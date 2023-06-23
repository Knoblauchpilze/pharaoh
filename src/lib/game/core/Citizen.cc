
#include "Citizen.hh"

namespace pharaoh {
namespace citizen {
auto str(const Type t) noexcept -> std::string
{
  switch (t)
  {
    case Type::LABOR_SEEKER:
      return "labor_seeker";
    case Type::GRANARY:
      return "granary";
    case Type::FARMER:
      return "farmer";
    case Type::BAZAAR:
      return "bazaar";
    default:
      return "unknown";
  }
}

auto str(const State s) noexcept -> std::string
{
  switch (s)
  {
    case State::ALIVE:
      return "alive";
    case State::DYING:
      return "dying";
    case State::DEAD:
      return "dead";
    default:
      return "unknown";
  }
}

auto str(const Motion m) noexcept -> std::string
{
  switch (m)
  {
    case Motion::USE_ROADS:
      return "use_roads";
    case Motion::USE_ANY:
      return "use_any";
    default:
      return "unknown";
  }
}

auto motion(const Type t) noexcept -> Motion
{
  switch (t)
  {
    case Type::FARMER:
      return Motion::USE_ANY;
    default:
      return Motion::USE_ROADS;
  }
}
} // namespace citizen

auto newCitizen(const citizen::Type type, const float x, const float y) noexcept -> Citizen
{
  return Citizen{.type = type, .x = x, .y = y};
}

} // namespace pharaoh
