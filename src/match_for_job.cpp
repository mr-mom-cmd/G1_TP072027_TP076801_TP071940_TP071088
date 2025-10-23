#include "match_for_job.hpp"
#include "rule_based_pass.hpp"
#include "weighted_score.hpp"
#include "ins_sort_matches_score.hpp"
#include "perf.hpp"

int matchForJob(const Job& job, Candidate cands[], int nCands, MatchResult outMatches[]){
    ScopedTimer total(g_time_match_total_ms);
    int mCount=0;
    for(int i=0;i<nCands;++i){
        ++g_candidates_evaluated;
        if(!ruleBasedPass(cands[i], job)) continue;
        int s = weightedScore(cands[i], job);
        if(mCount<MAX_MATCHES){
            outMatches[mCount].candIndex=i;
            outMatches[mCount].score=s;
            ++mCount;
        }
    }
    insertionSortMatchesByScore(outMatches, mCount);
    return mCount;
}
