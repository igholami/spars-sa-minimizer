//
// Created by Iman Gholami on 2/24/24.
//

#ifndef CMSC701_A0_SA_INDEX_H
#define CMSC701_A0_SA_INDEX_H

#include <string>
#include <vector>
#include <map>
#include <fstream>
#include "minimizer.h"

namespace suffix_array {

    class sa_index {


    public:
        explicit sa_index(std::string input, double ratio, minimizer* m);

        int n;
        std::string input;
        std::vector<int> suffixArray;
        int k{};
        double ratio;
        std::map<std::string, std::tuple<int, int>> lookup_table;
        minimizer *m;


        void write(std::ofstream& out);
        void read(std::ifstream& in);

        sa_index() = default;

        void build();
        void build_fast();
        void build_faster();

        int naive_lcp(int suffix1, int suffix2);
        bool suffix_cmp(int suffix1, int suffix2);
        std::pair<int, int> naiveCompare(int suffix, const std::string& pattern);
        std::pair<int, int> naiveCompare(int suffix, const std::string &pattern, int ensure_cp);

        void build_prefix_lookup_table();

        void sample();

    };

} // suffix_array

#endif //CMSC701_A0_SA_INDEX_H
