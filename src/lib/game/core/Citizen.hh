
#pragma once

#include "Index.hh"
#include <string>

namespace pharaoh {
namespace citizen {
enum class Type
{
  LABOR_SEEKER,
  GRANARY,
  FARMER,
  BAZAAR,
};

auto str(const Type t) noexcept -> std::string;

enum class State
{
  ALIVE,
  DYING,
  DEAD,
};

auto str(const State s) noexcept -> std::string;

enum class Motion
{
  USE_ROADS,
  USE_ANY,
};

auto str(const Motion m) noexcept -> std::string;
auto motion(const Type t) noexcept -> Motion;

} // namespace citizen

struct Citizen
{
  citizen::Type type{citizen::Type::LABOR_SEEKER};
  float x;
  float y;
  Index homeBuilding{INVALID_INDEX};
  citizen::State state{citizen::State::ALIVE};
};

auto newCitizen(const citizen::Type type, const float x, const float y) noexcept -> Citizen;

} // namespace pharaoh
