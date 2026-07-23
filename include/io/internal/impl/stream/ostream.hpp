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
#endif // IO_INTERNAL_OSTREAM_IMPL_HPP
