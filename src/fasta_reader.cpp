//
// Created by Iman Gholami on 2/24/24.
//

#include <fstream>
#include "fasta_reader.h"
#include "genome.h"

namespace genome_reader {
    fasta_reader::fasta_reader(const std::string& path) {
        std::ifstream file(path);
        this->genomes.resize(0);
        while(not file.eof()) {
            std::string line;
            std::getline(file, line);
            if (line[0] == '>') {
                genome_reader::genome genome{"", line.substr(1)};
                this->genomes.push_back(genome);
            } else {
                this->genomes.back().content.append(line);
            }
        }
    }

    std::string fasta_reader::whole_genome() {
        return this->genomes[0].content;
    }
} // genome_reader