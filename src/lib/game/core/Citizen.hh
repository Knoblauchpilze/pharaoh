
#pragma once

#include "Index.hh"
#include <string>

namespace pharaoh {
namespace citizen {
enum class Type
{
  SETTLER
};

auto str(const Type t) noexcept -> std::string;

} // namespace citizen

struct Citizen
{
  citizen::Type type{citizen::Type::SETTLER};
  float x;
  float y;
  Index homeBuilding{INVALID_INDEX};

  auto str() const noexcept -> std::string;
};

auto newCitizen(const citizen::Type type, const float x, const float y) noexcept -> Citizen;

} // namespace pharaoh
