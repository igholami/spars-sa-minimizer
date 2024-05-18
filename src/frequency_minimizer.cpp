//
// Created by Iman Gholami on 5/3/24.
//

#include "frequency_minimizer.h"
#include <algorithm>
#include <string>
#include <fstream>


namespace suffix_array {

        frequency_minimizer::frequency_minimizer(int k, int w, const std::string& pattern) {
            this->k = k;
            this->w = w;
            for (int i = 0; i + k <= pattern.size(); i++) {
                order[pattern.substr(i, k)]++;
            }
            for (auto & [key, value]: order) {
                std::cerr << key << " " << value << std::endl;
            }
        }

        std::vector<int> frequency_minimizer::get_indices(std::string pattern) {
            std::vector<int> indices;
            for (int i = 0; i + k <= pattern.size(); i++) {
                if (order.find(pattern.substr(i, k)) == order.end()) {
//                    std::cerr << "Pattern " << pattern.substr(i, k) << " not found in the order map" << std::endl;
                    return indices;
                }
            }
            for (int i = 0; i + w <= pattern.size(); i++) {
                int min_index = i;
                for (int j = i + 1; j + k <= i + w; j++) {
                    if (order[pattern.substr(j, k)] < order[pattern.substr(min_index, k)]) {
                        min_index = j;
                    }
                }
                indices.push_back(min_index);
            }
            indices.resize(std::unique(indices.begin(), indices.end()) - indices.begin());
            return indices;
        }

        int frequency_minimizer::get_w() {
            return w;
        }

        int frequency_minimizer::get_k() {
            return k;
        }

        int frequency_minimizer::get_type() {
            return 3;
        }

        void frequency_minimizer::write(std::ofstream &out) {
            out.write((char*)&k, sizeof(k));
            out.write((char*)&w, sizeof(w));
            int size = order.size();
            out.write((char*)&size, sizeof(size));
            for (auto& [key, value]: order) {
                out.write(key.data(), k);
                out.write((char*)&value, sizeof(value));
            }
        }

        void frequency_minimizer::read(std::ifstream &in) {
            in.read((char*)&k, sizeof(k));
            in.read((char*)&w, sizeof(w));
            int size;
            in.read((char*)&size, sizeof(size));
            for (int i = 0; i < size; i++) {
                std::string key;
                int value;
                key.resize(k);
                in.read(key.data(), k);
                in.read((char*)&value, sizeof(value));
                order[key] = value;
            }
        }
} // suffix_array