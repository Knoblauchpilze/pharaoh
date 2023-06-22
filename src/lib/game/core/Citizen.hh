
#pragma once

#include <string>

namespace pharaoh {
namespace citizen {
/// @brief - The type of a citizen.
enum class Type
{
  WALKER,
  GRANARY,
  FARMER,
  BAZAAR,
};

auto str(const Type t) noexcept -> std::string;

} // namespace citizen

struct Citizen
{
  citizen::Type type{citizen::Type::WALKER};
  float x;
  float y;
};

auto newCitizen(const citizen::Type type, const float x, const float y) noexcept -> Citizen;

} // namespace pharaoh
