
#pragma once

#include "Citizen.hh"
#include "Index.hh"
#include "Map.hh"
#include <core_utils/CoreObject.hh>
#include <memory>

namespace pharaoh::services {

namespace citizens {
struct Data
{
  const Index id;
  Citizen &citizen;
  Map &city;
};
} // namespace citizens

class Runner : public utils::CoreObject
{
  public:
  Runner(const citizen::Type type);

  void run(const citizens::Data &data) const;

  private:
  citizen::Type m_type;

  protected:
  virtual void simulate(const citizens::Data &data) const = 0;

  bool goTo(const citizens::Data &data, const MapPointf &dest, const float speed) const;
  bool determinePath(const citizens::Data &data, const MapPointf &dest) const;
  bool moveOnPath(const citizens::Data &data, const float speed) const;
};

using RunnerPtr = std::unique_ptr<Runner>;

} // namespace pharaoh::services
