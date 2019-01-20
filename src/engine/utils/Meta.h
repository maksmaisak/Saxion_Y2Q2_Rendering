//
// Created by Maksym Maisak on 2019-01-17.
//

#ifndef SAXION_Y2Q2_RENDERING_META_H
#define SAXION_Y2Q2_RENDERING_META_H

#include "FunctionTraits.h"

namespace utils {

    // T without const, volatile, & or &&
    // unqualified_t<const std::string&> is std::string
    // Equivalent to std::remove_cvref_t from C++20
    template<typename T>
    using unqualified_t = std::remove_cv_t<std::remove_reference_t<T>>;

    template<typename T>
    using is_string = std::disjunction<
        std::is_same<std::decay_t<unqualified_t<T>>, const char*>,
        std::is_same<std::decay_t<unqualified_t<T>>, char*>,
        std::is_same<unqualified_t<T>, std::string>
    >;

    template<typename T>
    inline constexpr bool is_string_v = is_string<T>::value;
}

#endif //SAXION_Y2Q2_RENDERING_META_H
