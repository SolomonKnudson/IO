#ifndef IO_INTERNAL_IMPL_TAGS_HPP
#define IO_INTERNAL_IMPL_TAGS_HPP
//3rd party
#include <operator/operator.hpp>

namespace io::internal::impl
{
  // IOstream impls follow STL convention
  // Insertion: >>. 'Outsertion': <<
  OPERATOR_CREATE_IMPL_TAG(ios_base);

  // Shared methods
  // Formatting
  OPERATOR_CREATE_IMPL_TAG(flags);
  OPERATOR_CREATE_IMPL_TAG(setf);

  OPERATOR_CREATE_IMPL_TAG(unsetf);
  OPERATOR_CREATE_IMPL_TAG(precision);

  OPERATOR_CREATE_IMPL_TAG(width);

  // Locales
  OPERATOR_CREATE_IMPL_TAG(imbue);
  OPERATOR_CREATE_IMPL_TAG(getloc);

  // Internal extensible array
  OPERATOR_CREATE_IMPL_TAG(iword);
  OPERATOR_CREATE_IMPL_TAG(pword);

  // Miscellaneous
  OPERATOR_CREATE_IMPL_TAG(register_callback);

  // Unformatted input
  // IStream methods
  OPERATOR_CREATE_IMPL_TAG(get);
  OPERATOR_CREATE_IMPL_TAG(peek);

  OPERATOR_CREATE_IMPL_TAG(unget);
  OPERATOR_CREATE_IMPL_TAG(putback);

  OPERATOR_CREATE_IMPL_TAG(getline);
  OPERATOR_CREATE_IMPL_TAG(ignore);

  OPERATOR_CREATE_IMPL_TAG(read);
  OPERATOR_CREATE_IMPL_TAG(readsome);

  OPERATOR_CREATE_IMPL_TAG(gcount);

  // OStream methods
  OPERATOR_CREATE_IMPL_TAG(put);
  OPERATOR_CREATE_IMPL_TAG(write);

  // Positioning
  // IStream methods
  OPERATOR_CREATE_IMPL_TAG(tellg);
  OPERATOR_CREATE_IMPL_TAG(seekg);

  // OStream methods
  OPERATOR_CREATE_IMPL_TAG(tellp);
  OPERATOR_CREATE_IMPL_TAG(seekp);

  // Miscellaneous
  OPERATOR_CREATE_IMPL_TAG(sync);

  // OStream methods
  OPERATOR_CREATE_IMPL_TAG(flush);
} // namespace io::internal::impl
#endif // IO_INTERNAL_IMPL_TAGS_HPP
