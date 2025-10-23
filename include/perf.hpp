#ifndef PERF_HPP
#define PERF_HPP

#include <chrono>

extern long long g_time_load_candidates_ms;
extern long long g_time_load_jobs_ms;
extern long long g_time_sort_loc_ms;
extern long long g_time_sort_matches_ms;
extern long long g_time_lowerupper_ms;
extern long long g_time_match_total_ms;

extern long long g_sort_loc_comp, g_sort_loc_moves;
extern long long g_sort_matches_comp, g_sort_matches_moves;

extern long long g_linear_cand_comp, g_linear_job_comp;
extern long long g_lower_bound_comp, g_upper_bound_comp;

extern long long g_candidates_evaluated;

void perf_reset();

class ScopedTimer {
public:
    explicit ScopedTimer(long long& target_ms)
        : target(target_ms), start(std::chrono::high_resolution_clock::now()) {}
    ~ScopedTimer() {
        auto end = std::chrono::high_resolution_clock::now();
        target += std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    }
private:
    long long& target;
    std::chrono::time_point<std::chrono::high_resolution_clock> start;
};

#endif
