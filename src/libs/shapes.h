#include <GL/gl.h>
#include <GL/glext.h>
#include <stdio.h>
#include <math.h>

void create_obj_qube(float center_x, float center_y, float radius, float aspect_ratio){

    center_x = center_x / 100;
    center_y = center_y / 100;
    radius = radius / 100;

    glBegin(GL_POLYGON);
        glVertex2f(-(radius - center_x), (radius + center_y));
        glVertex2f(-(radius - center_x), -(radius - center_y));
        glVertex2f(((radius + center_x)), -(radius - center_y));
        glVertex2f(((radius + center_x)), (radius + center_y));
    glEnd();
}

void create_obj_circle(float center_x, float center_y, float radius, int polnum, float aspect_ratio){

    center_x = center_x / 100;
    center_y = center_y / 100;
    radius = radius / 100;

    glBegin(GL_POLYGON);
    for (int i = 0; i < polnum; i++) {
        float theta = 2.0f * 3.1415926f * i / polnum; // Get the current angle
        float x = radius * cosf(theta);
        float y = radius * sinf(theta);
        glVertex2f(x + center_x, (y + center_y));
    }
    glEnd();
}
