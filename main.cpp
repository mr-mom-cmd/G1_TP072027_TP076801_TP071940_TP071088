#include <iostream>
#include "include/models.hpp"
#include "include/perf.hpp"
#include "include/load_candidates.hpp"
#include "include/load_jobs.hpp"
#include "include/cli.hpp"

int main(){
    perf_reset();

    Candidate candidates[MAX_CANDIDATES];
    Job jobs[MAX_JOBS];
    int candCount=0, jobCount=0;

    if(!loadCandidates("Database/resume.csv", candidates, candCount)){
        std::cerr<<"Failed to load candidates\n"; return 1;
    }
    if(!loadJobs("Database/job_description.csv", jobs, jobCount)){
        std::cerr<<"Failed to load jobs\n"; return 1;
    }
    std::cout<<"Loaded "<<candCount<<" candidates, "<<jobCount<<" jobs\n";

    // launch interactive CLI
    run_cli(candidates, candCount, jobs, jobCount);

    return 0;
}
