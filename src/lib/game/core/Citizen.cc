
#include "Citizen.hh"

namespace pharaoh {
namespace citizen {
auto str(const Type t) noexcept -> std::string
{
  switch (t)
  {
    case Type::WALKER:
      return "walker";
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

} // namespace citizen

auto newCitizen(const citizen::Type type, const float x, const float y) noexcept -> Citizen
{
  return Citizen{.type = type, .x = x, .y = y};
}

} // namespace pharaoh
