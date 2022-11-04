#include <gtest/gtest.h>


#include <units/isq/si/length.h>

#include <fmt/format.h>

#include <polygon/Point.h>


using namespace cura;

TEST(PointTest, ctad)
{
    auto point_2d = poly::Point{ 1LL, 2 };
    EXPECT_TRUE(point_2d.max_size() == 2);
    EXPECT_TRUE(sizeof(decltype(point_2d)::value_type) >= sizeof(std::int64_t));

    auto point_3d = poly::Point{ 1, 2, 3 };
    EXPECT_TRUE(point_3d.max_size() == 3);
    EXPECT_TRUE(sizeof(decltype(point_2d)::value_type) >= sizeof(int));
}

TEST(PointTest, units)
{
    auto point_1 = poly::Position<std::int64_t, 2>{ 2000 * u::mm, 5 * u::km };
    auto point_2 = poly::Position<std::int64_t, 2>{ 2 * u::m, 40 * u::um };

    EXPECT_TRUE(point_1.at(0) == point_2.at(0));
    EXPECT_TRUE(point_1.at(1) > point_2.at(1));
}

TEST(PointTest, addition)
{
    auto point_1 = poly::Position<std::int64_t, 2>{ 2000 * u::mm, 5 * u::km };
    auto point_2 = poly::Position<std::int64_t, 2>{ 2 * u::m, 40 * u::um };

    auto point_3 = point_1 + point_2;
    EXPECT_EQ(point_3.at(0), 4 * u::m);
}
