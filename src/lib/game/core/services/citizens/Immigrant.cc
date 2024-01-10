
#include "Immigrant.hh"

namespace pharaoh::services::citizens {
constexpr auto MOVE_SPEED = 1.0f / 2.0f;

Immigrant::Immigrant()
  : Runner(citizen::Type::IMMIGRANT)
{}

void Immigrant::simulate(const Data &data) const
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
    case citizen::Action::IMMIGRANT_CREATED:
      data.citizen.action = citizen::Action::IMMIGRANT_ARRIVING;
      break;
    case citizen::Action::IMMIGRANT_ARRIVING:
      goToBuilding(data);
      break;
    case citizen::Action::IMMIGRANT_ENTERING_HOUSE:
      enterBuilding(data);
      break;
    default:
      data.citizen.kill();
  }
}

void Immigrant::goToBuilding(const Data &data) const
{
  const auto &b = data.city.building(*data.citizen.homeBuilding);
  if (goTo(data, MapPointf{1.0f * b.pos.x, 1.0f * b.pos.y}, MOVE_SPEED))
  {
    data.citizen.action = citizen::Action::IMMIGRANT_ENTERING_HOUSE;
  }
}

void Immigrant::enterBuilding(const Data &data) const
{
  data.city.process(*data.citizen.homeBuilding,
                    [&data, this](const Index /*id*/, Building &b, const Map & /*city*/) {
                      b.population += data.citizen.population;
                      debug(data.citizen.str() + " arrived home, population is now "
                            + std::to_string(b.population));
                    });

  data.citizen.kill();
}

} // namespace pharaoh::services::citizens
