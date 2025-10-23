#include "../include/linear_job_by_id.hpp"
#include "../include/models.hpp"

const Job* linear_job_by_id(const ArrayList<Job>& jobs, int id){
    for (int i = 0; i < jobs.size(); ++i)
        if (jobs[i].id == id) return &jobs[i];
    return nullptr;
}
