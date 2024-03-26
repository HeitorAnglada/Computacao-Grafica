#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <math.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

typedef struct {
    float x, y;
    float vx, vy;
} Ball;

void drawCircle(GLfloat cx, GLfloat cy, GLfloat r, int num_segments) {
    glBegin(GL_TRIANGLE_FAN);
    for (int ii = 0; ii < num_segments; ii++) {
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

    Ball ball = {.x = 320, .y = 400, .vx = 0, .vy = 0};
    const float gravity = -0.98f;
    const float radius = 6.0f; ////// tamanho da bola
    float rampX1 = 450, rampY1 = 100, rampX2 = 300, rampY2 = 200; // Coordenadas da rampa

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        // Atualização da física da bola
        ball.vy += gravity; // Gravidade
        ball.y += ball.vy; // Atualização da posição Y
        ball.x += ball.vx; // Atualização da posição X

        // Detecção de colisão com o chão
        if (ball.y < radius) {
            ball.y = radius; // Reposiciona a bola para não afundar no chão
            ball.vy = -ball.vy * 0.7f; // Inverte a velocidade no eixo Y e aplica amortecimento
            ball.vx = 2.0f; // Aplica uma velocidade inicial no eixo X para a bola rolar
        }

        // Detecção de colisão com a rampa
        if (ball.x >= rampX2 && ball.x <= rampX1 && ball.y - radius <= (rampY2 - rampY1) / (rampX2 - rampX1) * (ball.x - rampX1) + rampY1) {
            ball.vx = 2.0f; // A bola rolará para a direita na rampa
            ball.vy = 0; // A velocidade Y é proporcional ao ângulo da rampa
        }

        // Desenho da bola
        glColor3f(1.0f, 0.0f, 0.0f); // Cor vermelha
        drawCircle(ball.x, ball.y, radius, 32);

        // Desenho da rampa
        glColor3f(0.0f, 1.0f, 0.0f); // Cor verde para a rampa
        drawRamp(rampX1, rampY1, rampX2, rampY2);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}
       
