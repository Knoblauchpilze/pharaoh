
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
  auto t() const noexcept -> int;

  void tick();

  auto str(const char separator = '/') const noexcept -> std::string;

  private:
  int m_year{1};
  int m_month{1};
  int m_day{1};
  int m_tick{0};

  void nextDay();
  void nextMonth();
  void nextYear();
};

} // namespace pharaoh
