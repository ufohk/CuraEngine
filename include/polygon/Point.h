

#ifndef CURAENGINE_POINT_H
#define CURAENGINE_POINT_H

#include <array>
#include <type_traits>

#include "polygon/Unit.h"
#include "utils/concepts/Polygon.h"

#include <gsl/gsl-lite.hpp>
#include <range/v3/all.hpp>
#include <range/v3/range/conversion.hpp>
#include <range/v3/view/transform.hpp>
#include <range/v3/view/zip.hpp>
#include <range/v3/view/zip_with.hpp>

namespace cura::poly
{

template<class Tp, std::size_t Nm = 2> // TODO: figure out how to set a max size (of 3 x,y,z)
class Point
{
public:
    // types
    using value_type = Tp;
    using pointer = value_type*;
    using const_pointer = const value_type*;
    using reference = value_type&;
    using const_reference = const value_type&;
    using iterator = value_type*;
    using const_iterator = const value_type*;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    template<typename... Ts>
    constexpr explicit Point(Ts&&... args) noexcept : data_{ std::forward<Ts>(args)... }
    {
    }
    //
    //    constexpr explicit Point(ranges::any_view<Tp> rng) noexcept
    //    {
    //        for (const auto& [idx, point] : rng | ranges::views::enumerate)
    //        {
    //            data_[idx] = point;
    //        }
    //    }


    constexpr void fill(const value_type& value)
    {
        std::fill_n(begin(), size(), value);
    }

    constexpr void swap(Point& other) noexcept(std::is_nothrow_swappable_v<Point&>)
    {
        std::swap_ranges(begin(), end(), other.begin());
    }

    // Iterators.
    [[nodiscard]] constexpr iterator begin() noexcept
    {
        return std::begin(data_);
    }

    [[nodiscard]] constexpr const_iterator begin() const noexcept
    {
        return std::begin(data_);
    }

    [[nodiscard]] constexpr iterator end() noexcept
    {
        return std::end(data_);
    }

    [[nodiscard]] constexpr const_iterator end() const noexcept
    {
        return std::end(data_);
    }

    [[nodiscard]] constexpr reverse_iterator rbegin() noexcept
    {
        return std::rbegin(data_);
    }

    [[nodiscard]] constexpr const_reverse_iterator rbegin() const noexcept
    {
        return std::rbegin(data_);
    }

    [[nodiscard]] constexpr reverse_iterator rend() noexcept
    {
        return std::rend(data_);
    }

    [[nodiscard]] constexpr const_reverse_iterator rend() const noexcept
    {
        return std::rend(data_);
    }

    [[nodiscard]] constexpr const_iterator cbegin() const noexcept
    {
        return std::cbegin(data_);
    }

    [[nodiscard]] constexpr const_iterator cend() const noexcept
    {
        return std::cend(data_);
    }

    [[nodiscard]] constexpr const_reverse_iterator crbegin() const noexcept
    {
        return std::crbegin(data_);
    }

    [[nodiscard]] const_reverse_iterator crend() const noexcept
    {
        return std::crend(data_);
    }

    // Capacity.
    [[nodiscard]] constexpr size_type size() const noexcept
    {
        return Nm;
    }

    [[nodiscard]] constexpr size_type max_size() const noexcept
    {
        return Nm;
    }

    [[nodiscard]] constexpr bool empty() const noexcept
    {
        return size() == 0;
    }

    // Element access.
    [[nodiscard]] constexpr reference operator[](size_type idx) noexcept
    {
        gsl_Expects(idx < Nm);
        return data_[idx];
    }

    [[nodiscard]] constexpr const_reference operator[](size_type idx) const noexcept
    {
        gsl_Expects(idx < Nm);
        return data_[idx];
    }

    [[nodiscard]] constexpr reference at(size_type idx)
    {
        gsl_Expects(idx < Nm);
        return data_.at(idx);
    }

    [[nodiscard]] constexpr const_reference at(size_type idx) const
    {
        gsl_Expects(idx < Nm);
        return data_.at(idx);
    }

    [[nodiscard]] constexpr reference front() noexcept
    {
        return data_.front();
    }

    [[nodiscard]] constexpr const_reference front() const noexcept
    {
        return data_.front();
    }

    [[nodiscard]] constexpr reference back() noexcept
    {
        return data_.back();
    }

    [[nodiscard]] constexpr const_reference back() const noexcept
    {
        return data_.back();
    }

    [[nodiscard]] constexpr pointer data() noexcept
    {
        return data_.data();
    }

    [[nodiscard]] const_pointer data() const noexcept
    {
        return data_.data();
    }

    // Arithmetic operations
    [[nodiscard]] constexpr Point operator+(const Vector auto& other) const
    {
        // FIXME: initialize Point with a rng
        Point<Tp, Nm> p;
        for (const auto& [idx, point] : ranges::views::zip_with([](const auto& lhs, const auto& rhs) { return lhs + rhs; }, *this, other) | ranges::views::enumerate)
        {
            p[idx] = point;
        }
        return p;
    }

    [[nodiscard]] constexpr Point operator+(const Scalar auto& magnitude) const
    {
        return *this | ranges::actions::transform([magnitude](const auto& lhs) { return lhs + magnitude; }) | ranges::to<std::array<Tp, Nm>>;
    }

private:
    std::array<Tp, Nm> data_;
};

// TODO: Add free function swap

// Length unit specialization of Point
template<Scalar Tp, std::size_t Nm = 2>
using Position = Point<units::isq::si::length<unit::base_length, Tp>, Nm>;

// CTAD
template<typename Tp, typename... Up>
Point(Tp, Up...) -> Point<std::enable_if_t<(std::is_same_v<Tp, Up> && ...), Tp>, 1 + sizeof...(Up)>;

// TODO: CTAD for the Position type

} // namespace cura::poly

#endif // CURAENGINE_POINT_H
