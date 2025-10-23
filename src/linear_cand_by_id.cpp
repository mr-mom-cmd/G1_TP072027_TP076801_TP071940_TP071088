#include "linear_cand_by_id.hpp"
#include "perf.hpp"

int linearSearchCandidateById(Candidate arr[], int n, int targetId){
    for(int i=0;i<n;++i){ ++g_linear_cand_comp; if(arr[i].id==targetId) return i; }
    return -1;
}
