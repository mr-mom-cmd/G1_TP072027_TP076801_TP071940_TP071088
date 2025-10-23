#include "has_skill.hpp"
bool hasSkill(const Candidate& c, const std::string& s){
    for(int i=0;i<c.skillsCount;++i) if(c.skills[i]==s) return true;
    return false;
}
