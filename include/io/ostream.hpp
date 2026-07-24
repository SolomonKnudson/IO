#ifndef IO_OSTREAM_HPP
#define IO_OSTREAM_HPP
#include <io/internal/impl/stream/ostream.hpp>
#include <io/ios_base.hpp>
#include <io/tags.hpp>

namespace io
{
  namespace stream
  {
    template <typename... Args>
    decltype(auto)
    cout(Args&&... args)
    {
      return Operator::operation<stream::Cout>(std::forward<Args>(args)...);
    }

    template <typename... Args>
    decltype(auto)
    wcout(Args&&... args)
    {
      return Operator::operation<stream::WCout>(std::forward<Args>(args)...);
    }

    template <typename... Args>
    decltype(auto)
    cerr(Args&&... args)
    {
      return Operator::operation<stream::Cerr>(std::forward<Args>(args)...);
    }

    template <typename... Args>
    decltype(auto)
    wcerr(Args&&... args)
    {
      return Operator::operation<stream::WCerr>(std::forward<Args>(args)...);
    }

    template <typename... Args>
    decltype(auto)
    clog(Args&&... args)
    {
      return Operator::operation<stream::Clog>(std::forward<Args>(args)...);
    }

    template <typename... Args>
    decltype(auto)
    wclog(Args&&... args)
    {
      return Operator::operation<stream::WClog>(std::forward<Args>(args)...);
    }
    // Unformatted input
    template <typename OStreamTag = stream::Cout>
    decltype(auto)
    put(const typename OStreamTag::stream_type::char_type ch)
    {
      static_assert(OStreamTag::is_writable,
                    "io::stream::put(): stream must "
                    "be writable!");

      return Operator::operation<internal::impl::put, OStreamTag>(ch);
    }

    template <typename OStreamTag = stream::Cout>
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
    template <typename OStreamTag = stream::Cout>
    decltype(auto)
    tellp()
    {
      static_assert(OStreamTag::is_writable,
                    "io::stream::tellg(): stream must "
                    "be writable!");

      return Operator::operation<internal::impl::tellp, OStreamTag>();
    }

    template <typename OStreamTag = stream::Cout, typename... Args>
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
    template <typename OStreamTag = stream::Cout>
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
