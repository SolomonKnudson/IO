#include <io/io.hpp>

//3rd party
#include <STLConvenience/chrono.hpp>
//STL
#include <cmath>

using namespace std::chrono_literals;

struct PayRate
{
  double_t payrate{};
  double_t overtime_multiplier{1.5};
};

struct TimeComponent
{
  std::chrono::nanoseconds
  total_time() const
  {
    return STLC::chrono::to_nanoseconds(
        hours + minutes + seconds + milliseconds + microseconds + nanoseconds);
  }

  std::chrono::hours hours{};
  std::chrono::minutes minutes{};

  std::chrono::seconds seconds{};
  std::chrono::milliseconds milliseconds{};

  std::chrono::microseconds microseconds{};
  std::chrono::nanoseconds nanoseconds{};
};

enum class TimePercision
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
  explicit TimePoint(const TimeComponent& time = {})
    : m_time_since_midnight{time.total_time()}
    , m_display_percision{deduce_time_display_percision(time)}
  {
  }

  explicit TimePoint(const TimeComponent& time, const TimePercision percision)
    : m_time_since_midnight{time.total_time()}
    , m_display_percision{percision}
  {
  }

  TimePoint&
  set_time(const TimeComponent& time)
  {
    m_time_since_midnight = time.total_time();
    return *this;
  }

  TimePoint&
  set_percision(TimePercision percision)
  {
    m_display_percision = percision;
    return *this;
  }

  TimePercision
  percision() const
  {
    return m_display_percision;
  }

  TimeComponent
  time() const
  {
    return {hours(),
            minutes(),
            seconds(),
            milliseconds(),
            microseconds(),
            nanoseconds()};
  }

  template <typename Duration>
  TimePoint&
  add_time(const Duration& duration)
  {
    m_time_since_midnight += duration;
    return *this;
  }

  template <typename Duration>
  TimePoint&
  remove_time(const Duration& duration)
  {
    m_time_since_midnight -= duration;
    return *this;
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
  to_string() const
  {
    std::string ret{};
    ret.append(std::to_string(hours().count())).push_back(':');

    auto min{minutes().count()};
    if (min < 10)
    {
      ret.push_back('0');
    }
    ret.append(std::to_string(min));

    if (m_display_percision != TimePercision::minutes)
    {
      ret.push_back(':');
      auto sec{seconds().count()};
      if (sec < 10)
      {
        ret.append("0");
      }
      ret.append(std::to_string(sec)).push_back('.');

      if (m_display_percision != TimePercision::seconds)
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

        if (m_display_percision != TimePercision::milliseconds)
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

          if (m_display_percision != TimePercision::microseconds)
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

  template <typename Rep, typename Period>
  void
  operator+=(const std::chrono::duration<Rep, Period>& rhs)
  {
    this->m_time_since_midnight += rhs;
  }

  template <typename Rep, typename Period>
  void
  operator-=(const std::chrono::duration<Rep, Period>& rhs)
  {
    this->m_time_since_midnight -= rhs;
  }

  void
  operator+=(const TimePoint& rhs)
  {
    this->m_time_since_midnight += rhs.m_time_since_midnight;
  }

  void
  operator-=(const TimePoint& rhs)
  {
    this->m_time_since_midnight -= rhs.m_time_since_midnight;
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
  TimePercision
  deduce_time_display_percision(const TimeComponent& time)
  {
    TimePercision ret{TimePercision::minutes};
    if (time.nanoseconds.count())
    {
      ret = TimePercision::nanoseconds;
    }
    else if (time.microseconds.count())
    {
      ret = TimePercision::microseconds;
    }
    else if (time.milliseconds.count())
    {
      ret = TimePercision::milliseconds;
    }
    else if (time.seconds.count())
    {
      ret = TimePercision::seconds;
    }
    return ret;
  }

  std::chrono::nanoseconds m_time_since_midnight{};
  TimePercision m_display_percision{};
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
  explicit WorkShift(const WorkShiftInfo& info = {})
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

  double_t minutes{static_cast<double_t>(shift.minutes().count())};
  double_t time_worked_decimal{static_cast<double_t>(hours) + (minutes / 60.0)};

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
                   TimePoint{TimeComponent{15h, 22min, 55s, 15ms, 5us, 20ns}}
                       .remove_time(1ns)
                       .to_string(),
                   "\n\n");

  std::chrono::seconds total_time_worked{};
  WorkShift shift{{"06/28/26",
                   {20.5},
                   TimePoint{TimeComponent{9h}},
                   TimePoint{TimeComponent{18h, 45min}}}};

  display_hours_worked(shift);
  total_time_worked += shift.total_time_worked<std::chrono::seconds>();

  shift.set_clock_in_time(TimePoint{TimeComponent{9h}});
  shift.set_clock_out_time(TimePoint{TimeComponent{18h, 30min}});

  shift.set_shift_date("06/29/26");
  display_hours_worked(shift);
  total_time_worked += shift.total_time_worked<std::chrono::seconds>();

  shift.set_clock_in_time(TimePoint{TimeComponent{12h}});
  shift.set_clock_out_time(TimePoint{TimeComponent{17h}});

  shift.set_shift_date("06/30/26");
  display_hours_worked(shift);
  total_time_worked += shift.total_time_worked<std::chrono::seconds>();

  shift.set_clock_in_time(TimePoint{TimeComponent{9h, 45min}});
  shift.set_clock_out_time(TimePoint{TimeComponent{18h}});

  shift.set_shift_date("07/01/26");
  display_hours_worked(shift);
  total_time_worked += shift.total_time_worked<std::chrono::seconds>();

  shift.set_clock_in_time(TimePoint{TimeComponent{10h, 15min}});
  shift.set_clock_out_time(TimePoint{TimeComponent{19h, 45min}});

  shift.set_shift_date("07/03/26");
  display_hours_worked(shift);
  total_time_worked += shift.total_time_worked<std::chrono::seconds>();

  shift.set_clock_in_time(TimePoint{TimeComponent{9h}});
  shift.set_clock_out_time(TimePoint{TimeComponent{14h, 30min}});

  shift.set_shift_date("07/04/26");
  display_hours_worked(shift);
  total_time_worked += shift.total_time_worked<std::chrono::seconds>();

  shift.set_clock_in_time(TimePoint{TimeComponent{9h}});
  shift.set_clock_out_time(TimePoint{TimeComponent{15h}});

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
                       static_cast<double_t>(total_hours) +
                           (static_cast<double_t>(total_minutes) / 60.0),
                       " hours");
    }

    double_t total_base_pay{shift.pay_rate().payrate * 40};
    double_t overtime_hours{(static_cast<double_t>(total_hours) +
                             (static_cast<double_t>(total_minutes) / 60.0)) -
                            40.0};
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
