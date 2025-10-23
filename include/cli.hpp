#ifndef CLI_HPP
#define CLI_HPP

#include "models.hpp"

// Runs the interactive CLI loop.
// Arrays are owned by main; CLI just reads them.
void run_cli(Candidate candidates[], int candCount, Job jobs[], int jobCount);

#endif
