//
// Created by Iman Gholami on 2/24/24.
//

#include "genome.h"

namespace genome_reader {
    genome::genome(const std::string& content, const std::string& header) {
        this->header = header;
        this->content = content;
    }

    genome::genome() = default;
} // genome_reader