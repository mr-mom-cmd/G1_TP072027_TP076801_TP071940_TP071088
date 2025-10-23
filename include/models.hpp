#ifndef MODELS_HPP
#define MODELS_HPP

#include <string>

const int MAX_CANDIDATES = 2000;
const int MAX_JOBS       = 500;
const int MAX_SKILLS     = 32;
const int MAX_COLS       = 16;
const int MAX_MATCHES    = MAX_CANDIDATES;

// Tunables
const int WEIGHT_REQUIRED        = 10;
const int WEIGHT_NICE2HAVE       = 5;
const int WEIGHT_LOCATION_BONUS  = 5;
const int WEIGHT_PER_EXTRA_YEAR  = 2;
const int EXTRA_YEAR_CAP         = 5;

const bool STRICT_LOCATION_MATCH = false;

struct Candidate {
    int id = -1;
    std::string name;
    std::string location;
    int years = 0;
    std::string skills[MAX_SKILLS];
    int skillsCount = 0;
};

struct Job {
    int id = -1;
    std::string title;
    std::string location;
    int minYears = 0;
    std::string required[MAX_SKILLS];
    int reqCount = 0;
    std::string niceToHave[MAX_SKILLS];
    int niceCount = 0;
};

struct MatchResult {
    int candIndex = -1;
    int score = 0;
};

#endif
