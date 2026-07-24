#ifndef IO_INTERNAL_IOS_BASE_IMPL_HPP
#define IO_INTERNAL_IOS_BASE_IMPL_HPP
#include <io/internal/concepts.hpp>
#include <io/internal/impl/tags.hpp>

template <> struct Operator::Impl<io::internal::impl::ios_base>
{
  template <typename IStream, typename LValue>
  OPERATOR_CREATE_REQUIRES(
      io::internal::concepts::HasStdStreamInsertion<IStream, LValue>)
  static OPERATOR_AUTO_RETURN invoke(IStream& in_stream, LValue&& l_value)
      OPERATOR_CREATE_TRAILING_RETURN(
          decltype(in_stream >> util::deref(std::forward<LValue>(l_value))))
  {
    in_stream >> Operator::util::deref(std::forward<LValue>(l_value));
    return in_stream;
  }

  template <typename OStream, typename... OStreamArgs>
  OPERATOR_CREATE_REQUIRES(
      io::internal::concepts::HasStdStreamOutsertion<OStream, OStreamArgs...>)
  static OPERATOR_AUTO_RETURN invoke(OStream& out_stream, OStreamArgs&&... args)
      OPERATOR_CREATE_TRAILING_RETURN(
          decltype(((out_stream << std::forward<OStreamArgs>(args)), ...)))
  {
    static_assert(sizeof...(OStreamArgs) > 0,
                  "Operator::Impl<io::internal::impl::ios_base>(args...): "
                  "ostream must be called with at least one value!");

    ((out_stream << std::forward<OStreamArgs>(args)), ...);
    return out_stream;
  }
};

// Formatting
// TODO:
// copyfmt
// fill

template <> struct Operator::Impl<io::internal::impl::flags>
{
  template <typename StreamTag>
  static decltype(auto)
  invoke()
  {
    return StreamTag::stream().flags();
  }

  template <typename StreamTag>
  static decltype(auto)
  invoke(const std::ios_base::fmtflags flags)
  {
    return StreamTag::stream().flags(flags);
  }
};

template <> struct Operator::Impl<io::internal::impl::setf>
{
  template <typename StreamTag>
  static decltype(auto)
  invoke(const std::ios_base::fmtflags flags)
  {
    return StreamTag::stream().setf(flags);
  }

  template <typename StreamTag>
  static decltype(auto)
  invoke(const std::ios_base::fmtflags flags,
         const std::ios_base::fmtflags mask)
  {
    return StreamTag::stream().setf(flags, mask);
  }
};

template <> struct Operator::Impl<io::internal::impl::unsetf>
{
  template <typename StreamTag>
  static decltype(auto)
  invoke(const std::ios_base::fmtflags flags)
  {
    return StreamTag::stream().unsetf(flags);
  }
};

template <> struct Operator::Impl<io::internal::impl::precision>
{
  template <typename StreamTag>
  static decltype(auto)
  invoke()
  {
    return StreamTag::stream().precision();
  }

  template <typename StreamTag>
  static decltype(auto)
  invoke(const std::streamsize new_precision)
  {
    return StreamTag::stream().precision(new_precision);
  }
};

template <> struct Operator::Impl<io::internal::impl::width>
{
  template <typename StreamTag>
  static decltype(auto)
  invoke()
  {
    return StreamTag::stream().width();
  }

  template <typename StreamTag>
  static decltype(auto)
  invoke(const std::streamsize new_width)
  {
    return StreamTag::stream().width(new_width);
  }
};

// TODO:
// State
// good
// eof
// fail
// bad
// rdstate
// setstate
// clear

// Locales
template <> struct Operator::Impl<io::internal::impl::imbue>
{
  template <typename StreamTag>
  static decltype(auto)
  invoke(const std::locale& loc)
  {
    return StreamTag::stream().imbue(loc);
  }
};

template <> struct Operator::Impl<io::internal::impl::getloc>
{
  template <typename StreamTag>
  static decltype(auto)
  invoke()
  {
    return StreamTag::stream().getloc();
  }
};

// Internal extensible array
template <> struct Operator::Impl<io::internal::impl::iword>
{
  template <typename StreamTag>
  static decltype(auto)
  invoke(const int32_t index)
  {
    return StreamTag::stream().iword(index);
  }
};

template <> struct Operator::Impl<io::internal::impl::pword>
{
  template <typename StreamTag>
  static decltype(auto)
  invoke(const int32_t index)
  {
    return StreamTag::stream().pword(index);
  }
};

// Miscellaneous
template <> struct Operator::Impl<io::internal::impl::register_callback>
{
  template <typename StreamTag>
  static decltype(auto)
  invoke(std::ios_base::event_callback function, const int32_t index)
  {
    return StreamTag::stream().register_callback(function, index);
  }
};

// TODO:
// execptions
// rdbuf
// tie
// narrow
// widen
#endif // IO_INTERNAL_IOS_BASE_IMPL_HPP
