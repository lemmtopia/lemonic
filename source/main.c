#include "lemonic.h"

int main(void)
{
    lemonic_open_window("lemonic", 640, 480);

    while (lemonic_is_running())
    {
        lemonic_update();
    }

    return 0;
}
