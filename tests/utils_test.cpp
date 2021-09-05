#include "../include/utils.h"
#include <boost/test/unit_test.hpp>
#include <type_traits>

#include "../include/types.h"

BOOST_AUTO_TEST_CASE(UtilitiesTest) {
  auto int_result = utils::pow_n_plus<2, int>(2, 2);
  BOOST_CHECK_EQUAL(int_result, 16);
  auto double_result = utils::pow_n_plus<2, double>(2, 2);
  auto type_test = std::is_same<decltype(double_result), double>::value;
  BOOST_CHECK(type_test);
}

BOOST_AUTO_TEST_CASE(EvaluationFunctionsTest) {
  std::vector<double> input(3, 1);
  auto retval = utils::evalfuncs::F_sphere<3>(input.data());
  BOOST_CHECK_EQUAL(retval, 3);
}

BOOST_AUTO_TEST_CASE(BlazeInternalTest) {
  Matrix input_mat = {{3, 5, 6}, {4, 5, 6}};
  auto sphere_func = [](const double *x, size_t N) -> double {
   return utils::evalfuncs::F_sphere<2>(x);
  };
  Vec expected_vec = {25, 50, 72};
  auto ret_vec = blaze::internal::apply(input_mat, sphere_func);
  BOOST_CHECK_EQUAL(ret_vec, expected_vec);
}
