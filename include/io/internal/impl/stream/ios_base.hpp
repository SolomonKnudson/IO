#ifndef IO_INTERNAL_IOS_BASE_IMPL_HPP
#define IO_INTERNAL_IOS_BASE_IMPL_HPP
#include <io/internal/concepts.hpp>
#include <io/internal/impl/tags.hpp>

template <> struct Operator::Impl<io::internal::impl::ios_base>
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
                  "Operator::Impl<io::internal::impl::ios_base>(args...): "
                  "ostream must be called with at least one value!");

    ((out_stream << std::forward<OStreamArgs>(args)), ...);
    return out_stream;
  }
};
#endif // IO_INTERNAL_IOS_BASE_IMPL_HPP
