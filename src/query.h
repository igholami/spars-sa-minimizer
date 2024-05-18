//
// Created by Iman Gholami on 2/26/24.
//

#ifndef CMSC701_A0_QUERY_H
#define CMSC701_A0_QUERY_H

#include <string>
#include <vector>
#include "sa_index.h"

namespace suffix_array {

    class query {
    public:
        query() = default;
        query(std::string name, std::string pattern, sa_index& index, const std::string& mode);

        std::string name;
        std::string pattern;
        int char_cmp_lb{};
        int char_cmp_ub{};
        int pref_interval_lb{};
        int pref_interval_ub{};
        int duration_microsecond{};
        std::vector<int> hits;


        void perform();

        sa_index* index;

        std::pair<int, int> binary_search(bool isUpperBound);

        bool optimization;
    };

} // suffix_array

#endif //CMSC701_A0_QUERY_H
