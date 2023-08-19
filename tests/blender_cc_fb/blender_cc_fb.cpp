#include <common.hxx>

int main(void)
{
    display_init(RESOLUTION_320x240, DEPTH_16_BPP, 3, GAMMA_NONE, ANTIALIAS_OFF);

    rdpq_init();
    rdpq_set_mode_standard();
    
    // The following essentially sets the blender modes to:
    // rgb_a: combined_color
    // rgb_b: framebuffer_color
    // alpha_a: combined_alpha
    // alpha_b: ~combined_alpha
    // This means that an opaque pixel will just be the combined color,
    // and a transparent pixel will be the combined color blended with the framebuffer color.
    rdpq_mode_blender(RDPQ_BLENDER_MULTIPLY);
    rdpq_set_prim_color(RGBA32(255, 255, 255, 255));

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

        // Opaque triangle on top of opaque triangle
        trishade_point_down(15, color_red, color_red, color_red);
        trishade_point_up(15, color_green, color_green, color_green);

        // Transparent triangle on top of opaque triangle
        trishade_point_down(65, color_red, color_red, color_red);
        trishade_point_up(65, color_green_transparent, color_green_transparent, color_green_transparent);

        // Opaque triangle on top of transparent triangle
        trishade_point_down(115, color_red_transparent, color_red_transparent, color_red_transparent);
        trishade_point_up(115, color_green, color_green, color_green);

        // Transparent triangle on top of transparent triangle
        trishade_point_down(165, color_red_transparent, color_red_transparent, color_red_transparent);
        trishade_point_up(165, color_green_transparent, color_green_transparent, color_green_transparent);

        // Multicolor transparent triangle on top of opaque triangle
        trishade_point_down(215, color_red, color_red, color_red);
        trishade_point_up(215, color_red_transparent, color_green_transparent, color_blue_transparent);

        // Multicolor opaque triangle on top of transparent triangle
        trishade_point_down(265, color_red_transparent, color_green_transparent, color_blue_transparent);
        trishade_point_up(265, color_green, color_green, color_green);

        rdpq_detach();
        display_show(screen);
    }
}
