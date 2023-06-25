
#pragma once

#include "Index.hh"
#include <optional>
#include <string>

namespace pharaoh {
namespace citizen {
enum class Type
{
  IMMIGRANT
};

auto str(const Type t) noexcept -> std::string;

enum class State
{
  ALIVE,
  DEAD,
};

auto str(const State s) noexcept -> std::string;

enum class Action
{
  IMMIGRANT_CREATED,
  IMMIGRANT_ARRIVING,
  IMMIGRANT_ENTERING_HOUSE,
};

auto str(const Action a) noexcept -> std::string;

} // namespace citizen

struct Citizen
{
  citizen::Type type{citizen::Type::IMMIGRANT};
  float x;
  float y;
  std::optional<Index> homeBuilding{};
  int population{0};

  std::optional<citizen::Action> action{};
  citizen::State state{citizen::State::ALIVE};

  auto str() const noexcept -> std::string;
  void kill() noexcept;
};

auto newCitizen(const citizen::Type type, const float x, const float y) noexcept -> Citizen;

} // namespace pharaoh
