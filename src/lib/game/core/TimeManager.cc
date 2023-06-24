
#include "TimeManager.hh"

namespace pharaoh {

TimeManager::TimeManager(float stepDurationInSeconds) noexcept
  : m_stepDurationInSeconds(stepDurationInSeconds)
{}

bool TimeManager::step(float secondsElapsed)
{
  m_lastStep += secondsElapsed;
  const auto stepTriggered = (m_lastStep >= m_stepDurationInSeconds);
  if (stepTriggered)
  {
    m_lastStep = 0.0f;
  }

  return stepTriggered;
}

} // namespace pharaoh
