#include "weighted_score.hpp"
#include "has_skill.hpp"
#include "tolowerx.hpp"

int weightedScore(const Candidate& c, const Job& j){
    int score=0;
    for(int i=0;i<j.reqCount;++i) if(hasSkill(c,j.required[i])) score+=WEIGHT_REQUIRED;
    for(int i=0;i<j.niceCount;++i) if(hasSkill(c,j.niceToHave[i])) score+=WEIGHT_NICE2HAVE;
    if(toLower(c.location)==toLower(j.location)) score+=WEIGHT_LOCATION_BONUS;
    if(c.years>j.minYears){
        int extra=c.years-j.minYears;
        if(extra>EXTRA_YEAR_CAP) extra=EXTRA_YEAR_CAP;
        score += extra*WEIGHT_PER_EXTRA_YEAR;
    }
    return score;
}
