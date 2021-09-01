#include <boost/test/unit_test.hpp>
#include "../include/utils.h"

#include <type_traits>

BOOST_AUTO_TEST_CASE(UtilitiesTest) {
  auto int_result =  utils::pow_n_plus<2, int>(2, 2);
  BOOST_CHECK_EQUAL(int_result, 16);
  auto double_result = utils::pow_n_plus<2, double>(2, 2); 
  auto type_test = std::is_same<decltype(double_result), double>::value;
  BOOST_CHECK(type_test);
}
