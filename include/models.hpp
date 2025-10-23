#ifndef MODELS_HPP
#define MODELS_HPP

#include <string>

const int MAX_CANDIDATES = 2000;
const int MAX_JOBS       = 500;
const int MAX_SKILLS     = 64;
const int MAX_COLS       = 64;
const int MAX_MATCHES    = MAX_CANDIDATES;

// weights for simple keyword-based scoring
const int WEIGHT_REQUIRED   = 10;
const int WEIGHT_NICE2HAVE  = 5;

struct Candidate {
    int id = -1;
    std::string description;                 // raw resume text
    std::string skills[MAX_SKILLS];          // extracted keywords
    int skillsCount = 0;
    std::string primaryKey;                  // first skill alphabetically (for sorting/filtering)
};

struct Job {
    int id = -1;
    std::string description;                 // raw job description
    std::string required[MAX_SKILLS];        // extracted required keywords
    int reqCount = 0;
    std::string niceToHave[MAX_SKILLS];      // extracted nice keywords
    int niceCount = 0;
};

struct MatchResult {
    int candIndex = -1;
    int score = 0;
};

#endif
