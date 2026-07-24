#ifndef IO_INTERNAL_OSTREAM_IMPL_HPP
#define IO_INTERNAL_OSTREAM_IMPL_HPP
#include <io/internal/impl/stream/ios_base.hpp>
#include <io/tags.hpp>

template <> struct Operator::Impl<io::stream::Cout>
{
  template <typename... Args>
  static decltype(auto)
  invoke(Args&&... args)
  {
    return Impl<io::internal::impl::ios_base>::invoke(
        io::stream::Cout::stream(), std::forward<Args>(args)...);
  }
};

template <> struct Operator::Impl<io::stream::WCout>
{
  template <typename... Args>
  static decltype(auto)
  invoke(Args&&... args)
  {
    return Impl<io::internal::impl::ios_base>::invoke(
        io::stream::WCout::stream(), std::forward<Args>(args)...);
  }
};

template <> struct Operator::Impl<io::stream::Cerr>
{
  template <typename... Args>
  static decltype(auto)
  invoke(Args&&... args)
  {
    return Impl<io::internal::impl::ios_base>::invoke(
        io::stream::Cerr::stream(), std::forward<Args>(args)...);
  }
};

template <> struct Operator::Impl<io::stream::WCerr>
{
  template <typename... Args>
  static decltype(auto)
  invoke(Args&&... args)
  {
    return Impl<io::internal::impl::ios_base>::invoke(
        io::stream::WCerr::stream(), std::forward<Args>(args)...);
  }
};

template <> struct Operator::Impl<io::stream::Clog>
{
  template <typename... Args>
  static decltype(auto)
  invoke(Args&&... args)
  {
    return Impl<io::internal::impl::ios_base>::invoke(
        io::stream::Clog::stream(), std::forward<Args>(args)...);
  }
};

template <> struct Operator::Impl<io::stream::WClog>
{
  template <typename... Args>
  static decltype(auto)
  invoke(Args&&... args)
  {
    return Impl<io::internal::impl::ios_base>::invoke(
        io::stream::WClog::stream(), std::forward<Args>(args)...);
  }
};

// Unformatted input
template <> struct Operator::Impl<io::internal::impl::put>
{
  template <typename OStreamTag>
  static decltype(auto)
  invoke(const typename OStreamTag::stream_type::char_type ch)
  {
    return OStreamTag::stream().put(ch);
  }
};

template <> struct Operator::Impl<io::internal::impl::write>
{
  template <typename OStreamTag>
  static decltype(auto)
  invoke(const typename OStreamTag::stream_type::char_type* ch,
         const std::streamsize count)
  {
    return OStreamTag::stream().write(ch, count);
  }
};

// Positioning
template <> struct Operator::Impl<io::internal::impl::tellp>
{
  template <typename OStreamTag>
  static typename OStreamTag::stream_type::pos_type
  invoke()
  {
    return OStreamTag::stream().tellp();
  }
};

template <> struct Operator::Impl<io::internal::impl::seekp>
{
  template <typename OStreamTag>
  static decltype(auto)
  invoke(const typename OStreamTag::stream_type::pos_type pos)
  {
    return OStreamTag::stream().seekp(pos);
  }

  template <typename OStreamTag>
  static decltype(auto)
  invoke(const typename OStreamTag::stream_type::off_type off,
         std::ios_base::seekdir& dir)
  {
    return OStreamTag::stream().seekp(off, dir);
  }
};

// Miscellaneous
template <> struct Operator::Impl<io::internal::impl::flush>
{
  template <typename OStreamTag>
  static decltype(auto)
  invoke()
  {
    return OStreamTag::stream().flush();
  }
};
#endif // IO_INTERNAL_OSTREAM_IMPL_HPP
