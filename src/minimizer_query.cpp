//
// Created by Iman Gholami on 4/30/24.
//

#include "minimizer_query.h"

namespace suffix_array {
    minimizer_query::minimizer_query(std::string name, std::string pattern, sa_index &index) {
        this->name = name;
        this->pattern = pattern;
        this->index = &index;
        this->start = -1;
        this->char_cmp_prefix = 0;
        auto indices = index.m->get_indices(pattern.substr(0, index.m->get_w()));
        if (!indices.empty()) {
            this->start = indices.front();
            this->q = query(name, pattern.substr(start), index, "minimizer");
        }
    }

    void minimizer_query::perform() {
        auto start_time = std::chrono::high_resolution_clock::now();
        this->char_cmp_prefix = 0;
        if (start == -1)
            return;
        q.perform();
        for (int i: q.hits) {
            if (i >= start) {
                bool found = true;
                for (int j = 0; j < start; j++) {
                    char_cmp_prefix++;
                    if (pattern[j] != index->input[i - start + j]) {
                        found = false;
                        break;
                    }
                }
                if (found)
                    hits.push_back(i - start);
            }
        }
        auto end_time = std::chrono::high_resolution_clock::now();
        duration_microsecond = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count();
    }

    int minimizer_query::get_char_cmp_prefix() {
        return char_cmp_prefix;
    }

    int minimizer_query::get_char_cmp_lb() {
        return (start == -1) ? 0 : q.char_cmp_lb;
    }

    int minimizer_query::get_char_cmp_ub() {
        return (start == -1) ? 0 : q.char_cmp_ub;
    }

    int minimizer_query::get_duration_microsecond() {
        return duration_microsecond;
    }

} // suffix_array