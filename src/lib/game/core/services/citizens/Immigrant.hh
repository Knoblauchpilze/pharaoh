
#pragma once

#include "Runner.hh"

namespace pharaoh::services::citizens {

class Immigrant : public Runner
{
  public:
  Immigrant();

  protected:
  void simulate(const Index id, Citizen &c, Map &city) const override;
};

} // namespace pharaoh::services::citizens
