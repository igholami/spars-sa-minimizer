//
// Created by Iman Gholami on 5/3/24.
//

#ifndef CMSC701_A0_RANDOM_ORDER_MINIMIZER_H
#define CMSC701_A0_RANDOM_ORDER_MINIMIZER_H

#include "minimizer.h"
#include <string>
#include <vector>
#include <fstream>
#include <map>

namespace suffix_array {

    class random_order_minimizer: public minimizer {
        int k{};
        int w{};
        std::map<std::string, int> order;
    public:
        random_order_minimizer() = default;
        random_order_minimizer(int k, int w, std::string pattern);
        std::vector<int> get_indices(std::string pattern) override;
        int get_w() override;
        int get_k() override;
        int get_type() override;
        std::string get_type_name() override { return "random_order"; }

        void write(std::ofstream& out) override;
        void read(std::ifstream& in) override;

    };

} // suffix_array

#endif //CMSC701_A0_RANDOM_ORDER_MINIMIZER_H
