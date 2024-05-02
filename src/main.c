#include <stdio.h>
#include <GLFW/glfw3.h>
#include "libs/window.h"
#include "libs/worker.h"
#include "libs/objects.h"
#include "libs/ineractions.h"

Collider *collider = NULL;

Object *player = NULL;
Object *ground = NULL;
Object *test = NULL;

void mainwin(float fb_width, float fb_height){

    float aspect_ratio = (float)fb_width / (float)fb_height;

    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-aspect_ratio, aspect_ratio, -1.0f, 1.0f, -1.0f, 1.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    drawObject(player);
    drawObject(ground);
    drawObject(test);

    glFlush();
}

void mainWorker(GLFWwindow *window){
    int fb_width, fb_height;
    double xcurs, ycurs;
    getWindowSize(window, &fb_width, &fb_height);
    getCursorPosition(window, &xcurs, &ycurs);

    if(getKey(window, 'W')) moveObject(player, 0.0, 0.005, NULL);
    if(getKey(window, 'A')) moveObject(player, -0.005, 0.0, NULL);
    if(getKey(window, 'S')) moveObject(player, 0.0, -0.005, NULL);
    if(getKey(window, 'D')) moveObject(player, 0.005, 0.0, NULL);

    mainwin(fb_width, fb_height);

    loadSzene(window);
}

int main() {

    GLFWwindow *window = createWindow(800, 800, "OpenGL");
    if(window == NULL) return -1;

    player = createObjectRectangle(-0.5, 0.5, 0.15, 0.15);
    ground = createObjectRectangle(0, -0.5, 2, 0.25);
    test = createObjectCircle(0.25, 0.5, 0.15, 25);

    addToCollider(&collider, player);
    addToCollider(&collider, ground);

    workerLoop(window, mainWorker, 30);

    closeWindow();
    return 0;
}
