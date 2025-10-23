#include "../include/linear_cand_by_id.hpp"
#include "../include/models.hpp"

const Candidate* linear_cand_by_id(const ArrayList<Candidate>& cands, int id){
    for (int i = 0; i < cands.size(); ++i)
        if (cands[i].id == id) return &cands[i];
    return nullptr;
}
