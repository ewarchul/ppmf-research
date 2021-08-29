#include "../include/utils.h"
#include <gtest/gtest.h>

TEST(UtilsTest, UtilityFunctions) {
  EXPECT_EQ(
    utils::get_default_lower_bound(),
    -100
  );
  EXPECT_EQ(
    utils::get_default_upper_bound(),
    100
  );
  EXPECT_EQ(
    std::invoke(utils::pow_n_plus<double, 2>(), 2, 2),
    16
  );
}
