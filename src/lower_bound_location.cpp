#include "lower_bound_location.hpp"
#include "tolowerx.hpp"
#include "perf.hpp"

int lowerBoundByLocation(const Candidate arr[], int n, const std::string& key){
    ScopedTimer t(g_time_lowerupper_ms);
    int L=0,R=n; std::string k = toLower(key);
    while(L<R){
        int M=(L+R)/2;
        ++g_lower_bound_comp;
        std::string mk = toLower(arr[M].primaryKey);
        if(mk < k) L=M+1; else R=M;
    }
    return L;
}
