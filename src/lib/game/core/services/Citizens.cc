
#include "Citizens.hh"
#include "Immigrant.hh"
#include "LaborSeeker.hh"

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
  m_runners[citizen::Type::IMMIGRANT]    = std::make_unique<citizens::Immigrant>();
  m_runners[citizen::Type::LABOR_SEEKER] = std::make_unique<citizens::LaborSeeker>();
}

void Citizens::simulateCitizen(const Index id, Citizen &c, Map &city) const
{
  if (!city.existsCitizen(id))
  {
    warn("No citizen found with id " + std::to_string(id));
    return;
  }

  performAction(id, c, city);
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

  auto data = citizens::Data{.id = id, .citizen = c, .city = city};
  runner->second->run(data);
}

} // namespace pharaoh::services
