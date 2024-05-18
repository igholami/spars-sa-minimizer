//
// Created by Iman Gholami on 4/30/24.
//

#ifndef CMSC701_A0_LEXICOGRAPHICAL_MINIMIZER_H
#define CMSC701_A0_LEXICOGRAPHICAL_MINIMIZER_H

#include "minimizer.h"

namespace suffix_array {

    class lexicographical_minimizer: public minimizer {
        int k{};
        int w{};
    public:
        lexicographical_minimizer() = default;
        lexicographical_minimizer(int k, int w);
        std::vector<int> get_indices(std::string pattern) override;
        int get_w() override;
        int get_k() override;
        int get_type() override;
        std::string get_type_name() override { return "lexicographical"; }

        void write(std::ofstream& out) override;
        void read(std::ifstream& in) override;

    };

} // suffix_array

#endif //CMSC701_A0_LEXICOGRAPHICAL_MINIMIZER_H
