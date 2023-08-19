// 0x0880012c01180118, 0x01480000ffff0000, 0x006e000000000000, 0x006e000000000000,
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

        rdpq_mode_combiner(RDPQ_COMBINER_FLAT);
        rdpq_set_prim_color(RGBA32(255, 255, 255, 255));

        // First test an overflowing triangle with a scissor, will not overflow at all
        rdp_set_clipping(0, 0, width, height);
        custom_triangle({ 0x0880012c01180118, 0x01480000ffff0000, 0x006e000000000000, 0x006e000000000000 });

        // Now test an overflowing triangle without a scissor, will actually overflow on real hardware
        rdp_set_clipping(0, 0, 1000, 1000);
        custom_triangle({ 0x0880022c02180218, 0x01480000ffff0000, 0x006e000000000000, 0x006e000000000000 });

        rdpq_detach();
        display_show(screen);
    }
}
