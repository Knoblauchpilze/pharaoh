
#pragma once

#include "Runner.hh"

namespace pharaoh::services::citizens {

class Immigrant : public Runner
{
  public:
  Immigrant();

  protected:
  void simulate(const Data &data) const override;

  bool killIfBuildingIsNotValid(const Data &data) const;
  void goToBuilding(const Data &data) const;
  void enterBuilding(const Data &data) const;
};

} // namespace pharaoh::services::citizens
