
#pragma once

#include "Calendar.hh"
#include "Map.hh"
#include <core_utils/CoreObject.hh>

namespace pharaoh {

class Scenario : public utils::CoreObject
{
  public:
  Scenario();

  auto name() const noexcept -> std::string;
  auto map() const noexcept -> const Map &;
  auto date() const noexcept -> const Calendar &;
  auto gold() const noexcept -> int;

  void step();
  void spawn(const building::Type type, float x, float y);
  void demolish(float x, float y);

  private:
  std::string m_name{"scenario"};
  Map m_map{};
  Calendar m_date{};
  int m_gold{1000};
};

} // namespace pharaoh
