#include "rule_based_pass.hpp"
#include "has_skill.hpp"

bool ruleBasedPass(const Candidate& c, const Job& j){
    for(int i=0;i<j.reqCount;++i) if(!hasSkill(c, j.required[i])) return false;
    return true;
}
