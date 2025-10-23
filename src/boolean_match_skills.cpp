#include "boolean_match_skills.hpp"
#include "has_skill.hpp"
#include "tolowerx.hpp"

bool booleanMatchSkills(const Candidate& c, const std::string keywords[], int kCount, bool modeAND){
    if(kCount<=0) return true;
    if(modeAND){
        for(int i=0;i<kCount;++i) if(!hasSkill(c, toLower(keywords[i]))) return false;
        return true;
    }else{
        for(int i=0;i<kCount;++i) if(hasSkill(c, toLower(keywords[i]))) return true;
        return false;
    }
}
