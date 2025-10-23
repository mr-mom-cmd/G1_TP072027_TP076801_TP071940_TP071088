#include "find_header.hpp"
#include "trim.hpp"
#include "tolowerx.hpp"

static bool is_likely_header_token(const std::string& tl) {
    return tl == "job_description" || tl == "resume" || tl == "description" ||
           tl == "text" || tl == "skills" || tl == "location" ||
           tl == "job"  || tl == "candidate";
}

bool csv_find_header(const ArrayList<std::string>& cols) {
    int hits = 0;
    for (int i = 0; i < cols.size(); ++i) {
        std::string t  = trim(cols[i]);
        if (t.empty()) continue;
        std::string tl = tolowerx(t);
        if (t.size() <= 40 && t.find(' ') == std::string::npos && is_likely_header_token(tl))
            ++hits;
    }
    return hits > 0;
}
