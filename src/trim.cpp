#include "trim.hpp"
#include <cctype>

std::string ltrim(const std::string& s){
    size_t i=0; while(i<s.size() && std::isspace((unsigned char)s[i])) ++i;
    return s.substr(i);
}
std::string rtrim(const std::string& s){
    if(s.empty()) return s;
    size_t i=s.size(); while(i>0 && std::isspace((unsigned char)s[i-1])) --i;
    return s.substr(0,i);
}
std::string trim(const std::string& s){ return rtrim(ltrim(s)); }
