#include <stdio.h>
#include <stdlib.h>
#include <GLFW/glfw3.h>


void workerLoop(GLFWwindow *window, void (*mainWorker)(GLFWwindow*), int fps){

    double lasttime = glfwGetTime();

    while(!glfwWindowShouldClose(window)){
        mainWorker(window);
        while (glfwGetTime() < lasttime + 1.0/fps) {
                // TODO: Put the thread to sleep, yield, or simply do nothing
        }
        lasttime += 1.0/fps;
    }
}
