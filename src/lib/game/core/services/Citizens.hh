
#pragma once

#include "Map.hh"
#include "Runner.hh"
#include "Service.hh"
#include <unordered_map>
#include <vector>

namespace pharaoh::services {

class Citizens : public Service
{
  public:
  Citizens();

  void run(Map &city) const override;

  private:
  std::unordered_map<citizen::Type, RunnerPtr> m_runners{};

  void initializeRunners();

  void simulateCitizen(const Index id, Citizen &c, Map &city) const;
  void performAction(const Index id, Citizen &c, Map &city) const noexcept;
};

} // namespace pharaoh::services
