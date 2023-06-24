
#include "Citizen.hh"

namespace pharaoh {
namespace citizen {
auto str(const Type t) noexcept -> std::string
{
  switch (t)
  {
    case Type::SETTLER:
      return "settler";
    default:
      return "unknown";
  }
}

} // namespace citizen

auto Citizen::str() const noexcept -> std::string
{
  return citizen::str(type) + "-" + std::to_string(x) + "x" + std::to_string(y);
}

auto newCitizen(const citizen::Type type, const float x, const float y) noexcept -> Citizen
{
  return Citizen{.type = type, .x = x, .y = y};
}

} // namespace pharaoh
