
#pragma once

#include <core_utils/TimeUtils.hh>
#include <optional>

namespace pharaoh {

class TimeManager
{
  public:
  TimeManager(float stepDurationInSeconds = 1.0f) noexcept;

  /// @brief - Step the time with the corresponding elapsed duration and returns
  /// true in case we reached a time point where we should trigger the process
  /// attached to this manager.
  /// @param secondsElapsed - the elapsed duration since the last call in seconds.
  /// @return - true if a new process should be triggered.
  bool step(float secondsElapsed);

  private:
  float m_stepDurationInSeconds{1.0f};
  float m_lastStep{0.0f};
};

} // namespace pharaoh
