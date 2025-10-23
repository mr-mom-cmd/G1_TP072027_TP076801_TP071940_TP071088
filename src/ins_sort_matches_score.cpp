#include "../include/ins_sort_cand_location.hpp"

// Вставочная (stable) сортировка: location ASC, затем id ASC.
void ins_sort_cand_location(ArrayList<Candidate>& a){
    for (int i = 1; i < a.size(); ++i){
        Candidate key = a[i];
        int j = i - 1;

        while (j >= 0){
            bool greater;
            if (a[j].location == key.location)
                greater = (a[j].id > key.id);
            else
                greater = (a[j].location > key.location);

            if (!greater) break;

            a[j + 1] = a[j];
            --j;
        }
        a[j + 1] = key;
    }
}
