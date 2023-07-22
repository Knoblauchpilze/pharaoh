
#include "LaborSeeker.hh"

namespace pharaoh::services::citizens {
constexpr auto MOVE_SPEED = 1.0f / 2.0f;

LaborSeeker::LaborSeeker()
  : Runner(citizen::Type::LABOR_SEEKER)
{}

void LaborSeeker::simulate(const Data &data) const
{
  if (data.citizen.state == citizen::State::DEAD)
  {
    error("Can't simulate " + data.citizen.str(), "Citizen already dead");
  }

  if (killIfBuildingIsNotValid(data))
  {
    return;
  }

  switch (*data.citizen.action)
  {
    case citizen::Action::LABOR_SEEKER_ROAMING:
      roam(data);
      break;
    case citizen::Action::LABOR_SEEKER_RETURNING_HOME:
      returnHome(data);
      break;
    default:
      data.citizen.kill();
  }
}

void LaborSeeker::roam(const Data &data) const
{
  warn("Should roam");
  data.citizen.action = citizen::Action::LABOR_SEEKER_RETURNING_HOME;
}

void LaborSeeker::returnHome(const Data &data) const
{
  warn("Nothing happened");
  data.citizen.kill();
}

} // namespace pharaoh::services::citizens
