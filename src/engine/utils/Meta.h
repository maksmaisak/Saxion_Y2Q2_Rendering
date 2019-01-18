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
}

#endif //SAXION_Y2Q2_RENDERING_META_H
