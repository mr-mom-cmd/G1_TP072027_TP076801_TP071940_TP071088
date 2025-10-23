#ifndef RULE_BASED_PASS_HPP
#define RULE_BASED_PASS_HPP
#include "models.hpp"
// Now: pass if candidate has ALL required keywords from job (no years/location)
bool ruleBasedPass(const Candidate& c, const Job& j);
#endif
