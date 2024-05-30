#include "defs.h"
#include "game.h"

int main(void)
{
    game g;
    game_initialize(&g);
    game_run(&g);
    game_shutdown(&g);
    return 0;
}
