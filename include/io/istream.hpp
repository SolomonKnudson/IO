#ifndef IO_ISTREAM_HPP
#define IO_ISTREAM_HPP
#include <io/internal/impl/stream/istream.hpp>
#include <io/tags.hpp>

namespace io
{
  namespace stream
  {
    // Formatted input
    template <typename LValue>
    decltype(auto)
    cin(LValue&& l_value)
    {
      return Operator::operation<stream::cin>(std::forward<LValue>(l_value));
    }

    template <typename LValue>
    decltype(auto)
    wcin(LValue&& l_value)
    {
      return Operator::operation<stream::wcin>(std::forward<LValue>(l_value));
    }

    // Unformatted input
    template <typename IStreamTag = tags::stream::cin, typename... Args>
    decltype(auto)
    get(Args&&... args)
    {
      static_assert(IStreamTag::is_readable,
                    "io::stream::get(args...): stream must be readable!");

      return Operator::operation<internal::impl::get, IStreamTag>(
          std::forward<Args>(args)...);
    }

    template <typename IStreamTag = tags::stream::cin>
    decltype(auto)
    peek()
    {
      static_assert(IStreamTag::is_readable,
                    "io::stream::peek(): stream must be readable!");

      return Operator::operation<internal::impl::peek, IStreamTag>();
    }

    template <typename IStreamTag = tags::stream::cin>
    decltype(auto)
    unget()
    {
      static_assert(IStreamTag::is_readable,
                    "io::stream::unget(): stream must be readable!");

      return Operator::operation<internal::impl::unget, IStreamTag>();
    }

    template <typename IStreamTag = tags::stream::cin>
    decltype(auto)
    putback(typename IStreamTag::stream_type::char_type ch)
    {
      static_assert(IStreamTag::is_readable,
                    "io::stream::putback(char_type): stream must be readable!");

      return Operator::operation<internal::impl::putback, IStreamTag>(ch);
    }

    template <typename IStreamTag = tags::stream::cin, typename... Args>
    decltype(auto)
    getline(Args&&... args)
    {
      static_assert(IStreamTag::is_readable,
                    "io::stream::getline(args...): stream must be readable!");

      return Operator::operation<internal::impl::getline, IStreamTag>(
          std::forward<Args>(args)...);
    }

    template <typename IStreamTag = tags::stream::cin, typename... Args>
    decltype(auto)
    ignore(Args&&... args)
    {
      static_assert(IStreamTag::is_readable,
                    "io::stream::ignore(args...): stream must be readable!");

      return Operator::operation<internal::impl::getline, IStreamTag>(
          std::forward<Args>(args)...);
    }

    template <typename IStreamTag = tags::stream::cin>
    decltype(auto)
    read(typename IStreamTag::stream_type::char_type* ch,
         const std::streamsize count)
    {
      static_assert(IStreamTag::is_readable,
                    "io::stream::read(char_type, std::streamsize): stream must "
                    "be readable!");

      return Operator::operation<internal::impl::read, IStreamTag>(ch, count);
    }

    template <typename IStreamTag = tags::stream::cin>
    decltype(auto)
    readsome(typename IStreamTag::stream_type::char_type* ch,
             const std::streamsize count)
    {
      static_assert(
          IStreamTag::is_readable,
          "io::stream::readsome(char_type, std::streamsize): stream must "
          "be readable!");

      return Operator::operation<internal::impl::readsome, IStreamTag>(ch,
                                                                       count);
    }

    template <typename IStreamTag = tags::stream::cin>
    decltype(auto)
    gcount()
    {
      static_assert(IStreamTag::is_readable,
                    "io::stream::gcount(): stream must "
                    "be readable!");

      return Operator::operation<internal::impl::gcount, IStreamTag>();
    }

    // Positioning
    template <typename IStreamTag = tags::stream::cin>
    decltype(auto)
    tellg()
    {
      static_assert(IStreamTag::is_readable,
                    "io::stream::tellg(): stream must "
                    "be readable!");

      return Operator::operation<internal::impl::tellg, IStreamTag>();
    }

    template <typename IStreamTag = tags::stream::cin, typename... Args>
    decltype(auto)
    seekg(Args&&... args)
    {
      static_assert(IStreamTag::is_readable,
                    "io::stream::seekg(): stream must "
                    "be readable!");

      return Operator::operation<internal::impl::seekg, IStreamTag>(
          std::forward<Args>(args)...);
    }

    // Miscellaneous
    template <typename IStreamTag = tags::stream::cin>
    decltype(auto)
    sync()
    {
      static_assert(IStreamTag::is_readable,
                    "io::stream::seekg(): stream must "
                    "be readable!");

      return Operator::operation<internal::impl::sync, IStreamTag>();
    }
  } // namespace stream
}; // namespace io
#endif // IO_ISTREAM_HPP
