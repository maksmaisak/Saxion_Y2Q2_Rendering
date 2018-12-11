//
// Created by Maksym Maisak on 28/10/18.
//

#ifndef SAXION_Y2Q1_CPP_CUSTOMTYPEINDEX_H
#define SAXION_Y2Q1_CPP_CUSTOMTYPEINDEX_H

#include <numeric>

/// Assigns indices to types.
/// If a specialization's `index` is accessed with 10 different types (index<T1>, index<T2>, ... , index<T10>),
/// values 0-9 will be assigned to those types, though order is not guaranteed.
template<typename Dummy>
class CustomTypeIndex {

    inline static std::size_t m_nextIndex = 0;

public:
    template<typename T>
    inline static const std::size_t index = m_nextIndex++;
};


#endif //SAXION_Y2Q1_CPP_CUSTOMTYPEINDEX_H
