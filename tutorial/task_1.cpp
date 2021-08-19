/*

GOAL:
Create a display window.

*/
#include <stdio.h>
#include <allegro5/allegro.h>
ALLEGRO_DISPLAY* display = NULL;
/*
    TODO: Declare display variable.
*/

const int width = 800;
const int height = 600;

void show_err_msg(int msg);
void game_init();
void game_begin();
void game_destroy();



int main(int argc, char *argv[]) {
    int msg = 0;

    printf("Hello world!!!\n");

    game_init();

    al_rest(5);     ///stop the program for 5 seconds so the window you create will stay for 5 seconds

    game_begin();

    al_rest(5);
    printf("See you, world!!\n");

    game_destroy();
    return 0;
}


void show_err_msg(int msg) {
    fprintf(stderr, "unexpected msg: %d", msg);
    game_destroy();
    exit(9);
}
/*
    The function above aims to show the error message and terminate the game.
    You may use it in any function need to deal with some error message.
    The program would not get any error if you don't utilize it,
    But you may get a tough debugging time when some mistakes happen.
    You can modify it to fit for your habit.
*/

void game_init() {
    if ( !al_init() ) {     ///al_init(), initialize the function in <allegro5/allegro.h>
        show_err_msg(-1);
    }
    display = al_create_display(width, height);     ///set the window with width and height
    al_set_window_position(display, 0, 0);      ///set the window with position
    /*
        TODO: Create your display variable.
    */
}
void game_begin() {
    al_clear_to_color(al_map_rgb(255,0,0));     ///fill the window with red
    al_flip_display();      ///display the result
    /*
        TODO: Fill the whole window with an arbitrary color, and show the window
    */
}
void game_destroy() {
    al_destroy_display(display);
    /*
        TODO: Destroy everything you have initialized or created.
    */
}
