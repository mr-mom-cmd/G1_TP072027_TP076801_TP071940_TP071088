#include <fstream>
#include "../include/load_jobs.hpp"
#include "../include/models.hpp"
#include "../include/split_csv.hpp"
#include "../include/trim.hpp"
#include "../include/tolowerx.hpp"
#include "../include/find_header.hpp"
#include "../include/parse_skills.hpp"

// Читает job_description.csv; текст — последняя непустая колонка.
// Если колонка "skills" или "location" присутствует — подхватим.
bool load_jobs(const std::string& path, ArrayList<Job>& out, std::string& err){
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

        Job j; j.id = nextId++;
        std::string text;

        // Берём последнюю непустую колонку как текст:
        for (int i = cols.size()-1; i >= 0; --i){
            std::string t = trim(cols[i]);
            if (!t.empty()){ text = t; break; }
        }
        if (text.empty()) { --nextId; continue; }

        j.text  = text;
        j.lower = tolowerx(text);

        // Попробуем распарсить навыки прямо из текста (или из отдельной колонки, если есть файл с такими полями)
        parse_skills(text, j.skills);

        // Эвристика локации
        if (j.lower.find("remote") != std::string::npos) j.location = "remote";

        out.push_back(j);
    }
    return true;
}
