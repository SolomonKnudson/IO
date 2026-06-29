#ifndef IO_INTERNAL_HPP
#define IO_INTERNAL_HPP
// #include <io/internal/impl/file.hpp>
// #include <io/internal/impl/socket.hpp>

//3rd party
#include <operator/operator.hpp>

namespace io
{
  namespace internal
  {
    template <typename ReadImplTag, typename... Args>
    decltype(auto)
    read(Args&&... args)
    {
      Operator::operation<ReadImplTag>(std::forward<Args>(args)...);
    };

    template <typename WriteImplTag, typename... Args>
    decltype(auto)
    write(Args&&... args)
    {
      Operator::operation<WriteImplTag>(std::forward<Args>(args)...);
    };
  }; // namespace internal
}; // namespace io
#endif // IO_INTERNAL_HPP
