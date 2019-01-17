//
// Created by Maksym Maisak on 2019-01-16.
//

#ifndef SAXION_Y2Q2_RENDERING_FUNCTIONTRAITS_H
#define SAXION_Y2Q2_RENDERING_FUNCTIONTRAITS_H

namespace utils {

    template<class F>
    struct checkDeducibleSignature {

        template<class G>
        static auto test(int) -> decltype(&G::operator(), void());

        struct dummy {};
        template<class>
        static auto test(...) -> dummy;

        using type = std::is_void<decltype(test<F>(0))>;
    };

    template<typename F>
    struct hasDeducibleSignature : checkDeducibleSignature<F>::type {};

    template<typename F>
    inline constexpr bool hasDeducibleSignature_v = hasDeducibleSignature<F>::value;

    template<typename TResult, typename TOwner, typename... TArgs>
    struct functionTraitsBase : std::true_type {

        using Result = TResult;
        using Owner  = TOwner;
        using Signature = TResult(TArgs...);
    };

    template<typename T, bool = hasDeducibleSignature_v<T>>
    struct functionTraits : std::false_type {};

    template<typename TResult, typename... Args>
    struct functionTraits<TResult(*)(Args...), false> : functionTraitsBase<TResult, void, Args...> {};

    template<typename TResult, typename TOwner, typename... Args>
    struct functionTraits<TResult(TOwner::*)(Args...), false> : functionTraitsBase<TResult, TOwner, Args...> {};

    template<typename TResult, typename... Args>
    struct functionTraits<TResult(Args...), false> : functionTraitsBase<TResult, void, Args...> {};

    template<typename TResult, typename TOwner, typename... Args>
    struct functionTraits<TResult(TOwner::*)(Args...) const, false> : functionTraitsBase<TResult, TOwner, Args...> {};

    template<typename TResult, typename... Args>
    struct functionTraits<TResult(Args...) const, false> : functionTraitsBase<TResult, void, Args...> {};

    template <typename F>
    struct functionTraits<F, true> : functionTraits<typename functionTraits<decltype(&F::operator())>::Signature> {};
}

#endif //SAXION_Y2Q2_RENDERING_FUNCTIONTRAITS_H
