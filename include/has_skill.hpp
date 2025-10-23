#ifndef HAS_SKILL_HPP
#define HAS_SKILL_HPP

#include <string>
#include "models.hpp"

/**
 * Проверка наличия навыка у кандидата (регистронезависимо).
 * Ищет:
 *   1) точное совпадение в Candidate::skills (уже в нижнем регистре, если ты парсил так),
 *   2) подстроку в Candidate::lower.
 */
bool has_skill(const Candidate& c, const std::string& skill);

/**
 * Проверка наличия навыка в описании вакансии (регистронезависимо).
 * Ищет:
 *   1) точное в Job::skills,
 *   2) подстроку в Job::lower.
 */
bool job_has_skill(const Job& j, const std::string& skill);

#endif // HAS_SKILL_HPP
