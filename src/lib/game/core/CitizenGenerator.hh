
#pragma once

#include "Map.hh"
#include "RoadNetwork.hh"
#include <core_utils/CoreObject.hh>
#include <optional>

namespace pharaoh {
class CitizenGenerator : public utils::CoreObject
{
  public:
  CitizenGenerator();

  void generate(Map &city) const noexcept;

  private:
  enum class BuildingTask
  {
  };

  auto determineTaskFor(const Building &b, const Map &m) const -> std::optional<BuildingTask>;
  bool shouldSpawnFor(const Building &b,
                      const std::optional<BuildingTask> &task,
                      const Map &m) const;
};

} // namespace pharaoh
