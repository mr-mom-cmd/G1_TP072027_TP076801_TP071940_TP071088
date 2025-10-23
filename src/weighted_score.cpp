#include "weighted_score.hpp"
#include "has_skill.hpp"

int weightedScore(const Candidate& c, const Job& j){
    int score=0;
    for(int i=0;i<j.reqCount;++i)  if(hasSkill(c,j.required[i]))     score+=WEIGHT_REQUIRED;
    for(int i=0;i<j.niceCount;++i) if(hasSkill(c,j.niceToHave[i]))   score+=WEIGHT_NICE2HAVE;
    return score;
}
