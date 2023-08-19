#include <array>
#include <common.hxx>

int main(void)
{
    display_init(RESOLUTION_320x240, DEPTH_16_BPP, 3, GAMMA_NONE, ANTIALIAS_OFF);

    rdpq_init();
    rdpq_set_mode_standard();
    
    rdpq_mode_combiner(RDPQ_COMBINER_FLAT);
    rdpq_mode_blender(RDPQ_BLENDER_MULTIPLY);
    rdpq_set_prim_color(RGBA32(0, 0, 0, 255));

    while (1) 
    {
        surface_t *screen = display_get();
        rdpq_attach(screen, NULL);

        // Clear screen
        rdpq_set_prim_color(RGBA32(0, 0, 0, 255));
        rdpq_fill_rectangle(0, 0, width, height);

        rdpq_set_prim_color(RGBA32(255, 255, 255, 128));
        {
            std::array<float, 6> coeffs1 = { 0, 0 };
            std::array<float, 6> coeffs2 = { width, 0 };
            std::array<float, 6> coeffs3 = { 0, height };

            rdpq_triangle(&TRIFMT_FILL,
                coeffs1.data(),
                coeffs2.data(),
                coeffs3.data()
            );
        }
        {
            std::array<float, 6> coeffs1 = { width, 0 };
            std::array<float, 6> coeffs2 = { width, height };
            std::array<float, 6> coeffs3 = { 0, height };

            rdpq_triangle(&TRIFMT_FILL,
                coeffs1.data(),
                coeffs2.data(),
                coeffs3.data()
            );
        }

        rdpq_detach();
        display_show(screen);
    }
}
