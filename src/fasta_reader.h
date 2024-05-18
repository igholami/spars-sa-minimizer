//
// Created by Iman Gholami on 2/24/24.
//

#ifndef CMSC701_A0_FASTA_READER_H
#define CMSC701_A0_FASTA_READER_H

#include <string>
#include <vector>
#include "genome.h"

namespace genome_reader {

    class fasta_reader {
    public:
        explicit fasta_reader(const std::string& path);
        std::string whole_genome();

        std::vector<genome> genomes;
    };

} // genome_reader

#endif //CMSC701_A0_FASTA_READER_H
