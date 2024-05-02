#include <stdio.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <GLFW/glfw3.h>
#include "libs/shapes.h"

void mainwin(float fb_width, float fb_height, int xcurs, int ycurs){

    float aspect_ratio = (float)fb_width / (float)fb_height;

    int width =  -((fb_width / 2 - xcurs) / fb_width * 200);
    int height = (fb_height / 2 - ycurs) / fb_height * 200;

    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-aspect_ratio, aspect_ratio, -1.0f, 1.0f, -1.0f, 1.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    create_obj_qube(-50, 50, 15, aspect_ratio);
    create_obj_circle(50, 50, 10, 30, aspect_ratio);
    create_obj_circle(width, height, 8, 30, aspect_ratio);
    glFlush();
}

// Callback function to handle window resize events
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

int main() {
    // Initialize GLFW
    if (!glfwInit()) {
        fprintf(stderr, "Failed to initialize GLFW\n");
        return -1;
    }

    // Create a windowed mode window and its OpenGL context
    GLFWwindow* window = glfwCreateWindow(800, 800, "OpenGL Window", NULL, NULL);
    if (!window) {
        fprintf(stderr, "Failed to create GLFW window\n");
        glfwTerminate();
        return -1;
    }

    // Make the window's context current
    glfwMakeContextCurrent(window);

    // Set the framebuffer size callback
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Loop until the user closes the window
    while (!glfwWindowShouldClose(window)) {
        int fb_width, fb_height;
        double xcurs, ycurs;
        glfwGetFramebufferSize(window, &fb_width, &fb_height);
        glfwGetCursorPos(window, &xcurs, &ycurs);

        // Render OpenGL graphics here
        mainwin(fb_width, fb_height, (int)xcurs, (int)ycurs);

        // Swap front and back buffers
        glfwSwapBuffers(window);

        // Poll for and process events
        glfwPollEvents();
    }

    // Terminate GLFW
    glfwTerminate();
    return 0;
}
