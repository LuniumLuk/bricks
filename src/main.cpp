#include <iostream>
#include <vector>
#include <cmath>
#include "platform.h"
#include "macro.h"
#include "image.h"
#include "timer.h"
#include "game.h"
#include "gui.h"

// A simple window API that support frame buffer swapping.
// I transported this window API from my software renderer project:
// https://github.com/LuniumLuk/soft-renderer
using namespace LuGL;

static void keyboardEventCallback(AppWindow *window, KEY_CODE key, bool pressed);
static void mouseButtonEventCallback(AppWindow *window, MOUSE_BUTTON button, bool pressed, float x, float y);
static void mouseScrollEventCallback(AppWindow *window, float offset);
static void mouseDragEventCallback(AppWindow *window, float x, float y);

int const scr_W = 512;
int const scr_H = 824;
int max_score = 0;

static AppWindow *window;
GUI gui(scr_W, scr_H, 10, 10, 2);

int main(int argc, char* argv[]) {
    initializeApplication();

    const char * title = "Bricks @ LuGL";
    Image image(scr_W, scr_H);
    window = createWindow(title, scr_W, scr_H, image.data);

    setKeyboardCallback(window, keyboardEventCallback);
    setMouseButtonCallback(window, mouseButtonEventCallback);
    setMouseScrollCallback(window, mouseScrollEventCallback);
    setMouseDragCallback(window, mouseDragEventCallback);

/////////////////////////////////////////////////////////////////////////////////////////////
////////////// G A M E   S E T U P
/////////////////////////////////////////////////////////////////////////////////////////////

    Game game(image);
    game.init();
    bool game_on = true;
    bool game_pause = true;

    SETUP_FPS();
    Timer t;
    while (!windowShouldClose(window)) {

/////////////////////////////////////////////////////////////////////////////////////////////
////////////// R E N D E R   L O O P
/////////////////////////////////////////////////////////////////////////////////////////////

        // Clear framebuffer.
        image.fill(colorf{0, 0, 0});

        game.draw();

        gui.text(image, "!!Bricks!!");
        gui.text(image, ">> Press A or D to jump <<");
        gui.text(image, (std::string("Score: ")
            + std::to_string(game.score)).c_str());
        gui.text(image, (std::string("Max Score: ")
            + std::to_string(max_score)).c_str());
        gui.text(image, "--------------------");

        if (game_on) {
            if (game_pause) {
                gui.text(image, "Game is paused");
                gui.text(image, ">> Press A or D to resume <<");
                if (isKeyDown(window, KEY_A) || isKeyDown(window, KEY_D)) {
                    game_pause = false;
                }
            }
            else {
                UserCommand command = UserCommand::None;
                if (isKeyDown(window, KEY_A))
                    command = UserCommand::JumpLeft;
                else if (isKeyDown(window, KEY_D))
                    command = UserCommand::JumpRight;

                if (game.tick(command, t.deltaTime())) {
                    game_on = false;
                    game_pause = true;
                    if (game.score > max_score) {
                        max_score = game.score;
                    }
                }
            }
        }
        else {
            gui.text(image, "Game Over!");
            if (gui.button(image, "Restart")) {
                game.init();
                game_on = true;
            }
        }

        gui.tick();

        UPDATE_FPS();
        swapBuffer(window);
        pollEvent();
    }

    terminateApplication();
    return 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////
////////////// I N P U T   C A L L B A C K S
/////////////////////////////////////////////////////////////////////////////////////////////

void keyboardEventCallback(AppWindow *window, KEY_CODE key, bool pressed) {
    __unused_variable(window);
    if (pressed) {
        switch (key) {
        case KEY_A:
            break;
        case KEY_S:
            break;
        case KEY_D:
            break;
        case KEY_W:
            break;
        case KEY_ESCAPE:
            destroyWindow(window);
            break;
        case KEY_SPACE:
            break;
        default:
            return;
        }
    }
}
void mouseButtonEventCallback(AppWindow *window, MOUSE_BUTTON button, bool pressed, float x, float y) {
    __unused_variable(window);
    gui.processMouseButtonEvent(button, pressed, x, y);
}
void mouseScrollEventCallback(AppWindow *window, float offset) {
    __unused_variable(window);
    __unused_variable(offset);
}
void mouseDragEventCallback(AppWindow *window, float x, float y) {
    __unused_variable(window);
    gui.processMouseDragEvent(x, y);
}