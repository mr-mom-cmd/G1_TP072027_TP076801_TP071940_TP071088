// add_ids.cpp  — simple converter: text-only CSV  ->  id,description CSV
// Usage (PowerShell):
//   g++ -std=c++17 -O2 add_ids.cpp -o add_ids.exe
//   .\add_ids.exe .\Database\resume.csv .\Database\resume_id.csv
//   .\add_ids.exe .\Database\job_description.csv .\Database\job_description_id.csv

#include <iostream>
#include <fstream>
#include <string>

int main(int argc, char* argv[]){
    if(argc < 3){
        std::cerr << "Usage: add_ids <input.csv> <output.csv>\n";
        return 1;
    }
    std::ifstream in(argv[1]);
    if(!in){ std::cerr<<"Cannot open input: "<<argv[1]<<"\n"; return 1; }
    std::ofstream out(argv[2]);
    if(!out){ std::cerr<<"Cannot open output: "<<argv[2]<<"\n"; return 1; }

    out << "id,description\n";
    std::string line; long long id=1;
    while(std::getline(in, line)){
        // skip empty lines and any obvious header marker
        if(line.empty()) continue;
        if(line=="resume" || line=="job_description") continue;
        // write as CSV: id,<quoted description>
        out << id++ << ",\"" << line << "\"\n";
    }
    std::cout << "Wrote " << (id-1) << " rows to " << argv[2] << "\n";
    return 0;
}
