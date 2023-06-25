
#include "Citizens.hh"
#include "Immigrant.hh"

namespace pharaoh::services {

Citizens::Citizens()
  : Service("citizens")
{
  initializeRunners();
}

void Citizens::run(Map &city) const
{
  city.process([this](const Index id, Citizen &c, Map &city) { simulateCitizen(id, c, city); });
}

void Citizens::initializeRunners()
{
  m_runners[citizen::Type::IMMIGRANT] = std::make_unique<citizens::Immigrant>();
}

void Citizens::simulateCitizen(const Index id, Citizen &c, Map &city) const
{
  if (!city.existsCitizen(id))
  {
    warn("No citizen found with id " + std::to_string(id));
    return;
  }

  killIfNeeded(id, c, city);
  performAction(id, c, city);
}

void Citizens::killIfNeeded(const Index /*id*/, Citizen &c, Map &city) const noexcept
{
  if (c.homeBuilding && !city.existsBuilding(*c.homeBuilding))
  {
    log("Home for " + c.str() + " does not exist anymore");
    c.kill();
  }
}

void Citizens::performAction(const Index id, Citizen &c, Map &city) const noexcept
{
  if (!c.action)
  {
    log(c.str() + " ran out of actions");
    c.kill();
    return;
  }

  if (c.state == citizen::State::DEAD)
  {
    return;
  }

  const auto runner = m_runners.find(c.type);
  if (runner == m_runners.end())
  {
    warn("Unhandled citizen type: " + citizen::str(c.type));
    return;
  }

  runner->second->run(id, c, city);
}

} // namespace pharaoh::services
