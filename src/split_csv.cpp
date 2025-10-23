#include "split_csv.hpp"
#include "trim.hpp"

// RFC-4180-ish: supports quoted fields, commas inside quotes, "" escape
int splitCSV(const std::string& line, std::string outArr[], int maxOut){
    int count = 0;
    std::string field;
    bool inQuotes = false;

    for (size_t i = 0; i < line.size(); ++i) {
        char c = line[i];
        if (c == '"') {
            if (inQuotes && i + 1 < line.size() && line[i + 1] == '"') { field.push_back('"'); ++i; }
            else inQuotes = !inQuotes;
        } else if (c == ',' && !inQuotes) {
            if (count < maxOut) outArr[count++] = trim(field);
            field.clear();
        } else field.push_back(c);
    }
    if (count < maxOut) outArr[count++] = trim(field);
    return count;
}
