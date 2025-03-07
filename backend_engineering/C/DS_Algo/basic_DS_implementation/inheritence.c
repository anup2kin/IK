#include <stdio.h>
#include <stdlib.h>

typedef struct Shape{
    void (*draw)(struct Shape *);
} Shape;

void drawShape(Shape *s){
    printf("Drawing shape!\n");
}

typedef struct Rectangle{
    Shape base;
    int width;
    int height;
} Rectangle;

void drawRectangle(Shape *s){
    Rectangle *r = (Rectangle*)s;
    printf("Drawing rectangle with width = %d, height = %d\n", r->width, r->height);
}

Rectangle* createRectangle(int w, int h){
    Rectangle *r = (Rectangle*)malloc(sizeof(Rectangle));
    r->width = w;
    r->height = h;
    r->base.draw = drawRectangle;
    return r;
}

typedef struct Circle{
    Shape base;
    int r;
} Circle;

void drawCircle(Shape *s){
    Circle *c = (Circle*)s;
    printf("Drawing circle with radius = %d\n", c->r);
}

Circle* createCircle(int r){
    Circle *c = (Circle*)malloc(sizeof(Circle));
    c->r = r;
    c->base.draw = drawCircle;
    return c;
}


// ========================
// Test Program
// ========================
int main() {
    Shape *shapes[2];  // Array of Shape pointers for polymorphism

    // Create objects
    shapes[0] = (Shape *)createRectangle(10, 5);
    shapes[1] = (Shape *)createCircle(7);

    // Call draw() polymorphically
    for (int i = 0; i < 2; i++) {
        shapes[i]->draw(shapes[i]);  // Calls correct draw() function
    }

    // Free allocated memory
    free(shapes[0]);
    free(shapes[1]);

    return 0;
}