#ifndef IO_OSTREAM_HPP
#define IO_OSTREAM_HPP
#include <io/internal/impl/stream/ostream.hpp>
#include <io/tags.hpp>

namespace io
{
  namespace stream
  {
    template <typename... Args>
    decltype(auto)
    cout(Args&&... args)
    {
      return Operator::operation<tags::stream::cout>(
          std::forward<Args>(args)...);
    }

    template <typename... Args>
    decltype(auto)
    wcout(Args&&... args)
    {
      return Operator::operation<tags::stream::wcout>(
          std::forward<Args>(args)...);
    }

    template <typename... Args>
    decltype(auto)
    cerr(Args&&... args)
    {
      return Operator::operation<tags::stream::cerr>(
          std::forward<Args>(args)...);
    }

    template <typename... Args>
    decltype(auto)
    wcerr(Args&&... args)
    {
      return Operator::operation<tags::stream::wcerr>(
          std::forward<Args>(args)...);
    }

    template <typename... Args>
    decltype(auto)
    clog(Args&&... args)
    {
      return Operator::operation<tags::stream::clog>(
          std::forward<Args>(args)...);
    }

    template <typename... Args>
    decltype(auto)
    wclog(Args&&... args)
    {
      return Operator::operation<tags::stream::wclog>(
          std::forward<Args>(args)...);
    }
  } // namespace stream
}; // namespace io
#endif // IO_OSTREAM_HPP
