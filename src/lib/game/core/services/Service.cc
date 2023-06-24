
#include "Service.hh"

namespace pharaoh {

Service::Service(const std::string &name)
  : utils::CoreObject(name)
{
  setService("pharaoh");
}

} // namespace pharaoh
