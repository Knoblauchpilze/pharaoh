
#include "Calendar.hh"
#include <iomanip>

namespace pharaoh {

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

void Calendar::nextDay()
{
  increment(1, 0, 0);
}

void Calendar::nextMonth()
{
  increment(0, 1, 0);
}

void Calendar::nextYear()
{
  increment(0, 0, 1);
}

void Calendar::increment(int day, int month, int year) noexcept
{
  m_year += year;
  m_month += month;
  m_day += day;
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

  return out.str();
}

} // namespace pharaoh
