#include <boost/test/test_tools.hpp>
#include <boost/test/unit_test.hpp>
#include "../include/math.h"
#include "../include/utils.h"

BOOST_AUTO_TEST_CASE(BlazeInternalApplyTest) {
  Matrix input_mat = {{3, 5, 6}, {4, 5, 6}};
  constexpr size_t dim = 2;
  Eval sphere_func = [&](const double *x, size_t _) {
   return utils::evalfuncs::F_sphere<dim>(x);
  };
  Vec expected_vec = {25, 50, 72};
  auto ret_vec = blaze::internal::apply(input_mat, sphere_func);
 BOOST_CHECK_EQUAL(ret_vec, expected_vec);
}

BOOST_AUTO_TEST_CASE(SortTestBlazeVector) {
  Vec v1{4, 6, 5, 7};
  Vec expected_vec{0, 2, 1, 3};
  auto v1_sorted = blaze::internal::sort_ind(v1);
  BOOST_CHECK_EQUAL(v1_sorted, expected_vec);
}

BOOST_AUTO_TEST_CASE(SortTestSTLVector) {
  std::vector v1{4, 6, 5, 7};
  std::vector expected_vec{0, 2, 1, 3};
  auto v1_sorted = blaze::internal::sort_ind(v1);
  BOOST_CHECK_EQUAL_COLLECTIONS(v1_sorted.begin(), v1_sorted.end(),
                                expected_vec.begin(), expected_vec.end());
}

