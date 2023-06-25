
#include "Runner.hh"

namespace pharaoh::services {

Runner::Runner(const citizen::Type type)
  : utils::CoreObject(citizen::str(type))
  , m_type(type)
{
  setService("pharaoh");
}

void Runner::run(const Index id, Citizen &c, Map &city) const
{
  if (c.type != m_type)
  {
    error("Can't simulate " + c.str(), "Expected type " + citizen::str(m_type));
  }

  simulate(id, c, city);
}

} // namespace pharaoh::services
