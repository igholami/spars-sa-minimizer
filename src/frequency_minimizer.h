//
// Created by Iman Gholami on 5/3/24.
//

#ifndef CMSC701_A0_FREQUENCY_MINIMIZER_H
#define CMSC701_A0_FREQUENCY_MINIMIZER_H

#include <string>
#include <vector>
#include <fstream>
#include <map>
#include "minimizer.h"

namespace suffix_array {

    class frequency_minimizer: public minimizer {
    public:
        int k{};
        int w{};
        std::map<std::string, int> order;
    public:
        frequency_minimizer() = default;
        frequency_minimizer(int k, int w, const std::string& pattern);
        std::vector<int> get_indices(std::string pattern) override;
        int get_w() override;
        int get_k() override;
        int get_type() override;
        std::string get_type_name() override { return "frequency"; }

        void write(std::ofstream& out) override;
        void read(std::ifstream& in) override;
    };

} // suffix_array

#endif //CMSC701_A0_FREQUENCY_MINIMIZER_H
