#ifndef IO_INTERNAL_IMPL_TAGS_HPP
#define IO_INTERNAL_IMPL_TAGS_HPP
//3rd party
#include <operator/operator.hpp>

namespace io::internal::impl
{
  // IOstream impls follow STL convention
  // Insertion: >>. 'Outsertion': <<
  OPERATOR_CREATE_IMPL_TAG(iostream);

  OPERATOR_CREATE_IMPL_TAG(cin);
  OPERATOR_CREATE_IMPL_TAG(wcin);

  OPERATOR_CREATE_IMPL_TAG(cout);
  OPERATOR_CREATE_IMPL_TAG(wcout);

  OPERATOR_CREATE_IMPL_TAG(cerr);
  OPERATOR_CREATE_IMPL_TAG(wcerr);

  OPERATOR_CREATE_IMPL_TAG(clog);
  OPERATOR_CREATE_IMPL_TAG(wclog);
} // namespace io::internal::impl
#endif // IO_INTERNAL_IMPL_TAGS_HPP
