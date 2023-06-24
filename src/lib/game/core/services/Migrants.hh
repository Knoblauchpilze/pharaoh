
#pragma once

#include "Map.hh"
#include "Service.hh"

namespace pharaoh::services {

class Migrants : public Service
{
  public:
  Migrants();

  void run(Map &city) const override;
};

} // namespace pharaoh::services
