
#pragma once

#include "Citizen.hh"
#include "Index.hh"
#include "Map.hh"
#include <core_utils/CoreObject.hh>
#include <memory>

namespace pharaoh::services {

class Runner : public utils::CoreObject
{
  public:
  Runner(const citizen::Type type);

  void run(const Index id, Citizen &c, Map &city) const;

  private:
  citizen::Type m_type;

  protected:
  virtual void simulate(const Index id, Citizen &c, Map &city) const = 0;
};

using RunnerPtr = std::unique_ptr<Runner>;

} // namespace pharaoh::services
