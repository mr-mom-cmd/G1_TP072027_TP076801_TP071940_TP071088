#include "split_to_array.hpp"
#include "trim.hpp"

int splitToArray(const std::string& line, char delim, std::string outArr[], int maxOut){
    int count=0; std::string cur;
    for(size_t i=0;i<line.size();++i){
        if(line[i]==delim){
            if(count<maxOut) outArr[count++]=trim(cur);
            cur.clear();
        }else cur.push_back(line[i]);
    }
    if(!cur.empty() || (!line.empty() && line.back()==delim)){
        if(count<maxOut) outArr[count++]=trim(cur);
    }
    return count;
}
