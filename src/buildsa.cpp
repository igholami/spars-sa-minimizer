#include <boost/program_options.hpp>
#include <iostream>
#include <fstream>

#include "fasta_reader.h"
#include "sa_index.h"
#include "cereal/archives/binary.hpp"
#include "cereal/types/vector.hpp"
#include "cereal/types/string.hpp"
#include "cereal/types/map.hpp"
#include "cereal/types/tuple.hpp"
#include "lexicographical_minimizer.h"
#include "minimizer.h"
#include "random_order_minimizer.h"
#include "frequency_minimizer.h"

namespace po = boost::program_options;
namespace gr = genome_reader;
namespace sa = suffix_array;

class input_parser {

public:
    void parse(int argc, char* argv[]) {
        po::options_description desc;
        desc.add_options()
                ("reference", po::value<std::string>(&this->reference)->required(), "Path to genome reference in FASTA format")
                ("ratio", po::value<double>(&this->ratio)->default_value(1), "Sampling ratio")
                ("k", po::value<int>(&this->k)->required(), "Size of k-mer for minimizer")
                ("w", po::value<int>(&this->w)->required(), "Size of window for minimizer")
                ("type", po::value<std::string>(&this->type)->default_value("lexicographical"), "Type of minimizer")
                ("output", po::value<std::string>(&this->output)->required(), "Path for index of suffix array")
                ;
        po::positional_options_description pd;
        pd.add("reference", 1);
        pd.add("ratio", 1);
        pd.add("k", 1);
        pd.add("w", 1);
        pd.add("type", 1);
        pd.add("output", 1);
        po::variables_map vm;
        po::store(po::command_line_parser(argc, argv).options(desc).positional(pd).run(), vm);
        po::notify(vm);
    }

    std::string reference;
    std::string output;
    int k{};
    int w{};
    double ratio;
    std::string type;
};

int main(int argc, char* argv[]) {
    input_parser inputParser;
    inputParser.parse(argc, argv);

    gr::fasta_reader fastaReader(inputParser.reference);
    std::string data = fastaReader.whole_genome();
    int new_length = ceil(data.size() * inputParser.ratio);
    data = data.substr(0,new_length) + "$";
    std::cerr << "Data size: " << data.size() << std::endl;

    sa::minimizer* m = nullptr;
    if (inputParser.type == "lexicographical") {
        m = new sa::lexicographical_minimizer(inputParser.k, inputParser.w);
    } else if (inputParser.type == "random_order") {
        m = new sa::random_order_minimizer(inputParser.k, inputParser.w, data);
    } else if (inputParser.type == "frequency") {
        m = new sa::frequency_minimizer(inputParser.k, inputParser.w, data);
    }
//    auto indices = m->get_indices(fastaReader.whole_genome());
//    int mn = indices.front();
//    int mx = indices.back();
//    for (int i = 0; i < mn; i++) indices.insert(indices.begin(), i);
//    for (int i = mx + 1; i < fastaReader.whole_genome().size(); i++) indices.push_back(i);


    sa::sa_index index(data, inputParser.ratio, m);
    index.build_faster();
    if (inputParser.type != "none")
        index.sample();
//    index.build_prefix_lookup_table();

    std::ofstream file(inputParser.output, std::ios::binary);
    index.write(file);
    file.close();

    return 0;
}
