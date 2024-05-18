//
// Created by Iman Gholami on 2/24/24.
//

#ifndef CMSC701_A0_GENOME_H
#define CMSC701_A0_GENOME_H

#include <string>

namespace genome_reader {

    class genome {
    public:
        genome(const std::string& content, const std::string& header);
        genome();

        std::string content;
        std::string header;
    };

} // genome_reader

#endif //CMSC701_A0_GENOME_H
