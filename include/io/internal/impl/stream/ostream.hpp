#ifndef IO_INTERNAL_OSTREAM_IMPL_HPP
#define IO_INTERNAL_OSTREAM_IMPL_HPP
#include <io/internal/impl/stream/ios_base.hpp>
#include <io/tags.hpp>
// 3rd Party
// STL
#include <iostream>

template <> struct Operator::Impl<io::tags::stream::cout>
{
  template <typename... Args>
  static decltype(auto)
  invoke(Args&&... args)
  {
    return Impl<io::internal::impl::ios_base>::invoke(
        std::cout, std::forward<Args>(args)...);
  }
};

template <> struct Operator::Impl<io::tags::stream::wcout>
{
  template <typename... Args>
  static decltype(auto)
  invoke(Args&&... args)
  {
    return Impl<io::internal::impl::ios_base>::invoke(
        std::wcout, std::forward<Args>(args)...);
  }
};

template <> struct Operator::Impl<io::tags::stream::cerr>
{
  template <typename... Args>
  static decltype(auto)
  invoke(Args&&... args)
  {
    return Impl<io::internal::impl::ios_base>::invoke(
        std::cerr, std::forward<Args>(args)...);
  }
};

template <> struct Operator::Impl<io::tags::stream::wcerr>
{
  template <typename... Args>
  static decltype(auto)
  invoke(Args&&... args)
  {
    return Impl<io::internal::impl::ios_base>::invoke(
        std::wcerr, std::forward<Args>(args)...);
  }
};

template <> struct Operator::Impl<io::tags::stream::clog>
{
  template <typename... Args>
  static decltype(auto)
  invoke(Args&&... args)
  {
    return Impl<io::internal::impl::ios_base>::invoke(
        std::clog, std::forward<Args>(args)...);
  }
};

template <> struct Operator::Impl<io::tags::stream::wclog>
{
  template <typename... Args>
  static decltype(auto)
  invoke(Args&&... args)
  {
    return Impl<io::internal::impl::ios_base>::invoke(
        std::wclog, std::forward<Args>(args)...);
  }
};
#endif // IO_INTERNAL_OSTREAM_IMPL_HPP
