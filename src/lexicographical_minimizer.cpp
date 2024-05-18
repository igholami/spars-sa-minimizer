//
// Created by Iman Gholami on 4/30/24.
//

#include <string>
#include <algorithm>
#include <fstream>
#include "lexicographical_minimizer.h"

namespace suffix_array {
    std::vector<int> lexicographical_minimizer::get_indices(std::string input) {
        std::vector<int> indices;
        for (int i=0; i+w<=input.size(); i++) {
            int min_index = i;
            for (int j=i+1; j+k<=i+w; j++) {
                if (input.substr(j, k) < input.substr(min_index, k))
                    min_index = j;
            }
            indices.push_back(min_index);
        }
        indices.resize(std::unique(indices.begin(), indices.end()) - indices.begin());
        return indices;
    }

    int lexicographical_minimizer::get_w() {
        return w;
    }

    int lexicographical_minimizer::get_k() {
        return k;
    }

    int lexicographical_minimizer::get_type() {
        return 1;
    }

    void lexicographical_minimizer::write(std::ofstream &out) {
        out.write((char*)&k, sizeof(k));
        out.write((char*)&w, sizeof(w));
    }

    void lexicographical_minimizer::read(std::ifstream &in) {
        in.read((char*)&k, sizeof(k));
        in.read((char*)&w, sizeof(w));
    }

    lexicographical_minimizer::lexicographical_minimizer(int k, int w) {
        this->k = k;
        this->w = w;
    }
} // suffix_array