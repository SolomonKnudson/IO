#ifndef IO_INTERNAL_OSTREAM_IMPL_HPP
#define IO_INTERNAL_OSTREAM_IMPL_HPP
#include <io/internal/impl/stream/ios_base.hpp>
#include <io/tags.hpp>

template <> struct Operator::Impl<io::tags::stream::cout>
{
  template <typename... Args>
  static decltype(auto)
  invoke(Args&&... args)
  {
    return Impl<io::internal::impl::ios_base>::invoke(
        io::tags::stream::cout::stream(), std::forward<Args>(args)...);
  }
};

template <> struct Operator::Impl<io::tags::stream::wcout>
{
  template <typename... Args>
  static decltype(auto)
  invoke(Args&&... args)
  {
    return Impl<io::internal::impl::ios_base>::invoke(
        io::tags::stream::wcout::stream(), std::forward<Args>(args)...);
  }
};

template <> struct Operator::Impl<io::tags::stream::cerr>
{
  template <typename... Args>
  static decltype(auto)
  invoke(Args&&... args)
  {
    return Impl<io::internal::impl::ios_base>::invoke(
        io::tags::stream::cerr::stream(), std::forward<Args>(args)...);
  }
};

template <> struct Operator::Impl<io::tags::stream::wcerr>
{
  template <typename... Args>
  static decltype(auto)
  invoke(Args&&... args)
  {
    return Impl<io::internal::impl::ios_base>::invoke(
        io::tags::stream::wcerr::stream(), std::forward<Args>(args)...);
  }
};

template <> struct Operator::Impl<io::tags::stream::clog>
{
  template <typename... Args>
  static decltype(auto)
  invoke(Args&&... args)
  {
    return Impl<io::internal::impl::ios_base>::invoke(
        io::tags::stream::clog::stream(), std::forward<Args>(args)...);
  }
};

template <> struct Operator::Impl<io::tags::stream::wclog>
{
  template <typename... Args>
  static decltype(auto)
  invoke(Args&&... args)
  {
    return Impl<io::internal::impl::ios_base>::invoke(
        io::tags::stream::wclog::stream(), std::forward<Args>(args)...);
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
