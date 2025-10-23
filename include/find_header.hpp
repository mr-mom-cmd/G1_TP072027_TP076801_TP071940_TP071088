#ifndef FIND_HEADER_HPP
#define FIND_HEADER_HPP

#include "split_to_array.hpp"

/**
 * Эвристика: определить, является ли строка CSV заголовком.
 * На вход подаются уже разобранные по колонкам значения первой строки.
 *
 * Критерии (достаточно выполнения любого):
 *  - встречаются типичные токены: job_description, resume, text, skills, location
 *  - большинство колонок короткие (<=40 символов) и без пробелов
 */
bool csv_find_header(const ArrayList<std::string>& cols);

#endif // FIND_HEADER_HPP
