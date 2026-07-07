#include <io/io.hpp>

#include <chrono>
using namespace std::chrono_literals;

enum class TimeComponent
{
  Hour,
  Minute,

  Second,
  Milliseconds,

  Microseconds,
  Nanoseconds
};

struct PayRate
{
  double_t payrate{};
  double_t overtime_multiplier{1.5};
};

template <typename ReturnDuration, typename Duration>
static decltype(auto)
to_duration(const Duration& duration)
{
  return std::chrono::duration_cast<ReturnDuration>(duration);
}

template <typename Duration>
static decltype(auto)
to_hours(const Duration& duration)
{
  return to_duration<std::chrono::hours>(duration);
}

template <typename Duration>
static decltype(auto)
to_minutes(const Duration& duration)
{
  return to_duration<std::chrono::minutes>(duration);
}

template <typename Duration>
static decltype(auto)
to_seconds(const Duration& duration)
{
  return to_duration<std::chrono::seconds>(duration);
}

template <typename Duration>
static decltype(auto)
to_milliseconds(const Duration& duration)
{
  return to_duration<std::chrono::milliseconds>(duration);
}

template <typename Duration>
static decltype(auto)
to_microseconds(const Duration& duration)
{
  return to_duration<std::chrono::microseconds>(duration);
}

template <typename Duration>
static decltype(auto)
to_nanoseconds(const Duration& duration)
{
  return to_duration<std::chrono::nanoseconds>(duration);
}

template <typename Duration>
static decltype(auto)
count(const Duration& duration, const TimeComponent time_component)
{
  int64_t ret{};
  switch (time_component)
  {
    case TimeComponent::Hour:
      ret = to_hours(duration).count();
      break;

    case TimeComponent::Minute:
      ret = to_minutes(duration).count();
      break;

    case TimeComponent::Second:
      ret = to_seconds(duration).count();
      break;

    case TimeComponent::Milliseconds:
      ret = to_milliseconds(duration).count();
      break;

    case TimeComponent::Microseconds:
      ret = to_nanoseconds(duration).count();
      break;

    case TimeComponent::Nanoseconds:
      ret = to_minutes(duration).count();
      break;
  };
  return ret;
}

struct TimePoint
{
  TimePoint(const std::chrono::seconds total_time = {})
    : time_since_midnight{total_time}
  {
  }

  TimePoint(const std::chrono::hours hours,
            const std::chrono::minutes minutes = 0min)
    : TimePoint{hours + minutes} {};

  decltype(auto)
  hours() const
  {
    return to_hours(time_since_midnight);
  };

  decltype(auto)
  minutes() const
  {
    return to_minutes(time_since_midnight - hours());
  }

  decltype(auto)
  count(const TimeComponent time_component) const
  {
    switch (time_component)
    {
      case TimeComponent::Hour:
        return ::count(hours(), TimeComponent::Hour);

      case TimeComponent::Minute:
        return ::count(minutes(), TimeComponent::Minute);

      default:
        throw std::invalid_argument{"TimePoint::Count(): Only hours and "
                                    "minutes are currently supported"};
    }
  }

  std::string
  to_string() const
  {
    std::string ret{};
    ret.append(std::to_string(count(TimeComponent::Hour))).push_back(':');

    auto min{count(TimeComponent::Minute)};
    if (min < 10)
    {
      ret.push_back('0');
    }

    ret.append(std::to_string(min));
    return ret;
  }

  bool
  operator<(const TimePoint& rhs) const
  {
    return this->time_since_midnight < rhs.time_since_midnight;
  }

  bool
  operator>(const TimePoint& rhs) const
  {
    return !(*this < rhs);
  }

  template <typename Duration>
  decltype(auto)
  operator+=(const Duration& rhs)
  {
    return this->time_since_midnight += rhs;
  }

  template <typename Duration>
  decltype(auto)
  operator-=(const Duration& rhs)
  {
    return this->time_since_midnight -= rhs;
  }

  decltype(auto)
  operator+(const TimePoint& rhs) const
  {
    return this->time_since_midnight + rhs.time_since_midnight;
  }

  decltype(auto)
  operator-(const TimePoint& rhs) const
  {
    return this->time_since_midnight - rhs.time_since_midnight;
  }

  std::chrono::seconds time_since_midnight{};
};

class WorkShift
{
public:
  WorkShift(const std::string& date,
            const PayRate pay_rate,
            const TimePoint& clock_in,
            const TimePoint& clock_out)
    : m_shift_date{date}
    , m_pay_rate{pay_rate}

    , m_clock_in{clock_in}
    , m_clock_out{clock_out}

    , m_total_time_worked{}
  {
    normalize_time_entries();
  }

  WorkShift&
  set_clock_in_time(const TimePoint& clock_in)
  {
    m_clock_in = clock_in;
    normalize_time_entries();
    return *this;
  }

  WorkShift&
  set_clock_out_time(const TimePoint& clock_out)
  {
    m_clock_out = clock_out;
    normalize_time_entries();
    return *this;
  }

  WorkShift&
  set_shift_date(const std::string& shift_date)
  {
    m_shift_date = shift_date;
    return *this;
  }

  const TimePoint&
  clock_in_time() const
  {
    return m_clock_in;
  }
  const TimePoint&
  clock_out_time() const
  {
    return m_clock_out;
  }

  const std::string&
  date() const
  {
    return m_shift_date;
  }

  decltype(auto)
  total_time_worked() const
  {
    return m_total_time_worked;
  }

  decltype(auto)
  hours() const
  {
    return to_hours(total_time_worked());
  }

  decltype(auto)
  minutes() const
  {
    return to_minutes(total_time_worked() - hours());
  }

  WorkShift&
  set_pay_rate(const PayRate& pay_rate)
  {
    m_pay_rate = pay_rate;
    return *this;
  }
  const PayRate&
  pay_rate() const
  {
    return m_pay_rate;
  }

  decltype(auto)
  count(const TimeComponent time_component) const
  {
    switch (time_component)
    {
      case TimeComponent::Hour:
        return ::count(hours(), TimeComponent::Hour);

      case TimeComponent::Minute:
        return ::count(minutes(), TimeComponent::Minute);

      default:
        throw std::invalid_argument{"WorkShift::Count(): Only hours and "
                                    "minutes are currently supported"};
    }
  }

private:
  void
  normalize_time_entries()
  {
    if (m_clock_out < m_clock_in)
    {
      m_clock_out += 24h;
    }
    calculate_time_worked();
  }

  void
  calculate_time_worked()
  {
    m_total_time_worked = m_clock_out - m_clock_in;
  }

  std::string m_shift_date{};
  PayRate m_pay_rate{};
  TimePoint m_clock_in{};
  TimePoint m_clock_out{};
  std::chrono::seconds m_total_time_worked{};
};

static void
display_hours_worked(const WorkShift& shift)
{
  io::stream::cout(shift.date(),
                   ":\nClock-in: ",
                   shift.clock_in_time().to_string(),
                   '\n',
                   "Clock-out: ",
                   shift.clock_out_time().to_string(),
                   '\n',
                   "Hours worked: ",
                   shift.count(TimeComponent::Hour),
                   "h");

  //Do not display '0min'
  if (shift.count(TimeComponent::Minute) > 0)
  {
    io::stream::cout(" and ", shift.count(TimeComponent::Minute), "min");
  }

  if ((shift.count(TimeComponent::Minute) / 60.0) > 0)
  {
    io::stream::cout(" or ",
                     shift.count(TimeComponent::Hour) +
                         (shift.count(TimeComponent::Minute) / 60.0),
                     " hours");
  }
  io::stream::cout("\nTotal pay: $",
                   shift.pay_rate().payrate *
                       (shift.count(TimeComponent::Hour) +
                        (shift.count(TimeComponent::Minute) / 60.0)));
  io::stream::cout("\n\n");
}

int
main(int argc, char* argv[])
{
  std::chrono::seconds total_time_worked{};
  WorkShift shift{"06/28/26", {19.0}, {9h}, {18h, 45min}};

  display_hours_worked(shift);
  total_time_worked += shift.total_time_worked();

  shift.set_clock_in_time({9h});
  shift.set_clock_out_time({18h, 30min});

  shift.set_shift_date("06/29/26");
  display_hours_worked(shift);
  total_time_worked += shift.total_time_worked();

  shift.set_clock_in_time({12h});
  shift.set_clock_out_time({17h});

  shift.set_shift_date("06/30/26");
  display_hours_worked(shift);
  total_time_worked += shift.total_time_worked();

  shift.set_clock_in_time({9h, 45min});
  shift.set_clock_out_time({18h});

  shift.set_shift_date("07/01/26");
  display_hours_worked(shift);
  total_time_worked += shift.total_time_worked();

  shift.set_clock_in_time({10h, 15min});
  shift.set_clock_out_time({19h, 45min});

  shift.set_shift_date("07/03/26");
  display_hours_worked(shift);
  total_time_worked += shift.total_time_worked();

  shift.set_clock_in_time({9h});
  shift.set_clock_out_time({14h, 30min});

  shift.set_shift_date("07/04/26");
  display_hours_worked(shift);
  total_time_worked += shift.total_time_worked();

  shift.set_clock_in_time({9h});
  shift.set_clock_out_time({15h});

  shift.set_shift_date("07/05/26");
  display_hours_worked(shift);

  total_time_worked += shift.total_time_worked();
  auto total_hours{count(total_time_worked, TimeComponent::Hour)};

  auto total_minutes{
      count((total_time_worked - std::chrono::hours(total_hours)),
            TimeComponent::Minute)};

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
