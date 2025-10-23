#include "boolean_match_skills.hpp"
#include "models.hpp"
#include "trim.hpp"
#include "tolowerx.hpp"

// Вспомогательные проверки по нижнему регистру
static bool has_any(const std::string& lower, const ArrayList<std::string>& terms){
    for (int i = 0; i < terms.size(); ++i)
        if (lower.find(terms[i]) != std::string::npos) return true;
    return false;
}
static bool has_all(const std::string& lower, const ArrayList<std::string>& terms){
    for (int i = 0; i < terms.size(); ++i)
        if (lower.find(terms[i]) == std::string::npos) return false;
    return true;
}
static bool has_none(const std::string& lower, const ArrayList<std::string>& terms){
    for (int i = 0; i < terms.size(); ++i)
        if (lower.find(terms[i]) != std::string::npos) return false;
    return true;
}

// Матчим КАНДИДАТА к требованиям ДОЛЖНОСТИ по булевой логике.
// Возвращаем score (>=0) или -1, если не прошёл фильтры.
int boolean_match_skills(
    const Candidate& cand,
    const Job& job,
    const ArrayList<std::string>& includeAll,
    const ArrayList<std::string>& includeAny,
    const ArrayList<std::string>& exclude
){
    const std::string& L = cand.lower;

    if (!has_all(L, includeAll)) return -1;
    if (!includeAny.empty() && !has_any(L, includeAny)) return -1;
    if (!has_none(L, exclude)) return -1;

    int score = 0;
    for (int i = 0; i < includeAll.size(); ++i)
        if (L.find(includeAll[i]) != std::string::npos) score += 2;
    for (int i = 0; i < includeAny.size(); ++i)
        if (L.find(includeAny[i]) != std::string::npos) score += 1;
    for (int i = 0; i < exclude.size(); ++i)
        if (L.find(exclude[i]) != std::string::npos) score -= 3;

    // небольшой бонус за совпадение с навыками из job.skills (если распарсены)
    for (int i = 0; i < job.skills.size(); ++i)
        if (L.find(job.skills[i]) != std::string::npos) ++score;

    return (score < 0) ? 0 : score;
}
