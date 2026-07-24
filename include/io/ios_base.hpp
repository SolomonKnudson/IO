#ifndef IO_IOBASE_HPP
#define IO_IOBASE_HPP
#include <io/internal/impl/stream/ios_base.hpp>

namespace io
{
  namespace stream
  {
    // Formatting
    template <typename StreamTag, typename... Args>
    decltype(auto)
    flags(Args&&... args)
    {
      return Operator::operation<internal::impl::flags, StreamTag>(
          std::forward<Args>(args)...);
    }

    template <typename StreamTag, typename... Args>
    decltype(auto)
    setf(Args&&... args)
    {
      return Operator::operation<internal::impl::setf, StreamTag>(
          std::forward<Args>(args)...);
    }

    template <typename StreamTag>
    decltype(auto)
    unsetf(const std::ios_base::fmtflags flags)
    {
      return Operator::operation<internal::impl::flags, StreamTag>(flags);
    }

    template <typename StreamTag, typename... Args>
    decltype(auto)
    precision(Args&&... args)
    {
      return Operator::operation<internal::impl::precision, StreamTag>(
          std::forward<Args>(args)...);
    }

    template <typename StreamTag, typename... Args>
    decltype(auto)
    width(Args&&... args)
    {
      return Operator::operation<internal::impl::width, StreamTag>(
          std::forward<Args>(args)...);
    }

    // Locales
    template <typename StreamTag>
    decltype(auto)
    imbue(const std::locale& loc)
    {
      return Operator::operation<internal::impl::imbue, StreamTag>(loc);
    }

    template <typename StreamTag>
    decltype(auto)
    getloc()
    {
      return Operator::operation<internal::impl::getloc, StreamTag>();
    }

    // Internal extensible array
    decltype(auto) inline xalloc() { return std::ios_base::xalloc(); }

    template <typename StreamTag>
    decltype(auto)
    iword(const int32_t index)
    {
      return Operator::operation<internal::impl::iword, StreamTag>(index);
    }

    template <typename StreamTag>
    decltype(auto)
    pword(const int32_t index)
    {
      return Operator::operation<internal::impl::iword, StreamTag>(index);
    }

    // Miscellaneous
    template <typename StreamTag>
    decltype(auto)
    register_callback(std::ios_base::event_callback function, int32_t index)
    {
      return Operator::operation<internal::impl::register_callback, StreamTag>(
          function, index);
    }

    decltype(auto) inline sync_with_stdio(const bool sync = true)
    {
      return std::ios_base::sync_with_stdio(sync);
    }
  } // namespace stream
}; // namespace io
#endif // IO_IOBASE_HPP
