#include "parse_skills.hpp"
#include "split_to_array.hpp"
#include "tolowerx.hpp"
#include "trim.hpp"
#include "models.hpp"

int parseSkills(const std::string& field, std::string outArr[], int maxOut){
    std::string lowered = toLower(field);
    std::string tmp[MAX_SKILLS];
    int n = splitToArray(lowered, ';', tmp, MAX_SKILLS);
    int outCount=0;
    for(int i=0;i<n;++i){
        std::string s = trim(tmp[i]); if(s.empty()) continue;
        bool exists=false;
        for(int j=0;j<outCount;++j) if(outArr[j]==s){ exists=true; break; }
        if(!exists && outCount<maxOut) outArr[outCount++]=s;
    }
    return outCount;
}
