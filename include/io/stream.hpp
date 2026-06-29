#ifndef IO_STREAM_HPP
#define IO_STREAM_HPP
#include <io/internal/impl/stream.hpp>

namespace io
{
  namespace stream
  {
    template <typename LValue>
    decltype(auto)
    cin(LValue&& l_value)
    {
      Operator::operation<internal::impl::cin>(std::forward<LValue>(l_value));
    };

    template <typename LValue>
    decltype(auto)
    wcin(LValue&& l_value)
    {
      Operator::operation<internal::impl::wcin>(std::forward<LValue>(l_value));
    };

    template <typename... Args>
    decltype(auto)
    cout(Args&&... args)
    {
      return Operator::operation<internal::impl::cout>(
          std::forward<Args>(args)...);
    };

    template <typename... Args>
    decltype(auto)
    wcout(Args&&... args)
    {
      return Operator::operation<internal::impl::wcout>(
          std::forward<Args>(args)...);
    };

    template <typename... Args>
    decltype(auto)
    cerr(Args&&... args)
    {
      return Operator::operation<internal::impl::cerr>(
          std::forward<Args>(args)...);
    };

    template <typename... Args>
    decltype(auto)
    wcerr(Args&&... args)
    {
      return Operator::operation<internal::impl::wcerr>(
          std::forward<Args>(args)...);
    };

    template <typename... Args>
    decltype(auto)
    clog(Args&&... args)
    {
      return Operator::operation<internal::impl::clog>(
          std::forward<Args>(args)...);
    };

    template <typename... Args>
    decltype(auto)
    wclog(Args&&... args)
    {
      return Operator::operation<internal::impl::clog>(
          std::forward<Args>(args)...);
    };
  } // namespace stream
}; // namespace io
#endif // IO_STREAM_HPP
