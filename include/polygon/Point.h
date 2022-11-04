

#ifndef CURAENGINE_POINT_H
#define CURAENGINE_POINT_H

#include <array>

#include "polygon/Unit.h"
#include "utils/concepts/Polygon.h"

namespace cura::poly
{

template<class Tp, std::size_t Nm = 2>
class Point : public std::array<Tp, Nm>
{
public:
    constexpr Point<Tp, Nm> operator+(const Vector auto& other) const;
    constexpr Point<Tp, Nm> operator+(const Scalar auto& magnitude) const;
};

template<Scalar Tp, std::size_t Nm = 2>
using Position = Point<units::isq::si::length<unit::base_length, Tp>, Nm>;

// CTAD
template<Scalar T, Scalar... U>
Point(T, U...) -> Point<T, 1 + sizeof...(U)>;

} // namespace cura::poly

#endif // CURAENGINE_POINT_H
