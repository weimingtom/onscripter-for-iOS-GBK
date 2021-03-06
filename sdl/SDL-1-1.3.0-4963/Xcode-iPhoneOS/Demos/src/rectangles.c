/*
 *	rectangles.c
 *	written by Holmes Futrell
 *	use however you want
*/

#include "SDL.h"
#include "sdl_opengles.h"
#include <time.h>
#include "common.h"

void
render(void)
{

    Uint8 r, g, b;
    /*  Come up with a random rectangle */
    SDL_Rect rect;
    rect.w = randomInt(64, 128);
    rect.h = randomInt(64, 128);
    rect.x = randomInt(0, SCREEN_WIDTH);
    rect.y = randomInt(0, SCREEN_HEIGHT);

    /* Come up with a random color */
    r = randomInt(50, 255);
    g = randomInt(50, 255);
    b = randomInt(50, 255);

    /*  Fill the rectangle in the color */
    SDL_SetRenderDrawColor(r, g, b, 255);
    SDL_RenderFill(&rect);

    /* update screen */
    SDL_RenderPresent();

}
extern SDL_Window *SDL_VideoWindow;
int
main(int argc, char *argv[])
{

    SDL_Window *window;
    int done;
    SDL_Event event;

    /* initialize SDL */
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        fatalError("Could not initialize SDL");
    }

    /* seed random number generator */
    srand(time(NULL));

    /* create window and renderer */
    window =
        SDL_CreateWindow(NULL, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT,
                         SDL_WINDOW_SHOWN);
    if (window == 0) {
        fatalError("Could not initialize Window");
    }
    if (SDL_CreateRenderer(window, -1, 0) != 0) {
        fatalError("Could not create renderer");
    }

    glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glViewport(0, 0, 640, 960);
	glRotatef(-90, 0, 0, 1);
	glOrthof(0.0, (GLfloat) 960, (GLfloat) 640, 0.0, 0, 100.0f);
    
    /* Fill screen with black */
    SDL_SetRenderDrawColor(0, 0, 0, 255);
    SDL_RenderFill(NULL);
      SDL_VideoWindow = window;
    SDL_iPhoneMoviePlay("");

    /* Enter render loop, waiting for user to quit */
    done = 0;
    while (!done) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                done = 1;
            }
        }
        render();
        SDL_Delay(1);
    }

    /* shutdown SDL */
    SDL_Quit();

    return 0;
}
