//
// Created by Iman Gholami on 2/24/24.
//

#include "sa_index.h"
#include "lexicographical_minimizer.h"
#include <fstream>
#include <string>
#include <vector>
#include "minimizer.h"
#include "random_order_minimizer.h"
#include "frequency_minimizer.h"

#include <utility>

namespace suffix_array {
    sa_index::sa_index(std::string input, double ratio, minimizer *m) {
        this->n = (int)input.size();
        this->input = std::move(input);
        this->m = m;
        this->ratio = ratio;
    }

    void sa_index::build_prefix_lookup_table() {
        lookup_table.clear();
        for (int i=0; i<suffixArray.size(); i++) {
            if (suffixArray[i] + k > suffixArray.size())
                continue;
            auto key = input.substr(suffixArray[i], k);
            if (lookup_table.find(key) == lookup_table.end())
                lookup_table[key] = {i, i+1};
            lookup_table[key] = {std::get<0>(lookup_table[key]), i + 1};
        }
    };

    void sa_index::build() {
        std::vector<std::pair<std::string, int>> sa(n);
        for (int i = 0; i < n; i++)
            sa[i] = {this->input.substr(i), i};
        sort(sa.begin(), sa.end());
        this->suffixArray.resize(n);
        for (int i = 0; i < n; i++)
            this->suffixArray[i] = sa[i].second;
    }

    void sa_index::build_fast() {
        std::vector<int> sa(n);
        for (int i=0; i<n; i++) sa[i] = i;
        sort(
                sa.begin(),
                sa.end(),
                [this](int s1, int s2) {return this->suffix_cmp(s1, s2);}
                );
        this->suffixArray = std::move(sa);
    }

    void sa_index::build_faster() {
        std::vector<int> rank(n);
        std::vector<std::pair<std::pair<int, int>, int>> doubled(n);
        for (int i=0; i<n; i++)
            rank[i] = (int)input[i];
        for (int l = 0; (1 << l) <= n; l++) {
            for (int i = 0; i < n; i++) {
                if (i + (1 << l) >= n)
                    doubled[i] = {{rank[i], -1}, i};
                else
                    doubled[i] = {{rank[i], rank[i + (1 << l)]}, i};
            }
            sort(doubled.begin(), doubled.end());
            for (int i=0; i<n; i++)
                if (i == 0 || doubled[i].first != doubled[i-1].first)
                    rank[doubled[i].second] = i+1;
                else
                    rank[doubled[i].second] = rank[doubled[i-1].second];
        }
        this->suffixArray.resize(n);
        for (int i=0; i<n; i++)
            this->suffixArray[i] = doubled[i].second;
    }

    bool sa_index::suffix_cmp(int suffix1, int suffix2) {
        while (
                suffix1 < input.size() and
                suffix2 < input.size() and
                input[suffix1] == input[suffix2]
                )
            suffix1++, suffix2++;
        if (std::max(suffix1, suffix2) == input.size())
            return suffix1 > suffix2;
        return input[suffix1] < input[suffix2];

    }

    int sa_index::naive_lcp(int suffix1, int suffix2) {
        int ans = 0;
        while (
                suffix1 < input.size() and
                suffix2 < input.size() and
                input[suffix1] == input[suffix2]
                )
            suffix1++, suffix2++, ans++;
        return ans;
    }

    std::pair<int, int> sa_index::naiveCompare(int suffix, const std::string& pattern) {
        return naiveCompare(suffix, pattern, 0);
    }

    std::pair<int, int> sa_index::naiveCompare(int suffix, const std::string& pattern, int ensure_cp) {
        int ans = 0;
        suffix += ensure_cp;
        for (int i=ensure_cp; i<pattern.size(); i++) {
            auto c = pattern[i];
            ans ++;
            if (suffix >= this->input.size() or c > this->input[suffix])
                return {-1, ans};
            if (c < this->input[suffix])
                return {1, ans};
            suffix ++;
        }
        ans ++;
        return {0, ans};
    }

    void sa_index::sample() {
        std::cerr << "Original size: " << suffixArray.size() << std::endl;
        std::vector<int> indices = m->get_indices(input);
        std::cerr << "Sampled size: " << indices.size() << std::endl;
        std::vector<int> sampled;
        for (int i : suffixArray)
            if (std::binary_search(indices.begin(), indices.end(), i))
                sampled.push_back(i);
        this->suffixArray = std::move(sampled);
    }

    void sa_index::write(std::ofstream& out) {
        out.write((char*)&n, sizeof(n));
        out.write((char*)&k, sizeof(k));
        out.write((char*)&ratio, sizeof(ratio));
        int l = (int)suffixArray.size();
        out.write((char*)&l, sizeof(l));
        out.write(input.data(), n);
        for (int i : suffixArray)
            out.write((char*)&i, sizeof(i));
        int type = m ? m->get_type() : 0;
        out.write((char*)&type, sizeof(type));
        if (type)
            m->write(out);
    }

    void sa_index::read(std::ifstream& in) {
        in.read((char*)&n, sizeof(n));
        in.read((char*)&k, sizeof(k));
        in.read((char*)&ratio, sizeof(ratio));
        int l;
        in.read((char*)&l, sizeof(l));
        input.resize(n);
        in.read(input.data(), n);
        suffixArray.resize(l);
        for (int &i : suffixArray)
            in.read((char*)&i, sizeof(i));
        int type = 0;
        in.read((char*)&type, sizeof(type));
        if (type == 1)
            m = new lexicographical_minimizer();
        else if (type == 2)
            m = new random_order_minimizer();
        else if (type == 3)
            m = new frequency_minimizer();
        if (type)
            m->read(in);
    }

} // suffix_array