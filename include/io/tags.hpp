#ifndef IO_IMPL_TAGS_HPP
#define IO_IMPL_TAGS_HPP
//3rd party
#include <iostream>

namespace io
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

    using Cin = stream_tag<std::istream, std::streambuf, std::cin, true, false>;
    using WCin =
        stream_tag<std::wistream, std::wstreambuf, std::wcin, true, false>;

    using Cout =
        stream_tag<std::ostream, std::streambuf, std::cout, false, true>;
    using WCout =
        stream_tag<std::wostream, std::wstreambuf, std::wcout, false, true>;

    using Cerr =
        stream_tag<std::ostream, std::streambuf, std::cerr, false, true>;
    using WCerr =
        stream_tag<std::wostream, std::wstreambuf, std::wcerr, false, true>;

    using Clog =
        stream_tag<std::ostream, std::streambuf, std::clog, false, true>;
    using WClog =
        stream_tag<std::wostream, std::wstreambuf, std::wclog, false, true>;
  } // namespace stream
} // namespace io
#endif // IO_IMPL_TAGS_HPP

