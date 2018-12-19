//
// Created by Maksym Maisak on 19/12/18.
//

#ifndef SAXION_Y2Q2_RENDERING_CALLABLETRAITS_H
#define SAXION_Y2Q2_RENDERING_CALLABLETRAITS_H

#include <functional>
#include <type_traits>

namespace en {

    template<typename TCallable, typename... Args>
    inline constexpr bool isCallable = std::is_convertible_v<
        TCallable,
        std::function<void(Args...)>
    >;

    template<typename TCallable>
    inline constexpr bool isCallableParameterless = isCallable<TCallable>;
}

#endif //SAXION_Y2Q2_RENDERING_CALLABLETRAITS_H
