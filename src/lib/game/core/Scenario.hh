
#pragma once

#include "Calendar.hh"
#include "Map.hh"
#include "Service.hh"
#include <core_utils/CoreObject.hh>
#include <unordered_map>

namespace pharaoh {

class Scenario : public utils::CoreObject
{
  public:
  Scenario();

  auto name() const noexcept -> std::string;
  auto map() noexcept -> Map &;
  auto date() const noexcept -> const Calendar &;
  auto gold() const noexcept -> int;

  void step();
  void spawn(const building::Type type, float x, float y);
  void demolish(float x, float y);

  private:
  using Tick = int;

  std::string m_name{"scenario"};

  Calendar m_date{};
  Map m_map{};

  int m_gold{1000};

  std::unordered_map<Tick, ServicePtr> m_services{};

  void initializeServices();
};

} // namespace pharaoh
