#include "lemonic.h"

int main(void)
{
    lemonic_open_window("lemonic", 640, 480);

    while (lemonic_is_running())
    {
	lemonic_message_loop();
    }

    return 0;
}
