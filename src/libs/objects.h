#include <stdlib.h>
#include <GL/gl.h>
#include <GL/glext.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <math.h>

typedef struct Polygon{
    float x;
    float y;
    struct Polygon *next;
}Polygon;


typedef struct Object{
    float x;
    float y;
    Polygon *head;
}Object;

typedef struct Collider{
    Object *Object;
    struct Collider *next;
}Collider;

Object *createObjectRectangle(float center_x, float center_y, float width, float height){
    Object *rec = (Object*)malloc(sizeof(Object));
    rec->x = center_x;
    rec->y = center_y;
    rec->head = NULL; // Initialize head to NULL
    Polygon *prev = NULL;

    float x = width/2;
    float y = height/2;

    float vertices[8] = {
        -x, y,
        x, y,
        x, -y,
        -x, -y
    };

    for (int i = 0; i < 8; i += 2){
        Polygon *current = (Polygon *)malloc(sizeof(Polygon));
        current->x = vertices[i];
        current->y = vertices[i+1];
        current->next = NULL;
        if (rec->head == NULL) {
            rec->head = current;
        } else {
            prev->next = current;
        }
        prev = current;
    }

    if (rec->head != NULL) {
        prev->next = rec->head;
    }

    return rec;
}

Object *createObjectCircle(float center_x, float center_y, float radius, int plygon_count){
    Object *circle = (Object*)malloc(sizeof(Object));
    circle->x = center_x;
    circle->y = center_y;
    circle->head = NULL; // Initialize head to NULL
    Polygon *prev = NULL;

    for (int i = 0; i < plygon_count; i++) {
        Polygon *current = (Polygon *)malloc(sizeof(Polygon));
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

void drawObject(Object *object){
    Polygon *current = object->head;
    glBegin(GL_POLYGON);
    do {
        glVertex2f(object->x + current->x, object->y + current->y);
        current = current->next;
    } while (current != object->head);
    glEnd();
}

int isContainedInObject(Object *object, float x, float y){
    Polygon *current = object->head;
    do{
        if(((x > (current->x + object->x) && x < object->x) || (x < (current->x + object->x) && x > object->x)) && ((y > (current->y + object->y) && y < object->y) || (y < (current->y + object->y) && y > object->y))) return 1;
        current = current->next;
    }while (current != object->head);
    return 0;
}

int collisionChecker(Object *object, float displacement_x, float displacement_y, Collider *collider){
    Polygon *current = object->head;
    do{
        Collider *help = collider;
        while(help != NULL){
            Object *col = help->Object;
            if(col == object) { help = help->next; continue; }
            if (isContainedInObject(col, current->x + displacement_x + object->x, current->y + displacement_y + object->y)) return 0;
            help = help->next;
        }
        current = current->next;
    }while(current != object->head);

    return 1;
}

void addToCollider(Collider **collider, Object *object){
    if(*collider == NULL){
        *collider = (Collider*)malloc(sizeof(Collider));
        (*collider)->Object = object;
        (*collider)->next = NULL;
    }else{
        Collider *current = *collider;
        while(current->next != NULL){
            current = current->next;
        }
        current->next = (Collider*)malloc(sizeof(Collider));
        current->next->Object = object;
        current->next->next = NULL;
    }
}

void moveObject(Object *object, float x_shift, float y_shift, Collider *collider){
    if(collider == NULL){
        if(x_shift > 0 && object->x < 1) object->x += x_shift;
        if(x_shift < 0 && object->x > -1) object->x += x_shift;
        if(y_shift > 0 && object->y < 1) object->y += y_shift;
        if(y_shift < 0 && object->y > -1) object->y += y_shift;
    }
    if(x_shift > 0 && object->x < 1 && collisionChecker(object, x_shift, y_shift, collider)) object->x += x_shift;
    if(x_shift < 0 && object->x > -1 && collisionChecker(object, x_shift, y_shift, collider)) object->x += x_shift;
    if(y_shift > 0 && object->y < 1 && collisionChecker(object, x_shift, y_shift, collider)) object->y += y_shift;
    if(y_shift < 0 && object->y > -1 && collisionChecker(object, x_shift, y_shift, collider)) object->y += y_shift;
}
