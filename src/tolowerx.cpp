#include "tolowerx.hpp"
#include <cctype>
std::string toLower(std::string s){
    for(size_t i=0;i<s.size();++i) s[i]=(char)std::tolower((unsigned char)s[i]);
    return s;
}
