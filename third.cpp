#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <math.h>

#define SCREEN_WIDTH 480
#define SCREEN_HEIGHT 640

typedef struct {
    float x, y;
    float vx, vy;
} Ball;

void drawCircle(GLfloat cx, GLfloat cy, GLfloat r, int num_segments) {
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(cx, cy); // Centro do círculo
    for (int ii = 0; ii <= num_segments; ii++) { // <= Para fechar o círculo
        GLfloat theta = 2.0f * 3.1415926f * (float)ii / (float)num_segments;

        GLfloat x = r * cosf(theta);
        GLfloat y = r * sinf(theta);

        glVertex2f(x + cx, y + cy);
    }
    glEnd();
}

void drawRamp(float x1, float y1, float x2, float y2) {
    glLineWidth(9); // Define a espessura da linha da rampa
    glBegin(GL_LINES);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glEnd();
}

int main() {
     GLFWwindow* window;

    if (!glfwInit()) {
        fprintf(stderr, "Falha ao inicializar GLFW\n");
        return -1;
    }

    window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Rube Goldberg Machine: Bola e Rampa", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Falha ao inicializar GLEW\n");
        return -1;
    }

    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, SCREEN_WIDTH, 0, SCREEN_HEIGHT, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    while (!glfwWindowShouldClose(window)) {

    }
    
}
