
#pragma once

#include "Runner.hh"

namespace pharaoh::services::citizens {

class LaborSeeker : public Runner
{
  public:
  LaborSeeker();

  protected:
  void simulate(const Data &data) const override;

  void roam(const Data &data) const;
  void returnHome(const Data &data) const;
};

} // namespace pharaoh::services::citizens
