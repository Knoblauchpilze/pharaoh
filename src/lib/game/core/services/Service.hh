
#pragma once

#include "Map.hh"
#include <core_utils/CoreObject.hh>
#include <memory>

namespace pharaoh {

class Service : public utils::CoreObject
{
  public:
  Service(const std::string &name);

  virtual void run(Map &city) const = 0;
};

using ServicePtr = std::unique_ptr<Service>;
} // namespace pharaoh
