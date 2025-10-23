#include "ins_sort_cand_location.hpp"
#include "perf.hpp"

static bool before(const Candidate& A, const Candidate& B){
    if(A.primaryKey.empty() && !B.primaryKey.empty()) return false;
    if(!A.primaryKey.empty() && B.primaryKey.empty()) return true;
    return A.primaryKey < B.primaryKey;
}

void insertionSortCandidatesByLocation(Candidate a[], int n){
    ScopedTimer t(g_time_sort_loc_ms);
    for(int i=1;i<n;++i){
        Candidate key = a[i];
        int j=i-1;
        while(j>=0){
            ++g_sort_loc_comp;
            if(before(key, a[j])){ a[j+1]=a[j]; ++g_sort_loc_moves; --j; }
            else break;
        }
        a[j+1]=key; ++g_sort_loc_moves;
    }
}
