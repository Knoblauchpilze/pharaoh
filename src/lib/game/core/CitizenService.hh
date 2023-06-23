
#pragma once

#include "Map.hh"
#include "RoadNetwork.hh"
#include <core_utils/CoreObject.hh>
#include <optional>

namespace pharaoh {
class CitizenService : public utils::CoreObject
{
  public:
  CitizenService();

  void generate(Map &city) const noexcept;

  private:
  enum class BuildingTask
  {
  };

  auto determineTaskFor(const Building &b, const Map &m) const noexcept
    -> std::optional<BuildingTask>;
  auto shouldSpawnFor(const Index id,
                      const Building &b,
                      const std::optional<BuildingTask> &task,
                      const Map &m) const noexcept -> std::optional<citizen::Type>;

  bool needsLaborSeeker(const Building &b) const noexcept;
};

} // namespace pharaoh
