#include <stdlib.h>
#include <GL/gl.h>
#include <GL/glext.h>
#include <stdio.h>
#include <math.h>

typedef struct ObjectQube{
    float x;
    float y;
    float a[2];
    float b[2];
    float c[2];
    float d[2];
}Qube;

typedef struct CirclePolygon{
    float x;
    float y;
    struct CirclePolygon *next;
}CirclePol;

typedef struct ObjectCircle{
    float x;
    float y;
    CirclePol *head;
}Circle;

Qube *createObjectQube(float center_x, float center_y, float radius){
    Qube *qube = (Qube*)malloc(sizeof(Qube));
    qube->x = center_x;
    qube->y = center_y;
    qube->a[0] = radius;
    qube->a[1] = radius;
    qube->b[0] = radius;
    qube->b[1] = radius;
    qube->c[0] = radius;
    qube->c[1] = radius;
    qube->d[0] = radius;
    qube->d[1] = radius;
    return qube;
}

Circle *createObjectCircle(float center_x, float center_y, float radius, int plygon_count){
    Circle *circle = (Circle*)malloc(sizeof(Circle));
    circle->x = center_x;
    circle->y = center_y;
    circle->head = NULL; // Initialize head to NULL
    CirclePol *prev = NULL;

    for (int i = 0; i < plygon_count; i++) {
        CirclePol *current = (CirclePol *)malloc(sizeof(CirclePol));
        float theta = 2.0f * 3.1415926f * i / plygon_count;
        float x = radius * cosf(theta);
        float y = radius * sinf(theta);
        current->x = x;
        current->y = y;
        current->next = NULL;
        if (circle->head == NULL) {
            circle->head = current;
        } else {
            prev->next = current;
        }
        prev = current;
    }

    if (circle->head != NULL) {
        prev->next = circle->head;
    }

    return circle;
}

void drawObjectQube(Qube *qube){
    glBegin(GL_POLYGON);
        glVertex2f(-(qube->a[0] - qube->x), qube->a[1] + qube->y);
        glVertex2f(-(qube->b[0] - qube->x), -(qube->b[1] - qube->y));
        glVertex2f(qube->c[0] + qube->x, -(qube->c[1] - qube->y));
        glVertex2f(qube->d[0] + qube->x, qube->d[1] + qube->y);
    glEnd();
}

void drawObjectCircle(Circle *circle){
    CirclePol *current = circle->head;
    glBegin(GL_POLYGON);
    do {
        glVertex2f(circle->x + current->x, circle->y + current->y);
        current = current->next;
    } while (current != circle->head);
    glEnd();
}
