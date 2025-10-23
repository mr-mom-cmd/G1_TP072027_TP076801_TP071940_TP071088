#include "perf.hpp"

long long g_time_load_candidates_ms = 0;
long long g_time_load_jobs_ms       = 0;
long long g_time_sort_loc_ms        = 0;
long long g_time_sort_matches_ms    = 0;
long long g_time_lowerupper_ms      = 0;
long long g_time_match_total_ms     = 0;

long long g_sort_loc_comp           = 0;
long long g_sort_loc_moves          = 0;
long long g_sort_matches_comp       = 0;
long long g_sort_matches_moves      = 0;

long long g_linear_cand_comp        = 0;
long long g_linear_job_comp         = 0;
long long g_lower_bound_comp        = 0;
long long g_upper_bound_comp        = 0;

long long g_candidates_evaluated    = 0;

void perf_reset() {
    g_time_load_candidates_ms = g_time_load_jobs_ms = 0;
    g_time_sort_loc_ms = g_time_sort_matches_ms = 0;
    g_time_lowerupper_ms = 0;
    g_time_match_total_ms = 0;

    g_sort_loc_comp = g_sort_loc_moves = 0;
    g_sort_matches_comp = g_sort_matches_moves = 0;

    g_linear_cand_comp = g_linear_job_comp = 0;
    g_lower_bound_comp = g_upper_bound_comp = 0;

    g_candidates_evaluated = 0;
}
