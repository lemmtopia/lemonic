#include "l_lemonic.h"

int main(void)
{
    lemonic_open_window("lemonic", 1280, 720, 4);

    while (lemonic_is_running())
    {
        draw_pixel(60, 60, 0xff02f3);
        draw_line(2, 2, 80, 65, 0xffffff);
        draw_line(2, 2, 2, 65, 0xffffff);
        fill_rect(90, 90, 40, 80, 0xf28203);
        draw_rect(90, 90, 40, 80, 0x0909ff);

        lemonic_update();
    }

    return 0;
}
