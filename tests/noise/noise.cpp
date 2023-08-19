#include <common.hxx>

int main(void)
{
    display_init(RESOLUTION_320x240, DEPTH_16_BPP, 3, GAMMA_NONE, ANTIALIAS_OFF);

    rdpq_init();
    rdpq_set_mode_standard();

    rdpq_mode_blender(RDPQ_BLENDER_MULTIPLY);
    rdpq_set_prim_color(RGBA32(0, 0, 0, 255));

    while (1)
    {
        surface_t *screen = display_get();
        rdpq_attach(screen, NULL);

        // Clear screen
        rdpq_mode_combiner(RDPQ_COMBINER_FLAT);
        rdpq_set_prim_color(RGBA32(0, 0, 0, 255));
        rdpq_fill_rectangle(0, 0, width, height);

        // Triangle and rectangle with noise
        rdpq_mode_combiner(RDPQ_COMBINER1((NOISE,0,SHADE,0), (0,0,0,SHADE)));
        trishade_point_down(20, color_blue, color_red, color_green);
        rdpq_mode_combiner(RDPQ_COMBINER1((NOISE,0,PRIM,0), (0,0,0,PRIM)));
        rdpq_set_prim_color(RGBA32(255, 0, 0, 255));
        rdpq_fill_rectangle(80, height - 200, 120, 200);

        rdpq_detach();
        display_show(screen);
    }
}
