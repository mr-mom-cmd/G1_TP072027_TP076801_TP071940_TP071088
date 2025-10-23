#include "../include/lower_bound_location.hpp"
#include "../include/models.hpp"

// Предполагаем, что кандидаты ОТСОРТИРОВАНЫ по location (см. ins_sort_cand_location).
// Возвращаем первый индекс, где location >= key (аналог std::lower_bound).
int lower_bound_location(const ArrayList<Candidate>& a, const std::string& key){
    int L = 0, R = a.size();
    while (L < R){
        int M = L + (R - L) / 2;
        if (a[M].location < key) L = M + 1;
        else                     R = M;
    }
    return L; // может быть == size()
}
