
#include "Calendar.hh"
#include <iomanip>

namespace pharaoh {
constexpr auto TICKS_IN_A_DAY   = 5;
constexpr auto DAYS_IN_A_MONTH  = 20;
constexpr auto MONTHS_IN_A_YEAR = 12;

Calendar::Calendar(int year, int month, int day) noexcept
  : m_year(year)
  , m_month(month)
  , m_day(day)
{}

auto Calendar::y() const noexcept -> int
{
  return m_year;
}

auto Calendar::m() const noexcept -> int
{
  return m_month;
}

auto Calendar::d() const noexcept -> int
{
  return m_day;
}

auto Calendar::t() const noexcept -> int
{
  return m_tick;
}

void Calendar::tick()
{
  ++m_tick;
  if (m_tick >= TICKS_IN_A_DAY)
  {
    m_tick = 0;
    nextDay();
  }
}

auto Calendar::str(const char separator) const noexcept -> std::string
{
  std::stringstream out;
  out << std::setfill('0') << std::setw(2);
  out << m_day << separator;
  out << std::setfill('0') << std::setw(2);
  out << m_month << separator;
  out << std::setfill('0') << std::setw(4);
  out << m_year;
  out << " (" << m_tick << ")";

  return out.str();
}

void Calendar::nextDay()
{
  ++m_day;
  if (m_day >= DAYS_IN_A_MONTH)
  {
    m_day = 0;
    nextMonth();
  }
}

void Calendar::nextMonth()
{
  ++m_month;
  if (m_month >= MONTHS_IN_A_YEAR)
  {
    m_month = 0;
    nextYear();
  }
}

void Calendar::nextYear()
{
  ++m_year;
}

} // namespace pharaoh
