#include "../include/parameters.h"

#include <iostream>

Parameters::Parameters(const int dim, const Vec &x0, const double sigma)
    : m_dim(dim), m_x0(x0), m_init_sigma(sigma) {
  m_init_lambda = 4 + std::floor(3 * std::log(m_dim));
  m_lbound = Vec(m_dim, utils::get_default_lower_bound());
  m_ubound = Vec(m_dim, utils::get_default_upper_bound());
  init();
};

Parameters::Parameters(const Vec &x0, const double sigma)
    : m_x0(x0), m_init_sigma(sigma) {
  m_dim = x0.size();
  m_lbound = Vec(m_dim, utils::get_default_lower_bound());
  m_ubound = Vec(m_dim, utils::get_default_upper_bound());
  m_init_lambda = 4 + std::floor(3 * std::log(m_dim));
  init();
};

Parameters::Parameters(const Vec &x0, const double sigma, const int lambda,
                       const Vec &lbound, const Vec &ubound)
    : m_x0(x0), m_init_sigma(sigma), m_init_lambda(lambda), m_lbound(lbound),
      m_ubound(ubound) {
  m_dim = x0.size();
  init();
};

void Parameters::init() {
  m_max_eval = 10000 * m_dim;
  m_max_iter = std::round(m_max_eval / m_init_lambda);
  m_mu = std::floor(m_init_lambda / 2);
  m_chi = std::sqrt(m_dim) *
          (1.0 - (1.0 / (4.0 * m_dim)) + 1.0 / (21.0 * std::pow(m_dim, 2)));
  m_cs = (m_mu_eff + 2) / (m_dim + m_mu_eff + 3);
  m_mu_weights =
      blaze::log(m_mu + 0.5) - blaze::log(blaze::linspace(m_mu, 1, m_mu));
  m_mu_sum_weights = blaze::sum(m_mu_weights);
  m_mu_weights = m_mu_weights / m_mu_sum_weights;
  m_mu_eff = std::pow(blaze::sum(m_mu_weights), 2) /
             blaze::sum(blaze::pow(m_mu_weights, 2));
  m_cc = 4.0 / (m_dim + 4);
  m_cmu = m_mu_eff;
  m_ccov = (1.0 / m_cmu) * 2.0 / std::pow((m_dim + 1.4), 2) +
           (1.0 - 1.0 / m_cmu) *
               ((2.0 * m_cmu - 1) / std::pow((m_dim + 2), 2) + 2 * m_cmu);
}

void Parameters::set_termination_criteria(TerminationCriteria term_crit) {
  m_terminations.insert(std::pair(term_crit, true));
}

void Parameters::set_max_eval(int max_eval) { m_max_eval = max_eval; }

void Parameters::set_max_iter(int max_iter) { m_max_iter = max_iter; }

void Parameters::reset_termination_criteria() { m_terminations.clear(); }

Vec Parameters::get_x0() const { return m_x0; }

Vec Parameters::get_lower_bound() const { return m_lbound; }

Vec Parameters::get_upper_bound() const { return m_lbound; }

double Parameters::get_init_sigma() const { return m_init_sigma; }

int Parameters::get_init_lambda() const { return m_init_lambda; }

int Parameters::get_max_eval() const { return m_max_eval; }

int Parameters::get_max_iter() const { return m_max_iter; }

double Parameters::get_mu_eff() const { return m_mu_eff; }
