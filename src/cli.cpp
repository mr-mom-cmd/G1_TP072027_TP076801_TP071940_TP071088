#include "cli.hpp"

#include <iostream>
#include <limits>
#include <string>

#include "linear_cand_by_id.hpp"
#include "linear_job_by_id.hpp"

#include "ins_sort_cand_location.hpp"   // now sorts by Candidate.primaryKey
#include "lower_bound_location.hpp"     // binary search on primaryKey
#include "upper_bound_location.hpp"

#include "match_for_job.hpp"
#include "boolean_match_skills.hpp"
#include "perf.hpp"
#include "tolowerx.hpp"

// ---------- tiny helpers ----------
static void flushLine() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}
static std::string readLine(const char* prompt) {
    std::cout << prompt;
    std::string s;
    std::getline(std::cin, s);
    return s;
}
static int readInt(const char* prompt, int fallback = 0) {
    std::cout << prompt;
    int x;
    if (std::cin >> x) { flushLine(); return x; }
    std::cin.clear();
    flushLine();
    return fallback;
}
static std::string snippet(const std::string& s){
    if(s.size() <= 80) return s;
    return s.substr(0,77) + "...";
}

// ---------- menu actions ----------
static void listJobs(Job jobs[], int jobCount) {
    if (jobCount == 0) { std::cout << "No jobs loaded.\n"; return; }
    std::cout << "Jobs (" << jobCount << "):\n";
    for (int i = 0; i < jobCount; ++i) {
        std::cout << "  [" << jobs[i].id << "] "
                  << snippet(jobs[i].description) << "\n";
    }
}

static void searchCandidateById(Candidate candidates[], int candCount) {
    int id = readInt("Enter candidate ID: ");
    int idx = linearSearchCandidateById(candidates, candCount, id);
    if (idx >= 0) {
        const Candidate& c = candidates[idx];
        std::cout << "Found candidate [id " << c.id << "] "
                  << snippet(c.description) << "\n";
        if(c.skillsCount>0){
            std::cout << "  Extracted skills: ";
            for(int i=0;i<c.skillsCount;++i){
                if(i) std::cout << ", ";
                std::cout << c.skills[i];
            }
            std::cout << "\n";
        }
    } else {
        std::cout << "Candidate ID " << id << " not found.\n";
    }
}

static void searchJobById(Job jobs[], int jobCount) {
    int id = readInt("Enter job ID: ");
    int idx = linearSearchJobById(jobs, jobCount, id);
    if (idx >= 0) {
        const Job& j = jobs[idx];
        std::cout << "Found job [id " << j.id << "] "
                  << snippet(j.description) << "\n";
        if(j.reqCount>0){
            std::cout << "  Required keywords: ";
            for(int i=0;i<j.reqCount;++i){
                if(i) std::cout << ", ";
                std::cout << j.required[i];
            }
            std::cout << "\n";
        }
    } else {
        std::cout << "Job ID " << id << " not found.\n";
    }
}

static void filterByPrimaryKeyword(Candidate candidates[], int candCount) {
    if (candCount == 0) { std::cout << "No candidates loaded.\n"; return; }
    std::string key = readLine("Enter keyword to filter (e.g., python): ");
    key = toLower(key);
    if (key.empty()) { std::cout << "Empty keyword.\n"; return; }

    static Candidate byKey[MAX_CANDIDATES];
    for (int i = 0; i < candCount; ++i) byKey[i] = candidates[i];

    // Sort by primaryKey (ascending)
    insertionSortCandidatesByLocation(byKey, candCount);

    // Binary search range with that key
    int L = lowerBoundByLocation(byKey, candCount, key);
    int R = upperBoundByLocation(byKey, candCount, key);

    int count = R - L;
    std::cout << "Found " << count << " candidate(s) whose primary keyword is '"
              << key << "':\n";
    for (int i = L; i < R; ++i) {
        std::cout << "  - [id " << byKey[i].id << "] "
                  << snippet(byKey[i].description) << "\n";
    }
}

static void matchJob(Job jobs[], int jobCount, Candidate candidates[], int candCount) {
    if (jobCount == 0 || candCount == 0) {
        std::cout << "Load data first.\n"; return;
    }
    int id = readInt("Enter job ID to match: ");
    int idx = linearSearchJobById(jobs, jobCount, id);
    if (idx < 0) { std::cout << "Job not found.\n"; return; }

    int top = readInt("How many top candidates to show? (e.g., 5): ", 5);
    if (top < 1) top = 1;

    MatchResult matches[MAX_MATCHES];
    int m = matchForJob(jobs[idx], candidates, candCount, matches);
    if (m == 0) { std::cout << "No matches.\n"; return; }

    if (top > m) top = m;
    std::cout << "Top " << top << " match(es) for [job " << jobs[idx].id << "]:\n";
    std::cout << "  " << snippet(jobs[idx].description) << "\n";
    for (int k = 0; k < top; ++k) {
        const Candidate& c = candidates[matches[k].candIndex];
        std::cout << "  #" << (k+1) << " [id " << c.id << "] "
                  << snippet(c.description)
                  << " (score=" << matches[k].score << ")\n";
    }
}

static void booleanSkills(Candidate candidates[], int candCount) {
    if (candCount == 0) { std::cout << "No candidates loaded.\n"; return; }
    std::string mode = toLower(readLine("Mode AND/OR? "));
    bool andMode = (mode == "and");

    std::string raw = readLine("Enter keywords separated by ';' (e.g., python;sql): ");
    if (raw.empty()) { std::cout << "No keywords provided.\n"; return; }

    // parse into fixed array
    const int MAX_KW = 16;
    std::string kw[MAX_KW];
    int cnt = 0; std::string cur;
    for (size_t i = 0; i < raw.size(); ++i) {
        if (raw[i] == ';') {
            if (!cur.empty() && cnt < MAX_KW) kw[cnt++] = toLower(cur);
            cur.clear();
        } else cur.push_back(raw[i]);
    }
    if (!cur.empty() && cnt < MAX_KW) kw[cnt++] = toLower(cur);

    int found = 0;
    for (int i = 0; i < candCount; ++i) {
        if (booleanMatchSkills(candidates[i], kw, cnt, andMode)) {
            std::cout << "  - [id " << candidates[i].id << "] "
                      << snippet(candidates[i].description) << "\n";
            ++found;
        }
    }
    std::cout << "Matched " << found << " candidate(s).\n";
}

static void showPerf() {
    std::cout << "\n=== Performance Summary ===\n";
    std::cout << "Load candidates time: " << g_time_load_candidates_ms << " ms\n";
    std::cout << "Load jobs time      : " << g_time_load_jobs_ms       << " ms\n";
    std::cout << "Sort (by key)       : " << g_time_sort_loc_ms        << " ms, "
              << "comparisons=" << g_sort_loc_comp << ", moves=" << g_sort_loc_moves << "\n";
    std::cout << "Sort (by score)     : " << g_time_sort_matches_ms    << " ms, "
              << "comparisons=" << g_sort_matches_comp << ", moves=" << g_sort_matches_moves << "\n";
    std::cout << "Lower/Upper bounds  : " << g_time_lowerupper_ms      << " ms, "
              << "lower comps=" << g_lower_bound_comp
              << ", upper comps=" << g_upper_bound_comp << "\n";
    std::cout << "Matching total time : " << g_time_match_total_ms     << " ms\n";
    std::cout << "Candidates evaluated: " << g_candidates_evaluated    << "\n\n";
}

// ---------- main loop ----------
void run_cli(Candidate candidates[], int candCount, Job jobs[], int jobCount) {
    for (;;) {
        std::cout <<
            "\n=== MENU ===\n"
            "1) List jobs\n"
            "2) Search candidate by ID (linear)\n"
            "3) Search job by ID (linear)\n"
            "4) Filter candidates by primary keyword (sort + binary)\n"
            "5) Match candidates to a job (rule+weighted)\n"
            "6) Boolean skills search (AND/OR)\n"
            "7) Show performance summary\n"
            "q) Quit\n"
            "Choice: ";
        std::string choice;
        std::getline(std::cin, choice);
        if (choice == "1")       listJobs(jobs, jobCount);
        else if (choice == "2")  searchCandidateById(candidates, candCount);
        else if (choice == "3")  searchJobById(jobs, jobCount);
        else if (choice == "4")  filterByPrimaryKeyword(candidates, candCount);
        else if (choice == "5")  matchJob(jobs, jobCount, candidates, candCount);
        else if (choice == "6")  booleanSkills(candidates, candCount);
        else if (choice == "7")  showPerf();
        else if (choice == "q" || choice == "Q") { std::cout << "Bye!\n"; break; }
        else std::cout << "Invalid choice.\n";
    }
}
