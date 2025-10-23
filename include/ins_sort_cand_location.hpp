#ifndef INS_SORT_CAND_LOCATION_HPP
#define INS_SORT_CAND_LOCATION_HPP

#include "models.hpp"

/**
 * Стабильная сортировка вставками кандидатов по:
 *   1) location (лексикографически по возрастанию),
 *   2) id (при равной location, по возрастанию).
 *
 * Нужна, чтобы затем делать бинпоиск по локации (см. lower_bound_location).
 * Оценка сложности: O(n^2), память O(1). На n≈10k приемлемо.
 */
void ins_sort_cand_location(ArrayList<Candidate>& a);

#endif // INS_SORT_CAND_LOCATION_HPP
