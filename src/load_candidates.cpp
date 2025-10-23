#include "load_candidates.hpp"
#include <fstream>
#include <iostream>
#include <cstdlib>
#include "split_csv.hpp"
#include "trim.hpp"
#include "parse_skills.hpp"
#include "tolowerx.hpp"
#include "perf.hpp"

static std::string firstNonEmpty(std::ifstream& fin){
    std::string line;
    while(std::getline(fin,line)){
        if(trim(line).empty()) continue;
        if(line=="resume") continue; // ignore label rows
        return line;
    }
    return std::string();
}

bool loadCandidates(const std::string& path, Candidate outArr[], int& outCount){
    ScopedTimer t(g_time_load_candidates_ms);
    outCount=0;
    std::ifstream fin(path.c_str());
    if(!fin){ std::cerr<<"Cannot open: "<<path<<"\n"; return false; }

    // Read first meaningful line; peek its column count
    std::string line = firstNonEmpty(fin);
    if(line.empty()){ std::cerr<<"Empty file: "<<path<<"\n"; return false; }

    // If it looks like a header row "id,description", skip it and move on
    std::string cols[MAX_COLS];
    int c0 = splitCSV(line, cols, MAX_COLS);
    bool hasHeader = (c0>=2 && toLower(cols[0])=="id" && toLower(cols[1])=="description");
    if(!hasHeader){
        // rewind to process this line as data
        fin.clear();
        fin.seekg(0, std::ios::beg);
    }

    long long autoId = 1;
    if(hasHeader){
        // proceed from current position
    } else {
        // consume any leading labels like "resume"
        std::string skip = firstNonEmpty(fin);
        if(!skip.empty()){
            // If first data line had header shape by accident, push back
            std::string tmp[MAX_COLS];
            int n=splitCSV(skip,tmp,MAX_COLS);
            if(!(n==1)) fin.seekg(0, std::ios::beg);
            else line = skip; // first data row
        }
    }

    // Main read loop
    // If we saw a header, we start fresh after it; otherwise we’ll read all lines.
    fin.clear();
    fin.seekg(0, std::ios::beg);
    bool headerConsumed = false;
    while(std::getline(fin, line)){
        if(trim(line).empty()) continue;
        if(line=="resume") continue;

        std::string vals[MAX_COLS];
        int n = splitCSV(line, vals, MAX_COLS);

        Candidate c;

        if(!headerConsumed && n>=2 && toLower(vals[0])=="id" && toLower(vals[1])=="description"){
            headerConsumed = true;
            continue;
        }

        if(n >= 2){
            c.id = std::atoi(vals[0].c_str());
            c.description = vals[1];
        } else {
            c.id = (int)autoId++;
            c.description = vals[0];
        }

        c.skillsCount = parseSkills(c.description, c.skills, MAX_SKILLS);
        // primaryKey = first skill alphabetically (for sorting/filtering)
        if(c.skillsCount>0){
            int best=0;
            for(int i=1;i<c.skillsCount;++i) if(c.skills[i] < c.skills[best]) best=i;
            c.primaryKey = c.skills[best];
        } else {
            c.primaryKey = ""; // no skills found
        }

        if(outCount<MAX_CANDIDATES) outArr[outCount++] = c;
    }
    return true;
}
