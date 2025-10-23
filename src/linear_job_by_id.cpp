#include "linear_job_by_id.hpp"
#include "perf.hpp"

int linearSearchJobById(Job arr[], int n, int targetId){
    for(int i=0;i<n;++i){ ++g_linear_job_comp; if(arr[i].id==targetId) return i; }
    return -1;
}
