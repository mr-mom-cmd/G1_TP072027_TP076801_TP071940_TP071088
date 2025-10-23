#include <fstream>
#include "../include/load_candidates.hpp"
#include "../include/models.hpp"
#include "../include/split_csv.hpp"
#include "../include/trim.hpp"
#include "../include/tolowerx.hpp"
#include "../include/find_header.hpp"
#include "../include/parse_skills.hpp"

// Читает resume.csv; берём "последнюю непустую колонку" как текст.
// Дополнительно заполняем lower и skills (через parse_skills).
bool load_candidates(const std::string& path, ArrayList<Candidate>& out, std::string& err){
    out.clear();
    std::ifstream f(path);
    if (!f.is_open()){ err = "Cannot open: " + path; return false; }

    std::string line;
    ArrayList<std::string> cols;
    bool firstChecked = false;
    int nextId = 1;

    while (std::getline(f, line)){
        if (trim(line).empty()) continue;
        split_csv_line(line, cols);

        if (!firstChecked){
            firstChecked = true;
            if (csv_find_header(cols)) continue;
        }

        std::string text;
        for (int i = cols.size()-1; i >= 0; --i){
            std::string t = trim(cols[i]);
            if (!t.empty()){ text = t; break; }
        }
        if (text.empty()) continue;

        Candidate c;
        c.id = nextId++;
        c.text = text;
        c.lower = tolowerx(text);
        // skills (грубый парс — из текста)
        parse_skills(text, c.skills);      // твой разобранный helper из include/parse_skills.hpp

        // Попробуем вытащить location из текста эвристикой (не обязательно)
        // если у тебя есть отдельная колонка — можешь заменить извлечение
        // здесь оставим пустым или «remote» если встречается слово
        if (c.lower.find("remote") != std::string::npos) c.location = "remote";

        out.push_back(c);
    }
    return true;
}
