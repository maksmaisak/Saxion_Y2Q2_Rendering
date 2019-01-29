//
// Created by Maksym Maisak on 2019-01-17.
//

#ifndef SAXION_Y2Q2_RENDERING_META_H
#define SAXION_Y2Q2_RENDERING_META_H

#include "FunctionTraits.h"

namespace utils {

    // T without const, volatile, & or &&
    // remove_cvref_t<const std::string&> is std::string
    // Equivalent to std::remove_cvref_t from C++20
    template<typename T>
    using remove_cvref_t = std::remove_cv_t<std::remove_reference_t<T>>;

    template<typename T>
    using is_string = std::disjunction<
        std::is_same<std::decay_t<remove_cvref_t<T>>, const char*>,
        std::is_same<std::decay_t<remove_cvref_t<T>>, char*>,
        std::is_same<remove_cvref_t<T>, std::string>
    >;

    template<typename T>
    inline constexpr bool is_string_v = is_string<T>::value;

    template<typename A, typename B = A, typename = void>
    struct is_equatable : std::false_type {};

    template<typename A, typename B>
    struct is_equatable<A, B, std::void_t<decltype(std::declval<A>() == std::declval<B>())>> : std::true_type {};

    template<typename A, typename B = A>
    inline constexpr bool is_equatable_v = is_equatable<A, B>::value;

    struct test {};
    static_assert(!is_equatable_v<test>);

    template<typename A, typename B = A, typename = void>
    struct equalityComparer {

        inline bool operator()(const A& a, const B& b) {
            return false;
        }
    };

    template<typename A, typename B>
    struct equalityComparer<A, B, std::enable_if_t<is_equatable_v<A, B>>> {

        inline bool operator()(const A& a, const B& b) {
            return a == b;
        }
    };
}

#endif //SAXION_Y2Q2_RENDERING_META_H
