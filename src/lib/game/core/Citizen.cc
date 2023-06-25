
#include "Citizen.hh"

namespace pharaoh {
namespace citizen {
auto str(const Type t) noexcept -> std::string
{
  switch (t)
  {
    case Type::IMMIGRANT:
      return "immigrant";
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
    case State::DEAD:
      return "dead";
    default:
      return "unknown";
  }
}

auto str(const Action a) noexcept -> std::string
{
  switch (a)
  {
    case Action::IMMIGRANT_CREATED:
      return "immigrant_created";
    case Action::IMMIGRANT_ARRIVING:
      return "immigrant_arriving";
    case Action::IMMIGRANT_ENTERING_HOUSE:
      return "immigrant_entering_house";
    default:
      return "unknown";
  }
}

} // namespace citizen

auto Citizen::str() const noexcept -> std::string
{
  return citizen::str(type) + "[" + pos.str() + "]";
}

void Citizen::kill() noexcept
{
  state = citizen::State::DEAD;
}

auto newCitizen(const citizen::Type type, const MapPointf &pos) noexcept -> Citizen
{
  return Citizen{.type = type, .pos = pos};
}

} // namespace pharaoh
