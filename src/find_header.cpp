#include "../include/find_header.hpp"
#include "../include/trim.hpp"
#include "../include/tolowerx.hpp"

static bool is_likely_header_token(const std::string& tl) {
    return tl == "job_description" || tl == "resume" || tl == "description" ||
           tl == "text" || tl == "skills" || tl == "location" ||
           tl == "job"  || tl == "candidate" || tl == "title";
}

bool csv_find_header(const ArrayList<std::string>& cols) {
    if (cols.size() == 0) return false;

    // Правило 1: наличие «знаковых» имён колонок
    int hits = 0;
    for (int i = 0; i < cols.size(); ++i) {
        std::string t  = trim(cols[i]);
        if (t.empty()) continue;
        std::string tl = tolowerx(t);
        if (is_likely_header_token(tl)) ++hits;
    }
    if (hits > 0) return true;

    // Правило 2: «похожесть на заголовок» — много коротких токенов без пробелов
    int shortNoSpace = 0, nonEmpty = 0;
    for (int i = 0; i < cols.size(); ++i) {
        std::string t = trim(cols[i]);
        if (t.empty()) continue;
        ++nonEmpty;
        if (t.size() <= 40 && t.find(' ') == std::string::npos) ++shortNoSpace;
    }
    return nonEmpty > 0 && shortNoSpace * 2 >= nonEmpty; // ≥ 50% коротких без пробелов
}
