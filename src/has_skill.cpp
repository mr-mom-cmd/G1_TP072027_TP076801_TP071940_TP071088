#include "../include/has_skill.hpp"
#include "../include/tolowerx.hpp"

bool has_skill(const Candidate& c, const std::string& skill){
    std::string s = tolowerx(skill);

    // 1) точное совпадение по разобранным skills
    for (int i = 0; i < c.skills.size(); ++i)
        if (c.skills[i] == s) return true;

    // 2) как подстрока в тексте (кэш нижнего регистра)
    return (!s.empty() && c.lower.find(s) != std::string::npos);
}

bool job_has_skill(const Job& j, const std::string& skill){
    std::string s = tolowerx(skill);

    for (int i = 0; i < j.skills.size(); ++i)
        if (j.skills[i] == s) return true;

    return (!s.empty() && j.lower.find(s) != std::string::npos);
}
