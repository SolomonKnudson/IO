#ifndef IO_IMPL_TAGS_HPP
#define IO_IMPL_TAGS_HPP
//3rd party
#include <operator/operator.hpp>

namespace io::tags
{
  namespace stream
  {
    template <typename StreamType,
              typename BufferType,
              auto& Stream,
              bool Readable,
              bool Writable>
    struct stream_tag
    {
      using stream_type = StreamType;
      using buffer_type = BufferType;

      static stream_type&
      stream()
      {
        return Stream;
      }

      static constexpr bool is_readable{Readable};
      static constexpr bool is_writable{Writable};
    };

    using cin = stream_tag<std::istream, std::streambuf, std::cin, true, false>;
    using wcin =
        stream_tag<std::wistream, std::wstreambuf, std::wcin, true, false>;

    using cout =
        stream_tag<std::ostream, std::streambuf, std::cout, false, true>;
    using wcout =
        stream_tag<std::wostream, std::wstreambuf, std::wcout, false, true>;

    using cerr =
        stream_tag<std::ostream, std::streambuf, std::cerr, false, true>;
    using wcerr =
        stream_tag<std::wostream, std::wstreambuf, std::wcerr, false, true>;

    using clog =
        stream_tag<std::ostream, std::streambuf, std::clog, false, true>;
    using wclog =
        stream_tag<std::wostream, std::wstreambuf, std::wclog, false, true>;
  } // namespace stream
} // namespace io::tags
#endif // IO_IMPL_TAGS_HPP

