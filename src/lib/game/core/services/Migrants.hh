
#pragma once

#include "Map.hh"
#include "Service.hh"
#include <vector>

namespace pharaoh::services {

class Migrants : public Service
{
  public:
  Migrants();

  void run(Map &city) const override;

  private:
  void generateMigrants(Map &city) const noexcept;

  auto collectEmptyHouses(Map &city) const noexcept -> std::vector<Index>;
};

} // namespace pharaoh::services
