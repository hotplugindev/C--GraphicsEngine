#include <stdio.h>
#include <GLFW/glfw3.h>
#include "libs/window.h"
#include "libs/worker.h"
#include "libs/objects.h"
#include "libs/ineractions.h"

Qube *player = NULL;
Circle *test = NULL;

void mainwin(float fb_width, float fb_height){

    float aspect_ratio = (float)fb_width / (float)fb_height;

    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-aspect_ratio, aspect_ratio, -1.0f, 1.0f, -1.0f, 1.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    drawObjectQube(player);
    drawObjectCircle(test);

    glFlush();
}

void mainWorker(GLFWwindow *window){
    int fb_width, fb_height;
    double xcurs, ycurs;
    getWindowSize(window, &fb_width, &fb_height);
    getCursorPosition(window, &xcurs, &ycurs);

    if(getKey(window, 'W')) player->y += 0.005;
    if(getKey(window, 'A')) player->x -= 0.005;
    if(getKey(window, 'S')) player->y -= 0.005;
    if(getKey(window, 'D')) player->x += 0.005;

    mainwin(fb_width, fb_height);

    loadSzene(window);
}

int main() {

    GLFWwindow *window = createWindow(800, 800, "OpenGL");
    if(window == NULL) return -1;

    player = createObjectQube(-0.5, 0.5, 0.15);
    test = createObjectCircle(0.5, 0.5, 0.15, 30);
    printf("%d", (int)'A');
    workerLoop(window, mainWorker, 30);

    closeWindow();
    return 0;
}
