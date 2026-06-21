#include <io/io.hpp>

int
main(int argc, char* argv[])
{
  io::stream::cout(
      "Can deref int*: ", std::boolalpha, type_traits::can_deref_v<int*>, '\n');

  std::string test_string{};
  int test_int{};

  io::stream::cout("io::stream::cout(args...)\n");

  const std::string const_string{"test"};
  io::stream::cout(const_string, '\n');

  io::stream::cout("Enter string: ");
  io::stream::cin(&test_string);

  io::stream::cout("Enter number: ");
  io::stream::cin(test_int);

  io::stream::cout("Test string: ", test_string, '\n');
  io::stream::cout("Test int: ", test_int, '\n');

  return 0;
}
