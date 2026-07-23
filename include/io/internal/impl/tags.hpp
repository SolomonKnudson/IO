#ifndef IO_INTERNAL_IMPL_TAGS_HPP
#define IO_INTERNAL_IMPL_TAGS_HPP
//3rd party
#include <operator/operator.hpp>

namespace io::internal::impl
{
  // IOstream impls follow STL convention
  // Insertion: >>. 'Outsertion': <<
  OPERATOR_CREATE_IMPL_TAG(ios_base);
  OPERATOR_CREATE_IMPL_TAG(get);

  OPERATOR_CREATE_IMPL_TAG(peek);
  OPERATOR_CREATE_IMPL_TAG(unget);

  OPERATOR_CREATE_IMPL_TAG(putback);
  OPERATOR_CREATE_IMPL_TAG(getline);

  OPERATOR_CREATE_IMPL_TAG(ignore);
  OPERATOR_CREATE_IMPL_TAG(read);

  OPERATOR_CREATE_IMPL_TAG(readsome);
  OPERATOR_CREATE_IMPL_TAG(gcount);
} // namespace io::internal::impl
#endif // IO_INTERNAL_IMPL_TAGS_HPP
