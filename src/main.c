#include <stdio.h>
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "libs/window.h"
#include "libs/worker.h"
#include "libs/objects.h"
#include "libs/interactions.h"

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

    if(getKey(window, 'A')) moveObject(player, -0.01, 0.0, collider, 10);
    if(getKey(window, 'D')) moveObject(player, 0.01, 0.0, collider, 10);
    if(getKey(window, ' ') ) { moveObject(player, 0.0, 0.03, collider, 4); }
    moveObject(player, 0.0, -0.015, collider, 10);

    mainwin(fb_width, fb_height);
    loadSzene(window);
}

int main() {

    char path[1024];

    ssize_t bytes_read = readlink("/proc/self/exe", path, sizeof(path) - 1);
    if (bytes_read == -1) {
      perror("readlink");
      exit(1);
    }

    path[bytes_read] = '\0';  // Null terminate the string

    // Extract directory path (assuming the executable is not the root directory)
    char *last_slash = strrchr(path, '/');
    if (last_slash != NULL) {
      *last_slash = '\0';  // Terminate the string at the last slash
    } else {
      // Handle edge case: executable might be in the root directory (/)
      printf("Executable might be in the root directory.\n");
    }

    // Change directory using chdir
    int result = chdir(path);
    if (result == -1) {
      perror("chdir");
      exit(1);
    }

    GLFWwindow *window = createWindow(800, 800, "OpenGL");
    if(window == NULL) return -1;

    //player = createObjectPolygon(0, 0, "polygons/player.pol");
    player = createObjectPolygon(0, 0, "polygons/player.pol");
    test = createObjectRectangle(-0.5, 0.5, 0.15, 0.15);
    ground = createObjectRectangle(0, -0.5, 2, 0.02);

    addToCollider(&collider, player);
    addToCollider(&collider, ground);
    addToCollider(&collider, test);

    workerLoop(window, mainWorker, 30);

    closeWindow();
    return 0;
}
