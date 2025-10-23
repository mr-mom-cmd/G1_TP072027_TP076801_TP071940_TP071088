#include "parse_skills.hpp"
#include "tolowerx.hpp"
#include "trim.hpp"
#include "models.hpp"

// Extend this list any time:
static const char* VOCAB[] = {
    "python","java","c++","c#","javascript","typescript","node","react","angular",
    "sql","mysql","postgres","mongodb",
    "excel","power bi","tableau",
    "ml","machine learning","deep learning","statistics","pandas","numpy",
    "tensorflow","keras","pytorch","scikit-learn",
    "docker","kubernetes","aws","azure","gcp",
    "rest","api","agile","scrum","git","linux","bash","spark","hadoop","etl",
    "nlp","cv"
};
static const int VOCAB_N = sizeof(VOCAB)/sizeof(VOCAB[0]);

// return true if 'needle' appears as a substring in 'hay' (both lowercased)
static bool containsLC(const std::string& hay, const std::string& needle){
    return hay.find(needle) != std::string::npos;
}

int parseSkills(const std::string& text, std::string outArr[], int maxOut){
    std::string lc = toLower(text);
    int outCount = 0;
    for(int i=0;i<VOCAB_N;++i){
        std::string kw = VOCAB[i];
        if(containsLC(lc, kw)){
            bool dup=false;
            for(int j=0;j<outCount;++j){ if(outArr[j]==kw){ dup=true; break; } }
            if(!dup && outCount<maxOut) outArr[outCount++] = kw;
        }
    }
    return outCount;
}
