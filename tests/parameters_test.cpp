#include "../include/parameters.h"
#include <boost/test/unit_test.hpp>
#include "../include/utils.h"

/*
 * https://arxiv.org/pdf/1604.00772.pdf
 *
 *  weights = log(mu+1/2)-log(1:mu)’; % muXone recombination weights
 *  mu = floor(mu); % number of parents/points for recombination
 *  weights = weights/sum(weights); % normalize recombination weights array
 *  mueff=sum(weights)ˆ2/sum(weights.ˆ2); % variance-effective size of mu
 *
 * */

struct TestParameters {
  int dim = 10;
  Vec x0 = Vec(dim, 1);
  double sigma = 7;
  int lambda = 10;
  long double eps = 0.00001;
};

BOOST_FIXTURE_TEST_CASE(TestParametersInitialization, TestParameters) {
  auto params = Parameters(dim, x0, sigma);
  auto expected_x0 = params.get_x0();
  auto expected_lambda = params.get_init_lambda();
  auto expected_max_eval = params.get_max_eval();
  auto expected_max_iter = params.get_max_iter();
  auto expected_mu_eff = params.get_mu_eff();

  BOOST_CHECK_EQUAL(expected_x0, x0);

  BOOST_CHECK_EQUAL(expected_lambda, 4 + std::floor(3 * std::log(dim)));

  BOOST_CHECK_EQUAL(expected_max_eval, 10000 * dim);

  BOOST_CHECK_EQUAL(
      expected_max_iter,
      std::round(10000 * dim / (4 + std::floor(3 * std::log(dim)))));

  BOOST_CHECK_CLOSE(expected_mu_eff, 3.167299, eps);
};
