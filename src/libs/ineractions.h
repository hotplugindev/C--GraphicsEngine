#include <GLFW/glfw3.h>

int getKey(GLFWwindow *window, char key){
    return glfwGetKey(window, (int)key);
}
