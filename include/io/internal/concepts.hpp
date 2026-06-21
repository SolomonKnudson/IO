#ifndef IO_INTERNAL_CONCEPTS_HPP
#define IO_INTERNAL_CONCEPTS_HPP
#if defined(__cpp_concepts)
#include <operator/operator.hpp>

namespace io::internal::concepts
{
  //IOStream
  template <typename Stream, typename LValue>
  concept HasStdStreamInsertion =
      OPERATOR_CREATE_REQUIRES((Stream& stream, LValue&& l_value) {
        stream >> Operator::util::deref(std::forward<LValue>(l_value));
      });

  template <typename Stream, typename... Args>
  concept HasStdStreamOutsertion =
      OPERATOR_CREATE_REQUIRES((Stream& stream, Args&&... args) {
        ((stream << std::forward<Args>(args)), ...);
      });
} // namespace io::internal::concepts
#endif // __cpp_concepts
#endif // IO_INTERNAL_CONCEPTS_HPP
