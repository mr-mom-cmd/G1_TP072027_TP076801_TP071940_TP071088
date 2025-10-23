#include "../include/ins_sort_matches_score.hpp"
#include "../include/models.hpp"

// Стабильная вставочная сортировка по score (по убыванию). При равенстве — по candId возрастанию.
void ins_sort_matches_score(ArrayList<Match>& a){
    for (int i = 1; i < a.size(); ++i){
        Match key = a[i];
        int j = i - 1;
        while (j >= 0 && (a[j].score < key.score ||
               (a[j].score == key.score && a[j].candId > key.candId))){
            a[j+1] = a[j];
            --j;
        }
        a[j+1] = key;
    }
}
