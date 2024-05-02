#include <stdio.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <libs/shapes.h>

void displayMe(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POLYGON);
        glVertex2f(-0.25, 0.25);
        glVertex2f(0.25, -0.25);
        glVertex2f(-0.25, -0.25);
    glEnd();
    glBegin(GL_POLYGON);
        glVertex2f(-0.25, 0.25);
        glVertex2f(0.25, -0.25);
        glVertex2f(0.25, 0.25);
    glEnd();
    glFlush();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(400, 300);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Main Display");
    glutDisplayFunc(displayMe);
    glutMainLoop();
    return 0;
}
