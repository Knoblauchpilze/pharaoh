
#pragma once

#include "Map.hh"
#include "Service.hh"
#include <vector>

namespace pharaoh::services {

class Figures : public Service
{
  public:
  Figures();

  void run(Map &city) const override;

  private:
};

} // namespace pharaoh::services
