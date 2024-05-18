//
// Created by Iman Gholami on 4/30/24.
//

#ifndef CMSC701_A0_MINIMIZER_H
#define CMSC701_A0_MINIMIZER_H

#include <vector>
#include <string>
#include <fstream>
#include "cereal/access.hpp"

namespace suffix_array {

    class minimizer {
    public:
        virtual std::vector<int> get_indices(std::string pattern) = 0;
        virtual int get_w() = 0;
        virtual int get_k() = 0;
        virtual int get_type() = 0;
        virtual std::string get_type_name() = 0;
        template <class Archive>
        void serialize( Archive & ar ) {
            ar();
        };
        virtual void write(std::ofstream& out) = 0;
        virtual void read(std::ifstream& in) = 0;
    };

} // suffix_array

#endif //CMSC701_A0_MINIMIZER_H
