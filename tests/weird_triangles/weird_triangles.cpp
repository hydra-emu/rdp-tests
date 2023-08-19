#include <array>
#include <common.hxx>

int main(void)
{
    display_init(RESOLUTION_320x240, DEPTH_16_BPP, 3, GAMMA_NONE, ANTIALIAS_OFF);

    rdpq_init();
    rdpq_set_mode_standard();
    
    rdpq_mode_blender(RDPQ_BLENDER_MULTIPLY);
    rdpq_set_prim_color(RGBA32(0, 0, 0, 255));

    // These triangles abuse the fact that before/after YM a different slope is used
    // while also testing for other things
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

        // Triangle command that draws two triangles
        // Tests that after the spans cross the triangle doesn't continue drawing
        custom_triangle({ 0x0880014000f000a0,0x003c0000ffff0000,0x0014000000010000,0x00280000ffff0000 });
        // Same command but left major
        custom_triangle({ 0x080001f001a00150,0x003c0000ffff0000,0x0014000000010000,0x00280000ffff0000 });

        // Triangle command that looks like a staircase
        custom_triangle({ 0x0880014000f000a0,0x0064000000000000,0x0050000000000000,0x005a000000000000 });

        // Triangle command where YH is below YM
        // Edgewalker starts at YH so if YM is above, the slope never changes from slope M to slope L, thus slope L is used
        custom_triangle({ 0x0880014000a000f0,0x008c0000ffff0000,0x0078000000006000,0x008200000000e000 });

        // Triangle that looks like pacman
        custom_triangle({ 0x0880014001280114,0x00a400000001e000,0x009e000000000000,0x00ae0000fffe8000 });

        // More might be added...

        rdpq_detach();
        display_show(screen);
    }
}
