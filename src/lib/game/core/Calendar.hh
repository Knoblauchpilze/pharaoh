
#pragma once

#include <string>

namespace pharaoh {

class Calendar
{
  public:
  Calendar() noexcept = default;
  Calendar(int year, int month, int day) noexcept;

  auto y() const noexcept -> int;
  auto m() const noexcept -> int;
  auto d() const noexcept -> int;

  void nextDay();
  void nextMonth();
  void nextYear();
  void increment(int day, int month, int year) noexcept;

  auto str(const char separator = '/') const noexcept -> std::string;

  private:
  int m_year{1};
  int m_month{1};
  int m_day{1};
};

} // namespace pharaoh
