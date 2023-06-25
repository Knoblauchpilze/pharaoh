
#include "Immigrant.hh"

namespace pharaoh::services::citizens {

Immigrant::Immigrant()
  : Runner(citizen::Type::IMMIGRANT)
{}

void Immigrant::simulate(const Index /*id*/, Citizen &c, Map & /*city*/) const
{
  if (c.state == citizen::State::DEAD)
  {
    error("Can't simulate " + c.str(), "Citizen already dead");
  }

  switch (*c.action)
  {
    case citizen::Action::IMMIGRANT_CREATED:
      c.action = citizen::Action::IMMIGRANT_ARRIVING;
      break;
    case citizen::Action::IMMIGRANT_ARRIVING:
      warn(citizen::str(*c.action) + " not handled yet");
      break;
    case citizen::Action::IMMIGRANT_ENTERING_HOUSE:
      warn(citizen::str(*c.action) + " not handled yet");
      break;
    default:
      c.kill();
  }
}

} // namespace pharaoh::services::citizens
