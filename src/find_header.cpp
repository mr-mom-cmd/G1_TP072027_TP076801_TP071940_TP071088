#include "find_header.hpp"
#include "tolowerx.hpp"

int findHeader(const std::string headers[], int hCount, const char* want){
    std::string W = toLower(std::string(want));
    for(int i=0;i<hCount;++i) if(toLower(headers[i])==W) return i;
    for(int i=0;i<hCount;++i){ std::string h=toLower(headers[i]); if(h.find(W)!=std::string::npos) return i; }
    return -1;
}
