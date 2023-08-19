#include <array>
#include <common.hxx>

int main(void)
{
    debug_init_isviewer();
    display_init(RESOLUTION_320x240, DEPTH_16_BPP, 3, GAMMA_NONE, ANTIALIAS_OFF);

    rdpq_init();
    rdpq_debug_start();
    rdpq_set_mode_standard();
    
    rdpq_mode_blender(RDPQ_BLENDER_MULTIPLY);
    rdpq_set_prim_color(RGBA32(0, 0, 0, 255));

    while (1) 
    {
        surface_t *screen = display_get();
        rdpq_attach(screen, NULL);

        // cc = (0 - 0) * 0 + primitive_color
        rdpq_mode_combiner(RDPQ_COMBINER_FLAT);

        // Clear screen
        rdpq_fill_rectangle(0, 0, width, height);

        // cc = (0 - 0) * 0 + shade_color
        rdpq_mode_combiner(RDPQ_COMBINER_SHADE);

        {
            std::array<float, 6> coeffs1 = { 0, 0, 1.0f, 1.0f, 1.0f, 0.5f };
            std::array<float, 6> coeffs2 = { width, 0, 1.0f, 1.0f, 1.0f, 0.5f };
            std::array<float, 6> coeffs3 = { 0, height, 1.0f, 1.0f, 1.0f, 0.5f };

            rdpq_triangle(&TRIFMT_SHADE,
                coeffs1.data(),
                coeffs2.data(),
                coeffs3.data()
            );
        }
        {
            std::array<float, 6> coeffs1 = { width, 0, 1.0f, 1.0f, 1.0f, 0.5f };
            std::array<float, 6> coeffs2 = { width, height, 1.0f, 1.0f, 1.0f, 0.5f };
            std::array<float, 6> coeffs3 = { 0, height, 1.0f, 1.0f, 1.0f, 0.5f };

            rdpq_triangle(&TRIFMT_SHADE,
                coeffs1.data(),
                coeffs2.data(),
                coeffs3.data()
            );
        }

        rdpq_detach();
        display_show(screen);
    }
}
