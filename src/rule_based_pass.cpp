#include "rule_based_pass.hpp"
#include "has_skill.hpp"
#include "tolowerx.hpp"

bool ruleBasedPass(const Candidate& c, const Job& j){
    if(c.years < j.minYears) return false;
    if(STRICT_LOCATION_MATCH && toLower(c.location)!=toLower(j.location)) return false;
    for(int i=0;i<j.reqCount;++i) if(!hasSkill(c, j.required[i])) return false;
    return true;
}
