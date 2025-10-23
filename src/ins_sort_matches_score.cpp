#include "ins_sort_matches_score.hpp"
#include "perf.hpp"

void insertionSortMatchesByScore(MatchResult a[], int n){
    ScopedTimer t(g_time_sort_matches_ms);
    for(int i=1;i<n;++i){
        MatchResult key=a[i];
        int j=i-1;
        while(j>=0){
            ++g_sort_matches_comp;
            if(a[j].score < key.score){
                a[j+1]=a[j]; ++g_sort_matches_moves;
                --j;
            } else break;
        }
        a[j+1]=key; ++g_sort_matches_moves;
    }
}
