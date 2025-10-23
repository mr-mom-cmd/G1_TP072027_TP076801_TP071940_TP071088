#include "load_jobs.hpp"
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
        if(line=="job_description") continue;
        return line;
    }
    return std::string();
}

bool loadJobs(const std::string& path, Job outArr[], int& outCount){
    ScopedTimer t(g_time_load_jobs_ms);
    outCount=0;
    std::ifstream fin(path.c_str());
    if(!fin){ std::cerr<<"Cannot open: "<<path<<"\n"; return false; }

    std::string line = firstNonEmpty(fin);
    if(line.empty()){ std::cerr<<"Empty file: "<<path<<"\n"; return false; }

    std::string cols[MAX_COLS];
    int c0 = splitCSV(line, cols, MAX_COLS);
    bool hasHeader = (c0>=2 && toLower(cols[0])=="id" && toLower(cols[1])=="description");
    if(!hasHeader){
        fin.clear();
        fin.seekg(0, std::ios::beg);
    }

    long long autoId=1;
    fin.clear();
    fin.seekg(0, std::ios::beg);
    bool headerConsumed=false;

    while(std::getline(fin, line)){
        if(trim(line).empty()) continue;
        if(line=="job_description") continue;

        std::string vals[MAX_COLS];
        int n = splitCSV(line, vals, MAX_COLS);

        if(!headerConsumed && n>=2 && toLower(vals[0])=="id" && toLower(vals[1])=="description"){
            headerConsumed=true; continue;
        }

        Job j;
        if(n>=2){
            j.id = std::atoi(vals[0].c_str());
            j.description = vals[1];
        } else {
            j.id = (int)autoId++;
            j.description = vals[0];
        }

        // extract keywords: required from strong terms, nice-to-have from the rest (simple split)
        // For simplicity we put all extracted terms into 'required' and leave nice empty.
        j.reqCount  = parseSkills(j.description, j.required, MAX_SKILLS);
        j.niceCount = 0;

        if(outCount<MAX_JOBS) outArr[outCount++] = j;
    }
    return true;
}
