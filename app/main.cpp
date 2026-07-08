#include <io/io.hpp>

#include <STLConvenience/chrono.hpp>
using namespace std::chrono_literals;

struct PayRate
{
  double_t payrate{};
  double_t overtime_multiplier{1.5};
};

struct Time
{
  std::chrono::hours hours{};
  std::chrono::minutes minutes{};

  std::chrono::seconds seconds{};
  std::chrono::milliseconds milliseconds{};

  std::chrono::microseconds microseconds{};
  std::chrono::nanoseconds nanoseconds{};
};

enum class TimeDisplayPercision
{
  minutes,
  seconds,
  milliseconds,
  microseconds,
  nanoseconds
};

class TimePoint
{
public:
  TimePoint(const Time& time = {})
    : m_time_since_midnight{STLC::chrono::to_nanoseconds(
          time.hours + time.minutes + time.seconds + time.milliseconds +
          time.microseconds + time.nanoseconds)}
  {
  }

  template <typename ReturnDuration>
  ReturnDuration
  to_duration() const
  {
    return STLC::chrono::to_duration<ReturnDuration>(m_time_since_midnight);
  };

  std::chrono::hours
  hours() const
  {
    return to_duration<std::chrono::hours>();
  };

  std::chrono::minutes
  minutes() const
  {
    return STLC::chrono::to_minutes(m_time_since_midnight %
                                    STLC::chrono::make_hours(1));
  }

  std::chrono::seconds
  seconds() const
  {
    return STLC::chrono::to_seconds(m_time_since_midnight %
                                    STLC::chrono::make_minutes(1));
  }

  std::chrono::milliseconds
  milliseconds() const
  {
    return STLC::chrono::to_milliseconds(m_time_since_midnight %
                                         STLC::chrono::make_seconds(1));
  }

  std::chrono::microseconds
  microseconds() const
  {
    return STLC::chrono::to_microseconds(m_time_since_midnight %
                                         STLC::chrono::make_milliseconds(1));
  }

  std::chrono::nanoseconds
  nanoseconds() const
  {
    return STLC::chrono::to_nanoseconds(m_time_since_midnight %
                                        STLC::chrono::make_microseconds(1));
  }

  std::string
  to_string(const TimeDisplayPercision percision =
                TimeDisplayPercision::minutes) const
  {
    std::string ret{};
    ret.append(std::to_string(hours().count())).push_back(':');

    auto min{minutes().count()};
    if (min < 10)
    {
      ret.push_back('0');
    }
    ret.append(std::to_string(min));

    if (percision != TimeDisplayPercision::minutes)
    {
      ret.push_back(':');
      auto sec{seconds().count()};
      if (sec < 10)
      {
        ret.append("0");
      }
      ret.append(std::to_string(sec)).push_back('.');

      if (percision != TimeDisplayPercision::seconds)
      {
        auto millisec{milliseconds().count()};
        if (millisec)
        {
          (millisec < 10 ? ret.append("00") : ret.append("0"));
          ret.append(std::to_string(millisec));
        }
        else
        {
          ret.append("000");
        }

        if (percision != TimeDisplayPercision::milliseconds)
        {
          auto microsec{microseconds().count()};
          if (microsec)
          {
            (microsec < 10 ? ret.append("00") : ret.append("0"));
            ret.append(std::to_string(microsec));
          }
          else
          {
            ret.append("000");
          }

          if (percision != TimeDisplayPercision::microseconds)
          {
            auto nanosec{nanoseconds().count()};
            if (nanosec)
            {
              (nanosec < 10 ? ret.append("00") : ret.append("0"));
              ret.append(std::to_string(nanosec));
            }
            else
            {
              ret.append("000");
            }
            ret.append("ns");
          }
        }
      }
    }
    return ret;
  }

  bool
  operator<(const TimePoint& rhs) const
  {
    return this->m_time_since_midnight < rhs.m_time_since_midnight;
  }

  bool
  operator>(const TimePoint& rhs) const
  {
    return !(*this < rhs);
  }

  template <typename Duration>
  void
  operator+=(const Duration& rhs)
  {
    this->m_time_since_midnight += rhs;
  }

  template <typename Duration>
  void
  operator-=(const Duration& rhs)
  {
    this->m_time_since_midnight -= rhs;
  }

  std::chrono::nanoseconds
  operator+(const TimePoint& rhs) const
  {
    return this->m_time_since_midnight + rhs.m_time_since_midnight;
  }

  std::chrono::nanoseconds
  operator-(const TimePoint& rhs) const
  {
    return this->m_time_since_midnight - rhs.m_time_since_midnight;
  }

private:
  std::chrono::nanoseconds m_time_since_midnight{};
};

struct WorkShiftInfo
{
  std::string date{};
  PayRate pay_rate{};

  TimePoint clock_in{};
  TimePoint clock_out{};
};

class WorkShift
{
public:
  WorkShift(const WorkShiftInfo& info = {})
    : m_info{info}
    , m_total_time_worked{}
  {
    calculate_time_worked();
  }

  WorkShift&
  set_clock_in_time(const TimePoint& clock_in)
  {
    m_info.clock_in = clock_in;
    calculate_time_worked();
    return *this;
  }

  WorkShift&
  set_clock_out_time(const TimePoint& clock_out)
  {
    m_info.clock_out = clock_out;
    calculate_time_worked();
    return *this;
  }

  WorkShift&
  set_shift_date(const std::string& shift_date)
  {
    m_info.date = shift_date;
    return *this;
  }

  const TimePoint&
  clock_in_time() const
  {
    return m_info.clock_in;
  }
  const TimePoint&
  clock_out_time() const
  {
    return m_info.clock_out;
  }

  const std::string&
  date() const
  {
    return m_info.date;
  }

  template <typename ReturnDuration>
  ReturnDuration
  total_time_worked() const
  {
    return STLC::chrono::to_duration<ReturnDuration>(m_total_time_worked);
  }

  std::chrono::hours
  hours() const
  {
    return total_time_worked<std::chrono::hours>();
  }

  std::chrono::minutes
  minutes() const
  {
    return STLC::chrono::to_minutes(total_time_worked<std::chrono::seconds>() -
                                    hours());
  }

  WorkShift&
  set_pay_rate(const PayRate& pay_rate)
  {
    m_info.pay_rate = pay_rate;
    return *this;
  }

  const PayRate&
  pay_rate() const
  {
    return m_info.pay_rate;
  }

private:
  void
  calculate_time_worked()
  {
    m_total_time_worked = m_info.clock_out - m_info.clock_in;
    if (m_info.clock_out < m_info.clock_in)
    {
      m_total_time_worked += STLC::chrono::make_hours(24);
    }
  }

  WorkShiftInfo m_info{};
  std::chrono::nanoseconds m_total_time_worked{};
};

static void
display_hours_worked(const WorkShift& shift)
{
  auto hours{shift.hours().count()};
  io::stream::cout(shift.date(),
                   ":\nClock-in: ",
                   shift.clock_in_time().to_string(),
                   "\nClock-out : ",
                   shift.clock_out_time().to_string(),
                   "\nHours worked : ",
                   hours,
                   "h");

  auto minutes{shift.minutes().count()};
  auto time_worked_decimal{hours + (minutes / 60.0)};

  //Do not display '0min'
  if (minutes > 0)
  {
    io::stream::cout(" and ", minutes, "min");
  }

  if ((minutes / 60.0) > 0)
  {
    io::stream::cout(" or ", time_worked_decimal, " hours");
  }

  io::stream::cout("\nPay rate: $",
                   shift.pay_rate().payrate,
                   "\nTotal pay: $",
                   shift.pay_rate().payrate * time_worked_decimal,
                   "\n\n");
}

int
main(int argc, char* argv[])
{
  io::stream::cout("TimePoint test: ",
                   TimePoint{Time{15h, 22min, 55s, 15ms, 5us, 20ns}}.to_string(
                       TimeDisplayPercision::nanoseconds),
                   "\n\n");

  display_hours_worked(
      {{"Overnight test", {19.0}, Time{15h}, Time{3h, 30min}}});
  std::chrono::seconds total_time_worked{};
  WorkShift shift{{"06/28/26", {19.0}, Time{9h}, Time{18h, 45min}}};

  display_hours_worked(shift);
  total_time_worked += shift.total_time_worked<std::chrono::seconds>();

  shift.set_clock_in_time(Time{9h});
  shift.set_clock_out_time(Time{18h, 30min});

  shift.set_shift_date("06/29/26");
  display_hours_worked(shift);
  total_time_worked += shift.total_time_worked<std::chrono::seconds>();

  shift.set_clock_in_time(Time{12h});
  shift.set_clock_out_time(Time{17h});

  shift.set_shift_date("06/30/26");
  display_hours_worked(shift);
  total_time_worked += shift.total_time_worked<std::chrono::seconds>();

  shift.set_clock_in_time(Time{9h, 45min});
  shift.set_clock_out_time(Time{18h});

  shift.set_shift_date("07/01/26");
  display_hours_worked(shift);
  total_time_worked += shift.total_time_worked<std::chrono::seconds>();

  shift.set_clock_in_time(Time{10h, 15min});
  shift.set_clock_out_time(Time{19h, 45min});

  shift.set_shift_date("07/03/26");
  display_hours_worked(shift);
  total_time_worked += shift.total_time_worked<std::chrono::seconds>();

  shift.set_clock_in_time(Time{9h});
  shift.set_clock_out_time(Time{14h, 30min});

  shift.set_shift_date("07/04/26");
  display_hours_worked(shift);
  total_time_worked += shift.total_time_worked<std::chrono::seconds>();

  shift.set_clock_in_time(Time{9h});
  shift.set_clock_out_time(Time{15h});

  shift.set_shift_date("07/05/26");
  display_hours_worked(shift);

  total_time_worked += shift.total_time_worked<std::chrono::seconds>();
  auto total_hours{STLC::chrono::to_hours(total_time_worked).count()};

  auto total_minutes{
      STLC::chrono::to_minutes(
          (total_time_worked - STLC::chrono::make_hours(total_hours)))
          .count()};

  if ((total_hours > 0) || (total_minutes > 0))
  {
    io::stream::cout("Total time worked: ");
    if (total_hours)
    {
      io::stream::cout(total_hours, "h ");
    }

    if (total_minutes)
    {
      io::stream::cout(total_minutes,
                       "min or ",
                       total_hours + (total_minutes / 60.0),
                       " hours");
    }

    double_t total_base_pay{shift.pay_rate().payrate * 40};
    double_t overtime_hours{(total_hours + (total_minutes / 60.0)) - 40};
    double_t total_overtime_pay{
        (shift.pay_rate().payrate * shift.pay_rate().overtime_multiplier) *
        overtime_hours};

    io::stream::cout("\nTotal overtime hours: ", overtime_hours, '\n');
    io::stream::cout("\nTotal base pay: $", total_base_pay);

    io::stream::cout("\nTotal overtime pay: $", total_overtime_pay);
    io::stream::cout("\n\nTotal pay: $", total_base_pay + total_overtime_pay);
  }
  return 0;
}
