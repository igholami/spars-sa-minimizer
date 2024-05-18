//
// Created by Iman Gholami on 4/30/24.
//

#ifndef CMSC701_A0_MINIMIZER_QUERY_H
#define CMSC701_A0_MINIMIZER_QUERY_H

# include <string>
# include <vector>
# include "sa_index.h"
# include "minimizer.h"
#include "query.h"


namespace suffix_array {

    class minimizer_query {
    public:
        std::string name;
        std::string pattern;
        sa_index* index;
        query q;
        std::vector<int> hits;
        int start;
        int char_cmp_prefix;
        int duration_microsecond;

        minimizer_query(std::string name, std::string pattern, sa_index& index);

        void perform();

        int get_char_cmp_prefix();
        int get_char_cmp_lb();
        int get_char_cmp_ub();
        int get_duration_microsecond();

    };

} // suffix_array

#endif //CMSC701_A0_MINIMIZER_QUERY_H
