
#include "Migrants.hh"

namespace pharaoh::services {
constexpr auto SETTLER_POPULATION = 4;

Migrants::Migrants()
  : Service("migrants")
{}

void Migrants::run(Map &city) const
{
  generateMigrants(city);
}

void Migrants::generateMigrants(Map &city) const noexcept
{
  const auto emptyHouses = collectEmptyHouses(city);

  const auto entry = city.entryPoint();
  for (const auto &house : emptyHouses)
  {
    city.spawn(citizen::Type::IMMIGRANT, 1.0f * entry.x, 1.0f * entry.y, house, [](Citizen &c) {
      c.population = SETTLER_POPULATION;
      c.action     = {citizen::Action::IMMIGRANT_CREATED};
    });
    log("Spawned settler at " + entry.str());
  }
}

auto Migrants::collectEmptyHouses(Map &city) const noexcept -> std::vector<Index>
{
  std::vector<Index> emptyHouses;

  city.process([&emptyHouses](const Index id, Building &b, const Map & /*city*/) {
    if (b.type == building::Type::HOUSE && b.population == 0 && b.citizens.empty())
    {
      emptyHouses.push_back(id);
    }
  });

  return emptyHouses;
}

} // namespace pharaoh::services
