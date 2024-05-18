//
// Created by Iman Gholami on 5/3/24.
//

#include "random_order_minimizer.h"
#include <algorithm>
#include <random>
#include <fstream>

namespace suffix_array {

    random_order_minimizer::random_order_minimizer(int k, int w, std::string pattern) {
        this->k = k;
        this->w = w;
        std::vector<std::string> k_mers;
        for (int i = 0; i + k <= pattern.size(); i++) {
            k_mers.push_back(pattern.substr(i, k));
        }
        sort(k_mers.begin(), k_mers.end());
        k_mers.resize(unique(k_mers.begin(), k_mers.end()) - k_mers.begin());
        std::random_device rd;
        std::mt19937 g(rd());
        std::shuffle(k_mers.begin(), k_mers.end(), g);
        for (int i = 0; i < k_mers.size(); i++) {
            order[k_mers[i]] = i;
        }
    }

    int random_order_minimizer::get_w() {
        return w;
    }

    int random_order_minimizer::get_k() {
        return k;
    }

    int random_order_minimizer::get_type() {
        return 2;
    }

    std::vector<int> random_order_minimizer::get_indices(std::string input) {
        std::vector<int> indices;
        for (int i = 0; i + w <= input.size(); i++) {
            if (order.find(input.substr(i, k)) == order.end())
                return indices;
        }
        for (int i = 0; i + w <= input.size(); i++) {
            int min_index = i;
            for (int j = i + 1; j + k <= i + w; j++) {
                if (order[input.substr(j, k)] < order[input.substr(min_index, k)]) {
                    min_index = j;
                }
            }
            indices.push_back(min_index);
        }
        indices.resize(std::unique(indices.begin(), indices.end()) - indices.begin());
        return indices;
    }

    void random_order_minimizer::write(std::ofstream &out) {
        out.write((char*)&k, sizeof(k));
        out.write((char*)&w, sizeof(w));
        int size = order.size();
        out.write((char*)&size, sizeof(size));
        for (auto& [key, value]: order) {
            out.write(key.data(), k);
            out.write((char*)&value, sizeof(value));
        }
    }

    void random_order_minimizer::read(std::ifstream &in) {
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