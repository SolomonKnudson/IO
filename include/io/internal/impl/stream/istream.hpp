#ifndef IO_INTERNAL_ISTREAM_IMPL_HPP
#define IO_INTERNAL_ISTREAM_IMPL_HPP
#include <io/internal/impl/stream/ios_base.hpp>
#include <io/tags.hpp>

// 3rd Party
// STL
#include <STLConvenience/type_traits.hpp>
#include <iostream>

// Formatted input
template <> struct Operator::Impl<io::tags::stream::cin>
{
  template <typename LValue>
  static decltype(auto)
  invoke(LValue&& l_value)
  {
    return Impl<io::internal::impl::ios_base>::invoke(
        io::tags::stream::cin::stream(), std::forward<LValue>(l_value));
  }
};

template <> struct Operator::Impl<io::tags::stream::wcin>
{
  template <typename LValue>
  static decltype(auto)
  invoke(LValue&& l_value)
  {
    return Impl<io::internal::impl::ios_base>::invoke(
        io::tags::stream::wcin::stream(), std::forward<LValue>(l_value));
  }
};

// Unformatted input
template <> struct Operator::Impl<io::internal::impl::get>
{
  template <typename IStreamTag>
  typename IStreamTag::stream_type::int_type
  invoke()
  {
    return IStreamTag::stream().get();
  }

  template <typename IStreamTag>
  static decltype(auto)
  invoke(typename IStreamTag::stream_type::char_type& ch)
  {
    return IStreamTag::stream().get(ch);
  }

  template <typename IStreamTag>
  static decltype(auto)
  invoke(typename IStreamTag::stream_type::char_type* ch,
         const std::streamsize count)
  {
    return IStreamTag::stream().get(ch, count);
  }

  template <typename IStreamTag>
  static decltype(auto)
  invoke(typename IStreamTag::stream_type::char_type* ch,
         const std::streamsize count,
         const typename IStreamTag::stream_type::char_type delim)
  {
    return IStreamTag::stream().get(ch, count, delim);
  }

  template <typename IStreamTag>
  static decltype(auto)
  invoke(typename IStreamTag::buffer_type& buffer)
  {
    return IStreamTag::stream().get(buffer);
  }

  template <typename IStreamTag>
  static decltype(auto)
  invoke(typename IStreamTag::buffer_type& buffer,
         const typename IStreamTag::stream_type::char_type delim)
  {
    return IStreamTag::stream().get(buffer, delim);
  }
};

template <> struct Operator::Impl<io::internal::impl::peek>
{
  template <typename IStreamTag>
  static decltype(auto)
  invoke()
  {
    return IStreamTag::stream().peek();
  }
};

template <> struct Operator::Impl<io::internal::impl::unget>
{
  template <typename IStreamTag>
  static decltype(auto)
  invoke()
  {
    return IStreamTag::stream().unget();
  }
};

template <> struct Operator::Impl<io::internal::impl::putback>
{
  template <typename IStreamTag>
  static decltype(auto)
  invoke(const typename IStreamTag::stream_type::char_type ch)
  {
    return IStreamTag::stream().putback(ch);
  }
};

template <> struct Operator::Impl<io::internal::impl::getline>
{
  template <typename IStreamTag, typename CharType>
  static decltype(auto)
  invoke(typename IStreamTag::stream_type::char_type* ch,
         const std::streamsize count)
  {
    return IStreamTag::stream().getline(ch, count);
  }

  template <typename IStreamTag>
  static decltype(auto)
  invoke(typename IStreamTag::stream_type::char_type* ch,
         const std::streamsize count,
         const typename IStreamTag::stream_type::char_type delim)
  {
    return IStreamTag::stream().getline(ch, count, delim);
  }
};

template <> struct Operator::Impl<io::internal::impl::ignore>
{
  template <typename IStreamTag>
  static decltype(auto)
  invoke(const std::streamsize count = 1,
         const typename IStreamTag::stream_type::int_type delim =
             typename IStreamTag::stream_type::traits_type::eof())
  {
    return IStreamTag::stream().ignore(count, delim);
  }

  template <typename IStreamTag>
  static decltype(auto)
  invoke(const std::streamsize count,
         const typename IStreamTag::stream_type::char_type delim)
  {
    return IStreamTag::stream().ignore(count, delim);
  }
};

template <> struct Operator::Impl<io::internal::impl::read>
{
  template <typename IStreamTag, typename CharType>
  static decltype(auto)
  invoke(typename IStreamTag::stream_type::char_type* ch,
         const std::streamsize count)
  {
    return IStreamTag::stream().read(ch, count);
  }
};

template <> struct Operator::Impl<io::internal::impl::readsome>
{
  template <typename IStreamTag, typename CharType>
  static std::streamsize
  invoke(typename IStreamTag::stream_type::char_type* ch,
         const std::streamsize count)
  {
    return IStreamTag::stream().readsome(ch, count);
  }
};

template <> struct Operator::Impl<io::internal::impl::gcount>
{
  template <typename IStreamTag>
  static std::streamsize
  invoke()
  {
    return IStreamTag::stream().gcount();
  }
};

// TODO: implement tellg(),seekg(), sync()

// Positioning
template <> struct Operator::Impl<io::internal::impl::tellg>
{
  template <typename IStreamTag>
  static typename IStreamTag::stream_type::pos_type
  invoke()
  {
    return IStreamTag::stream().tellg();
  }
};

template <> struct Operator::Impl<io::internal::impl::seekg>
{
  template <typename IStreamTag>
  static decltype(auto)
  invoke(const typename IStreamTag::stream_type::pos_type pos)
  {
    return IStreamTag::stream().seekg(pos);
  }

  template <typename IStreamTag>
  static decltype(auto)
  invoke(const typename IStreamTag::stream_type::off_type off,
         std::ios_base::seekdir& dir)
  {
    return IStreamTag::stream().seekg(off, dir);
  }
};

// Miscellaneous
template <> struct Operator::Impl<io::internal::impl::sync>
{
  template <typename IStreamTag>
  static typename IStreamTag::stream_type::pos_type
  invoke()
  {
    return IStreamTag::stream().sync();
  }
};
#endif // IO_INTERNAL_ISTREAM_IMPL_HPP
