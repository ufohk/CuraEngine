

#ifndef CURAENGINE_POLYGON_H
#define CURAENGINE_POLYGON_H

#include <concepts>
#include <cstdint>
#include <ranges>
#include <type_traits>


namespace cura::poly
{

template<class T>
concept Scalar = std::is_integral_v<T> || std::is_integral_v<typename T::rep>;

template<class T>
concept Vector = std::ranges::range<T> && Scalar<typename T::value_type>;

template<class T, class U>
concept is_same_rank = requires(T lhs, U rhs)
{
    { lhs.size() == rhs.size() };
};


} // namespace cura::poly

#endif // CURAENGINE_POLYGON_H
