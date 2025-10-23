#include "upper_bound_location.hpp"
#include "tolowerx.hpp"
#include "perf.hpp"

int upperBoundByLocation(const Candidate arr[], int n, const std::string& loc){
    ScopedTimer t(g_time_lowerupper_ms);
    int L=0,R=n; std::string key=toLower(loc);
    while(L<R){
        int M=(L+R)/2;
        ++g_upper_bound_comp;
        if(toLower(arr[M].location) <= key) L=M+1; else R=M;
    }
    return L;
}
