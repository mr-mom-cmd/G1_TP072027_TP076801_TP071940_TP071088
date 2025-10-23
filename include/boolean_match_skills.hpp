#ifndef BOOLEAN_MATCH_SKILLS_HPP
#define BOOLEAN_MATCH_SKILLS_HPP

#include <string>
#include "models.hpp"
#include "split_to_array.hpp" // даёт ArrayList<T>

/**
 * Булев матчинг кандидата к вакансии по навыкам/ключевым словам.
 *
 * Логика:
 *   - includeAll:   каждое слово/фраза должно встречаться в кандидате
 *   - includeAny:   хотя бы одно слово/фраза должно встречаться (если список не пуст)
 *   - exclude:      ни одно слово/фраза не должно встречаться
 *
 * Возвращает:
 *   -1  — кандидат отфильтрован (не прошёл условия)
 *   >=0 — score, чем больше — тем релевантнее (простая сумма весов)
 *
 * Примечание:
 *   Поиск регистронезависимый. Для эффективности используется поле Candidate::lower.
 *   Термы в списках допускаются в любом регистре — внутри функции они нормализуются.
 */
int boolean_match_skills(
    const Candidate& cand,
    const Job& job,
    const ArrayList<std::string>& includeAll,
    const ArrayList<std::string>& includeAny,
    const ArrayList<std::string>& exclude
);

#endif // BOOLEAN_MATCH_SKILLS_HPP
