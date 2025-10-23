#include "split_csv.hpp"
#include "split_to_array.hpp"

int splitCSV(const std::string& line, std::string outArr[], int maxOut){
    // Simple CSV: no quoted commas
    return splitToArray(line, ',', outArr, maxOut);
}
