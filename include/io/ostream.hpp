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
    // Unformatted input
    template <typename OStreamTag = tags::stream::cout>
    decltype(auto)
    put(const typename OStreamTag::stream_type::char_type ch)
    {
      static_assert(OStreamTag::is_writable,
                    "io::stream::put(): stream must "
                    "be writable!");

      return Operator::operation<internal::impl::put, OStreamTag>(ch);
    }

    template <typename OStreamTag = tags::stream::cout>
    decltype(auto)
    write(const typename OStreamTag::stream_type::char_type* ch,
          const std::streamsize count)
    {
      static_assert(OStreamTag::is_writable,
                    "io::stream::write(): stream must "
                    "be writable!");

      return Operator::operation<internal::impl::write, OStreamTag>(ch, count);
    }

    // Positioning
    template <typename OStreamTag = tags::stream::cout>
    decltype(auto)
    tellp()
    {
      static_assert(OStreamTag::is_writable,
                    "io::stream::tellg(): stream must "
                    "be writable!");

      return Operator::operation<internal::impl::tellp, OStreamTag>();
    }

    template <typename OStreamTag = tags::stream::cout, typename... Args>
    decltype(auto)
    seekp(Args&&... args)
    {
      static_assert(OStreamTag::is_writable,
                    "io::stream::seekg(): stream must "
                    "be wriable!");

      return Operator::operation<internal::impl::seekp, OStreamTag>(
          std::forward<Args>(args)...);
    }

    // Miscellaneous
    template <typename OStreamTag = tags::stream::cout>
    decltype(auto)
    flush()
    {
      static_assert(OStreamTag::is_writable,
                    "io::stream::flush(): stream must "
                    "be wriable!");

      return Operator::operation<internal::impl::flush, OStreamTag>();
    }
  } // namespace stream
}; // namespace io
#endif // IO_OSTREAM_HPP
