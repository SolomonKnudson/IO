#ifndef IO_STREAM_HPP
#define IO_STREAM_HPP
#include <io/internal/internal.hpp>

namespace io
{
  namespace stream
  {
    template <typename LValue>
    decltype(auto)
    cin(LValue&& l_value)
    {
      return internal::read<internal::impl::cin>(std::forward<LValue>(l_value));
    }

    template <typename LValue>
    decltype(auto)
    wcin(LValue&& l_value)
    {
      return internal::read<internal::impl::wcin>(
          std::forward<LValue>(l_value));
    }

    template <typename... Args>
    decltype(auto)
    cout(Args&&... args)
    {
      return internal::write<internal::impl::cout>(std::forward<Args>(args)...);
    }

    template <typename... Args>
    decltype(auto)
    wcout(Args&&... args)
    {
      return internal::write<internal::impl::wcout>(
          std::forward<Args>(args)...);
    }

    template <typename... Args>
    decltype(auto)
    cerr(Args&&... args)
    {
      return internal::write<internal::impl::cerr>(std::forward<Args>(args)...);
    }

    template <typename... Args>
    decltype(auto)
    wcerr(Args&&... args)
    {
      return internal::write<internal::impl::wcerr>(
          std::forward<Args>(args)...);
    }

    template <typename... Args>
    decltype(auto)
    clog(Args&&... args)
    {
      return internal::write<internal::impl::clog>(std::forward<Args>(args)...);
    }

    template <typename... Args>
    decltype(auto)
    wclog(Args&&... args)
    {
      return internal::write<internal::impl::wclog>(
          std::forward<Args>(args)...);
    }
  } // namespace stream
}; // namespace io
#endif // IO_STREAM_HPP
