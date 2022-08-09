// Copyright (c) 2022 Ultimaker B.V.
// CuraEngine is released under the terms of the AGPLv3 or higher

#ifndef CURAENGINE_CONCEPTS_H
#define CURAENGINE_CONCEPTS_H

#include <concepts>
#include <string_view>

namespace cura
{

template<typename T>
concept StringLike = std::convertible_to<T, std::string_view>;

} // namespace cura

#endif // CURAENGINE_CONCEPTS_H
