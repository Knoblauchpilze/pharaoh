
#include "Migrants.hh"

namespace pharaoh::services {

Migrants::Migrants()
  : Service("migrants")
{}

void Migrants::run(Map & /*city*/) const
{
  warn("nothing happening");
}

} // namespace pharaoh::services
