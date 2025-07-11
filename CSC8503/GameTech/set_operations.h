/*
 * hash_combine.h
 * This file is part of bpm21
 *
 * Copyright (C) 2020 - Giacomo Bergami
 *
 * bpm21 is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * bpm21 is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with bpm21. If not, see <http://www.gnu.org/licenses/>.
 */

//
// Created by giacomo on 17/01/21.
//

#ifndef INCONSISTENCY_DETECTOR_SET_OPERATIONS_H
#define INCONSISTENCY_DETECTOR_SET_OPERATIONS_H

#include <unordered_set>


template<typename T>
std::unordered_set<T> unordered_intersection(const std::unordered_set<T> &a,
                                             const std::unordered_set<T> &b){
    if (a.size() > b.size()) return unordered_intersection(b, a);


    std::unordered_set<T> v3;
    for (auto i = a.begin(); i != a.end(); i++) {
        if (b.find(*i) != b.end()) v3.insert(*i);
    }
    return v3;
}

template<typename T>
std::unordered_set<T> unordered_difference(const std::unordered_set<T> &a,
                                           const std::unordered_set<T> &b){
    std::unordered_set<T> v3;
    for (auto i = a.begin(); i != a.end(); i++) {
        if (b.find(*i) == b.end()) v3.insert(*i);
    }
    return v3;
}

template<typename T>
double unodreded_distance(const std::unordered_set<T> &a,
                          const std::unordered_set<T> &b) {
    if (a.size() < b.size()) return unodreded_distance(b, a);
    double total = a.size();
    for (auto i = b.begin(); i != b.end(); i++) {
        if (a.find(*i) == a.end()) total++;
    }
    if (total == 0.0) return 0.0;
    return (((double )unordered_difference(a,b).size())+((double )unordered_difference(b,a).size()))/total;
}

#include <vector>
#include <cmath>

template
        <typename T>
std::vector<std::unordered_set<T>> powerset(const std::unordered_set<T> & a) {
    std::vector<T> set{a.begin(), a.end()};
    std::vector<std::unordered_set<T>> result;
    /*set_size of power set of a set with set_size
    n is (2**n -1)*/

    unsigned long long int pow_set_size = std::pow(2, a.size()), set_size = a.size();
    unsigned long long int counter, j;

    /*Run from counter 000..0 to 111..1*/
    for(counter = 0; counter < pow_set_size; counter++)
    {
        std::unordered_set<T> subset;
        for(j = 0; j < set_size; j++)
        {

            /* Check if jth bit in the counter is set
                If set then print jth element from set */
            if(counter & (1 << j))
                subset.insert(set.at(j));
        }
        result.emplace_back(subset);
    }
    return result;
}

#include <ostream>

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::unordered_set<T> &s)
{
    os << '{';
    for (auto const& i: s) {
        os << i << ", ";
    }
    return os << '}';
}

#include <numeric>
#include <vector>

template <typename T>
std::unordered_set<std::unordered_set<T>> cartesian_product(const std::vector<std::vector<T>> & v ) {
    const long long N = std::accumulate( v.begin(), v.end(), 1LL, []( long long a, const std::vector<T>& b ) { return a*b.size(); } );
    std::unordered_set<std::unordered_set<T>> result;
    for( long long n=0 ; n<N ; ++n ) {
        lldiv_t q { n, 0 };
        std::unordered_set<T> u;
        for( long long i=v.size()-1 ; 0<=i ; --i ) {
            q = std::div( q.quot, v[i].size() );
            u.insert(v[i][q.rem]);
            //u[i] = v[i][q.rem];
        }
        result.insert(u);
    }
    return result;
}
/*
template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T> &s)
{
    os << '[';
    for (auto const& i: s) {
        os << i << ", ";
    }
    return os << ']';
}*/

#include <map>
#include <functional>

template <typename Iterator, typename Key, typename Value>
std::map<Key, std::vector<Value>> GroupByKeyExtractor(Iterator begin, Iterator end, std::function<Key(const Value&)> keyExtractor)
{
    DEBUG_ASSERT(std::is_sorted(begin, end));
    std::map<Key, std::vector<Value>> groups;
    decltype(end) upper;

    for(auto lower = begin; lower != end; lower = upper)
    {
        Key k = keyExtractor(*lower);

        // get the upper position of all elements with the same ID
        upper = std::upper_bound(begin, end,  *lower,[keyExtractor](const Value& x, const Value& y) { return keyExtractor(x) < keyExtractor(y); });

        // add those elements as a group to the output vector
        groups[k] = {lower, upper};
    }

    return groups;
}

template <typename Iterator, typename Key, typename Value>
std::vector<std::pair<Key, std::vector<Value>>> GroupByKeyExtractorAsVector(Iterator begin, Iterator end, std::function<Key(const Value&)> keyExtractor)
{
    DEBUG_ASSERT(std::is_sorted(begin, end));
    std::vector<std::pair<Key, std::vector<Value>>> groups;
    decltype(end) upper;

    for(auto lower = begin; lower != end; lower = upper)
    {
        Key k = keyExtractor(*lower);

        // get the upper position of all elements with the same ID
        upper = std::upper_bound(begin, end,  *lower,[keyExtractor](const Value& x, const Value& y) { return keyExtractor(x) < keyExtractor(y); });

        // add those elements as a group to the output vector
        groups.emplace_back(k, std::vector<Value>{lower, upper});
    }

    return groups;
}

#include <cassert>

template <typename Iterator, typename Key, typename Value>
std::vector<std::vector<Value>> GroupByKeyExtractorIgnoreKey(Iterator begin, Iterator end, std::function<Key(const Value&)> keyExtractor)
{
    DEBUG_ASSERT(std::is_sorted(begin, end));
    std::vector<std::vector<Value>> groups;
    decltype(end) upper;

    for(auto lower = begin; lower != end; lower = upper)
    {
        Key k = keyExtractor(*lower);

        // get the upper position of all elements with the same ID
        upper = std::upper_bound(begin, end,  *lower,[keyExtractor](const Value& x, const Value& y) { return keyExtractor(x) < keyExtractor(y); });

        // add those elements as a group to the output vector
        groups.emplace_back(std::vector<Value>{lower, upper});
    }

    return groups;
}

template <typename T>
void remove_duplicates(std::vector<T>& vec){
    std::sort(vec.begin(), vec.end());
    vec.erase(std::unique(vec.begin(), vec.end()), vec.end());
}


#endif //INCONSISTENCY_DETECTOR_SET_OPERATIONS_H
