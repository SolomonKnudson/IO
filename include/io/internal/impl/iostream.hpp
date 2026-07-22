#ifndef IO_INTERNAL_STREAM_IMPLS_HPP
#define IO_INTERNAL_STREAM_IMPLS_HPP
#include <io/internal/concepts.hpp>
#include <io/internal/impl/tags.hpp>

// 3rd Party
// STL
#include <iostream>

template <> struct Operator::Impl<io::internal::impl::iostream>
{
  template <typename IStream, typename LValue>
  OPERATOR_CREATE_REQUIRES(
      io::internal::concepts::HasStdStreamInsertion<IStream, LValue>)
  static OPERATOR_AUTO_RETURN invoke(IStream& in_stream, LValue&& l_value)
      OPERATOR_CREATE_TRAILING_RETURN(
          decltype(in_stream >> util::deref(std::forward<LValue>(l_value))))
  {
    in_stream >> Operator::util::deref(std::forward<LValue>(l_value));
    return in_stream;
  }

  template <typename OStream, typename... OStreamArgs>
  OPERATOR_CREATE_REQUIRES(
      io::internal::concepts::HasStdStreamOutsertion<OStream, OStreamArgs...>)
  static OPERATOR_AUTO_RETURN invoke(OStream& out_stream, OStreamArgs&&... args)
      OPERATOR_CREATE_TRAILING_RETURN(
          decltype(((out_stream << std::forward<OStreamArgs>(args)), ...)))
  {
    static_assert(sizeof...(OStreamArgs) > 0,
                  "Operator::Impl<io::internal::impl::iostream>(args...): "
                  "ostream must be called with at least one value!");

    ((out_stream << std::forward<OStreamArgs>(args)), ...);
    return out_stream;
  }
};

template <> struct Operator::Impl<io::internal::impl::cin>
{
  template <typename LValue>
  static decltype(auto)
  invoke(LValue&& l_value)
  {
    return Impl<io::internal::impl::iostream>::invoke(
        std::cin, std::forward<LValue>(l_value));
  }
};

template <> struct Operator::Impl<io::internal::impl::wcin>
{
  template <typename LValue>
  static decltype(auto)
  invoke(LValue&& l_value)
  {
    return Impl<io::internal::impl::iostream>::invoke(
        std::wcin, std::forward<LValue>(l_value));
  }
};

template <> struct Operator::Impl<io::internal::impl::cout>
{
  template <typename... Args>
  static decltype(auto)
  invoke(Args&&... args)
  {
    return Impl<io::internal::impl::iostream>::invoke(
        std::cout, std::forward<Args>(args)...);
  }
};

template <> struct Operator::Impl<io::internal::impl::wcout>
{
  template <typename... Args>
  static decltype(auto)
  invoke(Args&&... args)
  {
    return Impl<io::internal::impl::iostream>::invoke(
        std::wcout, std::forward<Args>(args)...);
  }
};

template <> struct Operator::Impl<io::internal::impl::cerr>
{
  template <typename... Args>
  static decltype(auto)
  invoke(Args&&... args)
  {
    return Impl<io::internal::impl::iostream>::invoke(
        std::cerr, std::forward<Args>(args)...);
  }
};

template <> struct Operator::Impl<io::internal::impl::wcerr>
{
  template <typename... Args>
  static decltype(auto)
  invoke(Args&&... args)
  {
    return Impl<io::internal::impl::iostream>::invoke(
        std::wcerr, std::forward<Args>(args)...);
  }
};

template <> struct Operator::Impl<io::internal::impl::clog>
{
  template <typename... Args>
  static decltype(auto)
  invoke(Args&&... args)
  {
    return Impl<io::internal::impl::iostream>::invoke(
        std::clog, std::forward<Args>(args)...);
  }
};

template <> struct Operator::Impl<io::internal::impl::wclog>
{
  template <typename... Args>
  static decltype(auto)
  invoke(Args&&... args)
  {
    return Impl<io::internal::impl::iostream>::invoke(
        std::wclog, std::forward<Args>(args)...);
  }
};
#endif // IO_INTERNAL_STREAM_IMPLS_HPP
