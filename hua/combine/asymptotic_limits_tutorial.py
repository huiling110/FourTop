#!/usr/bin/env python3
"""
Asymptotic Limits Tutorial: Step-by-step calculation for a simple counting experiment

This script demonstrates how the AsymptoticLimits method works in CMS Combine.
It calculates observed and expected upper limits on signal strength (r) using
the CLs method with asymptotic approximations.

Physics Setup:
- Simple counting experiment: observe N events
- Expected background: b
- Expected signal (at r=1): s
- Model: N ~ Poisson(r*s + b)

The goal is to find the 95% CL upper limit on r.

Author: Claude Code Tutorial
"""

import numpy as np
from scipy import stats
from scipy.optimize import minimize_scalar, brentq
import warnings
warnings.filterwarnings('ignore')

def print_header(title):
    """Print a formatted section header"""
    print("\n" + "=" * 70)
    print(f" {title}")
    print("=" * 70)


def print_step(step_num, description):
    """Print a step marker"""
    print(f"\n--- Step {step_num}: {description} ---")


def poisson_log_likelihood(n_obs, mu):
    """
    Poisson log-likelihood: log P(n|mu)

    Args:
        n_obs: observed count
        mu: expected count (r*s + b)

    Returns:
        log-likelihood value
    """
    if mu <= 0:
        return -np.inf
    return n_obs * np.log(mu) - mu - np.sum(np.log(np.arange(1, n_obs + 1)))


def nll(r, n_obs, s, b):
    """Negative log-likelihood as function of signal strength r"""
    mu = r * s + b
    return -poisson_log_likelihood(n_obs, mu)


def profile_likelihood_ratio(r, n_obs, s, b):
    """
    Calculate the profile likelihood ratio lambda(r)

    lambda(r) = L(r, hat{theta}_r) / L(hat{r}, hat{theta})

    For simple counting: this simplifies since there are no nuisance parameters

    Args:
        r: signal strength to test
        n_obs: observed count
        s: expected signal (at r=1)
        b: expected background

    Returns:
        Profile likelihood ratio
    """
    # Likelihood at test point r
    mu_r = r * s + b
    L_r = np.exp(poisson_log_likelihood(n_obs, mu_r))

    # Maximum likelihood estimate of r (unconstrained)
    r_hat = max(0, (n_obs - b) / s)  # MLE, constrained to r >= 0
    mu_hat = r_hat * s + b
    L_hat = np.exp(poisson_log_likelihood(n_obs, mu_hat))

    if L_hat == 0:
        return 0

    return L_r / L_hat


def q_mu(r, n_obs, s, b):
    """
    Test statistic q_mu for upper limits

    q_mu = -2 * ln(lambda(r))  if r_hat <= r
         = 0                    if r_hat > r

    This is the one-sided test statistic appropriate for upper limits.
    """
    r_hat = max(0, (n_obs - b) / s)

    if r_hat > r:
        # Data prefers higher signal strength than r -> no exclusion
        return 0

    plr = profile_likelihood_ratio(r, n_obs, s, b)
    if plr <= 0:
        return 100  # Large value for numerical stability

    return -2 * np.log(plr)


def calculate_cls(q_obs, r, s, b):
    """
    Calculate CLs using asymptotic approximation (Cowan et al. 2011)

    Under asymptotic approximation:
    - q_mu follows a chi-square distribution (with modifications)
    - We can calculate p-values analytically

    CLs = CL_{s+b} / CL_b

    where:
    - CL_{s+b} = P(q_mu >= q_obs | signal+background hypothesis)
    - CL_b = P(q_mu >= q_obs | background-only hypothesis)
    """
    # Asimov dataset: expected counts under each hypothesis
    # Under signal+background (mu = r*s + b)
    mu_sb = r * s + b
    # Under background-only (mu = b)
    mu_b = b

    # For asymptotic formulas, we need the non-centrality parameter
    # sigma^2 = variance of q_mu under background-only hypothesis
    # For counting experiment: sigma^2 ≈ (r*s)^2 / (r*s + b)

    if r * s <= 0:
        return 1.0, 1.0, 1.0

    # Asymptotic approximation (simplified for counting experiment)
    # Under H0 (background only): sqrt(q_mu) ~ N(0, 1) approximately
    # Under H1 (signal+background): sqrt(q_mu) ~ N(-sqrt(Lambda), 1)
    # where Lambda = (r*s)^2 / (r*s + b) for Poisson

    Lambda = (r * s)**2 / (r * s + b)  # Non-centrality parameter

    sqrt_q = np.sqrt(max(0, q_obs))
    sqrt_Lambda = np.sqrt(Lambda)

    # CL_{s+b}: probability of q >= q_obs under signal+background
    # Using asymptotic formula: 1 - Phi(sqrt(q) + sqrt(Lambda))
    # But for upper limits with q_mu, we use different formula

    # Simplified asymptotic (Wald approximation):
    # p_{s+b} = 1 - Phi(sqrt(q_obs))
    # p_b = 1 - Phi(sqrt(q_obs) - sqrt(Lambda))

    p_sb = 1 - stats.norm.cdf(sqrt_q)
    p_b = 1 - stats.norm.cdf(sqrt_q - sqrt_Lambda)

    if p_b < 1e-10:
        cls = 1.0
    else:
        cls = p_sb / p_b

    return cls, p_sb, p_b


def find_limit(n_obs, s, b, cl=0.95):
    """
    Find the upper limit on r at given confidence level

    We find r such that CLs = 1 - cl (typically 0.05 for 95% CL)
    """
    target = 1 - cl  # 0.05 for 95% CL

    def objective(r):
        q = q_mu(r, n_obs, s, b)
        cls, _, _ = calculate_cls(q, r, s, b)
        return cls - target

    # Search for the limit
    try:
        r_limit = brentq(objective, 0.001, 50, xtol=1e-4)
    except ValueError:
        # If brentq fails, use a simple scan
        r_values = np.linspace(0.01, 10, 1000)
        for r in r_values:
            q = q_mu(r, n_obs, s, b)
            cls, _, _ = calculate_cls(q, r, s, b)
            if cls < target:
                r_limit = r
                break
        else:
            r_limit = 10.0

    return r_limit


def expected_limit_quantile(s, b, quantile, cl=0.95):
    """
    Calculate expected limit at a given quantile of the background-only distribution

    quantile: 0.5 for median, 0.16/0.84 for ±1σ, 0.025/0.975 for ±2σ
    """
    # Under background-only hypothesis, expected observation
    # follows Poisson(b), but for asymptotic we use Gaussian approximation

    # Generate "Asimov" data at the given quantile
    # For background-only: n_expected = b
    # The fluctuations are characterized by sqrt(b)

    # At quantile q, the expected count is approximately:
    # n_q = b + sqrt(b) * Phi^{-1}(q)
    z = stats.norm.ppf(quantile)
    n_expected = b + np.sqrt(b) * z
    n_expected = max(0, n_expected)  # Can't have negative counts

    return find_limit(n_expected, s, b, cl)


def main():
    print_header("ASYMPTOTIC LIMITS TUTORIAL")
    print("""
This tutorial demonstrates the CLs method for setting upper limits
on signal strength in a simple counting experiment.

We'll work through each step of the calculation.
    """)

    # =========================================================================
    # SETUP: Define the experiment
    # =========================================================================
    print_header("EXPERIMENT SETUP")

    # Parameters (you can modify these)
    s = 10.0      # Expected signal events (at r=1)
    b = 50.0      # Expected background events
    n_obs = 55    # Observed events (you can change this)

    print(f"Expected signal (s):     {s:.1f} events")
    print(f"Expected background (b): {b:.1f} events")
    print(f"Observed events (n):     {n_obs} events")
    print(f"\nModel: n ~ Poisson(r × s + b) = Poisson(r × {s:.1f} + {b:.1f})")
    print(f"\nGoal: Find 95% CL upper limit on signal strength r")

    # =========================================================================
    # STEP 1: Maximum Likelihood Estimate
    # =========================================================================
    print_step(1, "Maximum Likelihood Estimate (MLE)")

    r_hat = max(0, (n_obs - b) / s)
    print(f"\nMLE of signal strength:")
    print(f"  r_hat = (n_obs - b) / s = ({n_obs} - {b:.1f}) / {s:.1f} = {r_hat:.3f}")
    print(f"\nInterpretation: Data is consistent with r = {r_hat:.3f}")
    if r_hat < 0.1:
        print("  (Close to background-only hypothesis)")

    # =========================================================================
    # STEP 2: Test Statistic q_mu at various r values
    # =========================================================================
    print_step(2, "Profile Likelihood Ratio Test Statistic q_μ")

    print("""
The test statistic for upper limits is:

  q_μ = -2 × ln[L(μ) / L(μ_hat)]   if μ_hat ≤ μ
      = 0                          if μ_hat > μ

where μ = r × s + b is the expected event count.
    """)

    print(f"\nCalculating q_μ for several r values:")
    print(f"{'r':>8} {'μ=r×s+b':>12} {'q_μ':>12} {'sqrt(q_μ)':>12}")
    print("-" * 48)

    test_r_values = [0.5, 1.0, 1.5, 2.0, 2.5, 3.0]
    for r in test_r_values:
        mu = r * s + b
        q = q_mu(r, n_obs, s, b)
        sqrt_q = np.sqrt(q) if q > 0 else 0
        print(f"{r:>8.1f} {mu:>12.1f} {q:>12.4f} {sqrt_q:>12.4f}")

    # =========================================================================
    # STEP 3: CLs Calculation
    # =========================================================================
    print_step(3, "CLs Method")

    print("""
The CLs method provides a modified frequentist approach:

  CLs = CL_{s+b} / CL_b

where:
  CL_{s+b} = P(q ≥ q_obs | signal+background)  [p-value under H1]
  CL_b     = P(q ≥ q_obs | background-only)    [p-value under H0]

We exclude signal strength r if CLs < 0.05 (for 95% CL).
    """)

    print(f"\nCLs values for different r:")
    print(f"{'r':>8} {'q_obs':>10} {'CL_s+b':>12} {'CL_b':>12} {'CLs':>12} {'Excluded?':>12}")
    print("-" * 70)

    for r in test_r_values:
        q = q_mu(r, n_obs, s, b)
        cls, p_sb, p_b = calculate_cls(q, r, s, b)
        excluded = "YES" if cls < 0.05 else "no"
        print(f"{r:>8.1f} {q:>10.4f} {p_sb:>12.4f} {p_b:>12.4f} {cls:>12.4f} {excluded:>12}")

    # =========================================================================
    # STEP 4: Find the 95% CL Upper Limit
    # =========================================================================
    print_step(4, "Finding the 95% CL Upper Limit")

    print("""
The 95% CL upper limit is the value of r where CLs = 0.05.
We find this by scanning or root-finding.
    """)

    r_limit = find_limit(n_obs, s, b, cl=0.95)
    q_at_limit = q_mu(r_limit, n_obs, s, b)
    cls_at_limit, _, _ = calculate_cls(q_at_limit, r_limit, s, b)

    print(f"\n>>> OBSERVED 95% CL UPPER LIMIT: r < {r_limit:.4f} <<<")
    print(f"\nAt r = {r_limit:.4f}:")
    print(f"  q_μ  = {q_at_limit:.4f}")
    print(f"  CLs = {cls_at_limit:.4f} ≈ 0.05")

    # =========================================================================
    # STEP 5: Expected Limits (Median and Bands)
    # =========================================================================
    print_step(5, "Expected Limits (Brazil Band)")

    print("""
Expected limits are calculated assuming the background-only hypothesis is true.
We compute the median expected limit and the ±1σ, ±2σ bands.
    """)

    # Calculate expected limits at different quantiles
    exp_median = expected_limit_quantile(s, b, 0.5)
    exp_p1s = expected_limit_quantile(s, b, 0.84)    # +1σ
    exp_m1s = expected_limit_quantile(s, b, 0.16)    # -1σ
    exp_p2s = expected_limit_quantile(s, b, 0.975)   # +2σ
    exp_m2s = expected_limit_quantile(s, b, 0.025)   # -2σ

    print(f"\nExpected 95% CL Upper Limits:")
    print(f"  -2σ:    r < {exp_m2s:.4f}")
    print(f"  -1σ:    r < {exp_m1s:.4f}")
    print(f"  Median: r < {exp_median:.4f}")
    print(f"  +1σ:    r < {exp_p1s:.4f}")
    print(f"  +2σ:    r < {exp_p2s:.4f}")

    # =========================================================================
    # SUMMARY
    # =========================================================================
    print_header("SUMMARY: Limit Results")

    print(f"""
Experiment: {n_obs} events observed, {b:.0f} background, {s:.0f} signal expected

                      AsymptoticLimits Results
┌─────────────────────────────────────────────────────────────────┐
│  Observed Limit:  r < {r_limit:.4f}                                   │
│                                                                 │
│  Expected  2.5%:  r < {exp_m2s:.4f}                                   │
│  Expected 16.0%:  r < {exp_m1s:.4f}                                   │
│  Expected 50.0%:  r < {exp_median:.4f}                                   │
│  Expected 84.0%:  r < {exp_p1s:.4f}                                   │
│  Expected 97.5%:  r < {exp_p2s:.4f}                                   │
└─────────────────────────────────────────────────────────────────┘
    """)

    # Interpretation
    print("Interpretation:")
    if r_limit < exp_m1s:
        print(f"  Observed limit ({r_limit:.3f}) is STRONGER than -1σ expected ({exp_m1s:.3f})")
        print("  → Data has fewer events than expected (downward fluctuation)")
    elif r_limit > exp_p1s:
        print(f"  Observed limit ({r_limit:.3f}) is WEAKER than +1σ expected ({exp_p1s:.3f})")
        print("  → Data has more events than expected (possible signal or upward fluctuation)")
    else:
        print(f"  Observed limit ({r_limit:.3f}) is within ±1σ of expected ({exp_median:.3f})")
        print("  → Data is consistent with background-only hypothesis")

    # =========================================================================
    # COMPARISON: Effect of VLL options
    # =========================================================================
    print_header("WHY VLL OPTIONS DON'T AFFECT LIMITS")

    print("""
In CMS Combine, VLL analysis uses:
  --setParameters r=0 --freezeParameters r

This sets the initial parameter value to r=0 and freezes it.

However, AsymptoticLimits IGNORES these options because:

1. The method SCANS through r values from rMin to rMax
2. At each r, it calculates CLs independently
3. The initial value of r doesn't matter - only the scan range matters

The VLL options ARE important for:
- Significance: Sets null hypothesis (what we're testing against)
- Impacts: Baseline for calculating systematic effects
- GoF tests: Evaluates fit quality at specific r value

But for limits, the scan-based approach means the starting point is irrelevant.
    """)

    print("\n" + "=" * 70)
    print(" End of Tutorial")
    print("=" * 70)


if __name__ == "__main__":
    main()
