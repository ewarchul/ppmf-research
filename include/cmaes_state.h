class cmaes_state {
  using dummy = double;
private:
  dummy m_cov_matrix;
  dummy m_inv_cov_matrix;
  dummy m_mean;
  dummy m_pc;
  dummy m_ps;
  bool h_sigma;

  dummy m_population;
  dummy m_best_so_far;
  dummy m_worst_so_far;
  dummy m_current_best;
};
