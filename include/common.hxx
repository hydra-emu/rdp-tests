#pragma once

#include <array>
#include <cstdint>
#include <vector>
#include <libdragon.h>

constexpr int width = 320;
constexpr int height = 240;

using my_color_t = std::array<float, 4>;

constexpr auto color_red = my_color_t{ 1, 0, 0, 1 };
constexpr auto color_green = my_color_t{ 0, 1, 0, 1 };
constexpr auto color_blue = my_color_t{ 0, 0, 1, 1 };

constexpr auto color_red_transparent = my_color_t{ 1, 0, 0, 0.5 };
constexpr auto color_green_transparent = my_color_t{ 0, 1, 0, 0.5 };
constexpr auto color_blue_transparent = my_color_t{ 0, 0, 1, 0.5 };

constexpr auto color_empty = my_color_t{ 0, 0, 0, 0 };

inline void trishade_point_down(float off_x, my_color_t vert1color, my_color_t vert2color, my_color_t vert3color)
{
    std::array<float, 6> coeffs1 = { off_x + 20, 200 };
    std::copy(vert1color.begin(), vert1color.end(), coeffs1.begin() + 2);
    std::array<float, 6> coeffs2 = { off_x + 0, height - 200 };
    std::copy(vert2color.begin(), vert2color.end(), coeffs2.begin() + 2);
    std::array<float, 6> coeffs3 = { off_x + 40, height - 200 };
    std::copy(vert3color.begin(), vert3color.end(), coeffs3.begin() + 2);

    rdpq_triangle(&TRIFMT_SHADE,
        coeffs1.data(),
        coeffs2.data(),
        coeffs3.data()
    );
}

inline void trishade_point_up(float off_x, my_color_t vert1color, my_color_t vert2color, my_color_t vert3color)
{
    std::array<float, 6> coeffs1 = { off_x + 0, 200 };
    std::copy(vert1color.begin(), vert1color.end(), coeffs1.begin() + 2);
    std::array<float, 6> coeffs2 = { off_x + 40, 200 };
    std::copy(vert2color.begin(), vert2color.end(), coeffs2.begin() + 2);
    std::array<float, 6> coeffs3 = { off_x + 20, height - 200 };
    std::copy(vert3color.begin(), vert3color.end(), coeffs3.begin() + 2);

    rdpq_triangle(&TRIFMT_SHADE,
        coeffs3.data(),
        coeffs2.data(),
        coeffs1.data()
    );
}

inline void trishade_point_right(float off_x, my_color_t vert1color, my_color_t vert2color, my_color_t vert3color)
{
    std::array<float, 6> coeffs1 = { off_x + 0, 200 };
    std::copy(vert1color.begin(), vert1color.end(), coeffs1.begin() + 2);
    std::array<float, 6> coeffs2 = { off_x + 0, height - 200 };
    std::copy(vert2color.begin(), vert2color.end(), coeffs2.begin() + 2);
    std::array<float, 6> coeffs3 = { off_x + 40, height / 2};
    std::copy(vert3color.begin(), vert3color.end(), coeffs3.begin() + 2);

    rdpq_triangle(&TRIFMT_SHADE,
        coeffs1.data(),
        coeffs2.data(),
        coeffs3.data()
    );
}

inline void trishade_point_left(float off_x, my_color_t vert1color, my_color_t vert2color, my_color_t vert3color)
{
    std::array<float, 6> coeffs1 = { off_x + 40, 200 };
    std::copy(vert1color.begin(), vert1color.end(), coeffs1.begin() + 2);
    std::array<float, 6> coeffs2 = { off_x + 40, height - 200 };
    std::copy(vert2color.begin(), vert2color.end(), coeffs2.begin() + 2);
    std::array<float, 6> coeffs3 = { off_x + 0, height / 2 };
    std::copy(vert3color.begin(), vert3color.end(), coeffs3.begin() + 2);

    rdpq_triangle(&TRIFMT_SHADE,
        coeffs1.data(),
        coeffs2.data(),
        coeffs3.data()
    );
}

inline void tridepth_point_down(float off_x, float vert1depth, float vert2depth, float vert3depth)
{
    std::array<float, 3> coeffs1 = { off_x + 20, 200, vert1depth };
    std::array<float, 3> coeffs2 = { off_x + 0, height - 200, vert2depth };
    std::array<float, 3> coeffs3 = { off_x + 40, height - 200, vert3depth };

    rdpq_triangle(&TRIFMT_ZBUF,
        coeffs1.data(),
        coeffs2.data(),
        coeffs3.data()
    );
}

inline void tridepth_point_up(float off_x, float vert1depth, float vert2depth, float vert3depth)
{
    std::array<float, 4> coeffs1 = { off_x + 0, 200, vert1depth };
    std::array<float, 4> coeffs2 = { off_x + 40, 200, vert2depth };
    std::array<float, 4> coeffs3 = { off_x + 20, height - 200, vert3depth };

    rdpq_triangle(&TRIFMT_ZBUF,
        coeffs3.data(),
        coeffs2.data(),
        coeffs1.data()
    );
}

inline void custom_triangle(std::vector<uint64_t> cmd)
{
    rspq_write_t w = rspq_write_begin(RDPQ_OVL_ID, RDPQ_CMD_TRI, cmd.size() * 2);
    for (size_t i = 0; i < cmd.size(); i++)
    {
        rspq_write_arg(&w, cmd[i] >> 32);
        rspq_write_arg(&w, cmd[i]);
    }
    rspq_write_end(&w);
}