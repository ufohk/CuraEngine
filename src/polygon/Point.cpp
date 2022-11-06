
#include <gsl/gsl-lite.hpp>
#include <range/v3/to_container.hpp>
#include <range/v3/view/transform.hpp>
#include <range/v3/view/zip_with.hpp>

#include "polygon/Point.h"


namespace cura::poly
{

// template<class Tp, std::size_t Nm>
// constexpr Point<Tp, Nm> Point<Tp, Nm>::operator+(const Vector auto& other) const
//{
//     gsl_Expects(! this->empty() && ! other.empty());
//     return ranges::views::zip_with([](const auto& lhs, const auto& rhs) { return lhs + rhs; }, this, other) | ranges::to<Point<Tp, Nm>>;
// }
//
// template<class Tp, std::size_t Nm>
// constexpr Point<Tp, Nm> Point<Tp, Nm>::operator+(const Scalar auto& magnitude) const
//{
//     gsl_Expects(! this->empty());
//     return ranges::views::transform([magnitude](const auto& lhs) { return lhs + magnitude; }) | ranges::to<Point<Tp, Nm>>;
// }


} // namespace cura::poly
