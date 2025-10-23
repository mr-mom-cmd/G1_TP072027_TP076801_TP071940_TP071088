#include <iostream>

#include "include/models.hpp"
#include "include/perf.hpp"
#include "include/load_candidates.hpp"
#include "include/load_jobs.hpp"
#include "include/cli.hpp"

// ---- move big arrays off the stack ----
static Candidate g_candidates[MAX_CANDIDATES];
static Job       g_jobs[MAX_JOBS];
static int       g_candCount = 0;
static int       g_jobCount  = 0;

int main(){
    std::cout << "[dbg] Program started\n";
    perf_reset();

    if(!loadCandidates("Database/resume.csv", g_candidates, g_candCount)){
        std::cerr<<"[err] Failed to load candidates\n"; 
        return 1;
    }
    if(!loadJobs("Database/job_description.csv", g_jobs, g_jobCount)){
        std::cerr<<"[err] Failed to load jobs\n"; 
        return 1;
    }
    std::cout<<"Loaded "<<g_candCount<<" candidates, "<<g_jobCount<<" jobs\n";

    run_cli(g_candidates, g_candCount, g_jobs, g_jobCount);

    return 0;
}
