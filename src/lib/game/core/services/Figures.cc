
#include "Figures.hh"

namespace pharaoh::services {
constexpr auto SETTLER_POPULATION = 4;

Figures::Figures()
  : Service("figures")
{}

void Figures::run(Map & /*city*/) const
{
  warn("figure generation");
}

} // namespace pharaoh::services
