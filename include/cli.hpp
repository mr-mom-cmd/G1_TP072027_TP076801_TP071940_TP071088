#ifndef CLI_HPP
#define CLI_HPP

#include "models.hpp"

// Run the interactive command-line menu.
// Arrays are owned by main and passed in here.
void run_cli(Candidate candidates[], int candCount, Job jobs[], int jobCount);

#endif
