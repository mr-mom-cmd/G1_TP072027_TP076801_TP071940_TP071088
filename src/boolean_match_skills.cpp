#include "../include/boolean_match_skills.hpp"
#include "../include/trim.hpp"
#include "../include/tolowerx.hpp"

// ---------- внутренние утилиты (без STL) ----------

static void normalize_terms(const ArrayList<std::string>& in, ArrayList<std::string>& out) {
    out.clear();
    for (int i = 0; i < in.size(); ++i) {
        std::string t = tolowerx(trim(in[i]));
        if (!t.empty()) out.push_back(t);
    }
}

static bool has_all(const std::string& hay_lower, const ArrayList<std::string>& terms_lower) {
    for (int i = 0; i < terms_lower.size(); ++i)
        if (hay_lower.find(terms_lower[i]) == std::string::npos) return false;
    return true;
}

static bool has_any(const std::string& hay_lower, const ArrayList<std::string>& terms_lower) {
    for (int i = 0; i < terms_lower.size(); ++i)
        if (hay_lower.find(terms_lower[i]) != std::string::npos) return true;
    return false;
}

static bool has_none(const std::string& hay_lower, const ArrayList<std::string>& terms_lower) {
    for (int i = 0; i < terms_lower.size(); ++i)
        if (hay_lower.find(terms_lower[i]) != std::string::npos) return false;
    return true;
}

// ---------- публичная функция ----------

int boolean_match_skills(
    const Candidate& cand,
    const Job& job,
    const ArrayList<std::string>& includeAll,
    const ArrayList<std::string>& includeAny,
    const ArrayList<std::string>& exclude
){
    // 1) нормализуем термы (trim + tolower)
    ArrayList<std::string> ALL, ANY, EX;
    normalize_terms(includeAll, ALL);
    normalize_terms(includeAny, ANY);
    normalize_terms(exclude,   EX);

    const std::string& L = cand.lower; // уже в нижнем регистре при загрузке

    // 2) булевы предикаты
    if (!has_all(L, ALL))              return -1;
    if (!ANY.empty() && !has_any(L,ANY)) return -1;
    if (!has_none(L, EX))              return -1;

    // 3) скоринг: +2 за ALL, +1 за ANY; -3 за EX (теоретически уже исключены)
    int score = 0;
    for (int i = 0; i < ALL.size(); ++i)
        if (L.find(ALL[i]) != std::string::npos) score += 2;
    for (int i = 0; i < ANY.size(); ++i)
        if (L.find(ANY[i]) != std::string::npos) score += 1;
    for (int i = 0; i < EX.size();  ++i)
        if (L.find(EX[i])  != std::string::npos) score -= 3;

    // 4) лёгкий бонус за совпадения с job.skills (если были распарсены)
    for (int i = 0; i < job.skills.size(); ++i) {
        const std::string& s = job.skills[i];
        if (!s.empty() && L.find(s) != std::string::npos) ++score;
    }

    return (score < 0) ? 0 : score;
}
