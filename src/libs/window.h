#include <stdio.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <GLFW/glfw3.h>

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

GLFWwindow *createWindow(int height, int width, char *name){
    if (!glfwInit()) {
        fprintf(stderr, "Failed to initialize GLFW\n");
        return NULL;
    }

    GLFWwindow* window = glfwCreateWindow(800, 800, name, NULL, NULL);
    if (!window) {
        fprintf(stderr, "Failed to create GLFW window\n");
        glfwTerminate();
        return NULL;
    }

    glfwMakeContextCurrent(window);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    return window;
}

void closeWindow(){
    glfwTerminate();
}

void loadSzene(GLFWwindow *window){
    glfwSwapBuffers(window);
    glfwPollEvents();
}

void getWindowSize(GLFWwindow *window, int *width, int *height){
    glfwGetFramebufferSize(window, width, height);
}

void getCursorPosition(GLFWwindow *window, double *x, double *y){
    glfwGetCursorPos(window, x, y);
}

void setWindowSize(GLFWwindow *window, int width, int height){
    glfwSetWindowSize(window, width, height);
}
