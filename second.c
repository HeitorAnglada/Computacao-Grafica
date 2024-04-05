#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <math.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480


/**
 * Struct to represent a ball.
 *
 * This struct is used to represent a ball in a 2D space. It contains
 * the coordinates (x, y) and the velocity (vx, vy) of the ball.
 */
typedef struct {
    /**
     * The x coordinate of the ball.
     */
    float x;

    /**
     * The y coordinate of the ball.
     */
    float y;

    /**
     * The x component of the velocity of the ball.
     */
    float vx;

    /**
     * The y component of the velocity of the ball.
     */
    float vy;
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
    // glewExperimental = GL_TRUE;
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

    Ball ball = {.x = 150, .y = 600, .vx = 0, .vy = 0};
    const float gravity = -0.1f;
    const float radius = 10.0f; ////// tamanho da bola
    float ramp2X1 = 150, ramp2Y1 = 50, ramp2X2 = 600, ramp2Y2 = 200; // Coordenadas da rampa2
    float ramp3X1 = 0, ramp3Y1 = 100, ramp3X2 = 100, ramp3Y2 = 0; // Coordenadas da rampa2
    float rampX1 = 450, rampY1 = 300, rampX2 = 300, rampY2 = 400; // Coordenadas da rampa
    float ramp4X1 = 0, ramp4Y1 = 150, ramp4X2 = 100, ramp4Y2 = 120; // Coordenadas da rampa

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
        if (ball.x >= rampX2 && ball.x <= rampX1){
            if ( ball.y - radius <= (rampY2 - rampY1) / (rampX2 - rampX1) * (ball.x - rampX1) + rampY1 && ball.y + radius ) {
                if (ball.y + radius >= (rampY2 - rampY1) / (rampX2 - rampX1) * (ball.x - rampX1) + rampY1) {
                    ball.vx = -2.0f; // A bola rolará para a esquerda na rampa
                    ball.vy = 0; // A velocidade Y é proporcional ao ángulo da rampa
                }
            }
        }
        // printf((rampY2 - rampY1) / (rampX2 - rampX1) * (ball.x - rampX1) + rampY1);
    

         // Detecção de colisão com a rampa
        if (ball.x <= ramp2X2 && ball.x >= ramp2X1){
            if (ball.y - radius <= ((ramp2Y1 - ramp2Y2)/ (ramp2X1 - ramp2X2) * (ball.x - ramp2X1) + ramp2Y1)) {
                if(ball.y + radius >= ((ramp2Y1 - ramp2Y2)/ (ramp2X1 - ramp2X2) * (ball.x - ramp2X1) + ramp2Y1)){
                    ball.vx = -1.7f; // A bola rolará para a direita na rampa
                    ball.vy = -ball.vy * 0.9f; // A velocidade Y é proporcional ao ângulo da rampa
                }
                
            }
        }
        
          // Detecção de colisão com a rampa
        if (ball.x <= ramp3X2 && ball.x >= ramp3X1){
            if(ball.y - radius <= (ramp3Y2 - ramp3Y1) / (ramp3X2 - ramp3X1) * (ball.x - ramp3X1) + ramp3Y1) {
                if(ball.y + radius >= (ramp3Y2 - ramp3Y1) / (ramp3X2 - ramp3X1) * (ball.x - ramp3X1) + ramp3Y1){
                    ball.vx = 2.0f; // A bola rolará para a direita na rampa
                    ball.vy = -ball.vy * 1; // A velocidade Y é proporcional ao ângulo da rampa
                }
            }
        }

         // Detecção de colisão com a rampa
        if (ball.x <= ramp4X2 && ball.x >= ramp4X1){
            if( ball.y - radius <= (ramp4Y2 - ramp4Y1) / (ramp4X2 - ramp4X1) * (ball.x - ramp4X1) + ramp4Y1) {
                if( ball.y + radius >= (ramp4Y2 - ramp4Y1) / (ramp4X2 - ramp4X1) * (ball.x - ramp4X1) + ramp4Y1){
                    ball.vx = 2.0f; // A bola rolará para a direita na rampa
                    ball.vy = -ball.vy * 0.9f; // A velocidade Y é proporcional ao ângulo da rampa
                }
            }
        }

        // Desenho da bola
        glColor3f(1.0f, 0.0f, 0.0f); // Cor vermelha
        drawCircle(ball.x, ball.y, radius, 32);

        //  // Desenho da rampa
        glColor3f(0.0f, 1.0f, 0.0f); // Cor verde para a rampa
        drawRamp(ramp4X1, ramp4Y1, ramp4X2, ramp4Y2);

        glColor3f(1.0f, 1.0f, 1.0f); // Cor verde para a rampa
        drawRamp(ramp3X1, ramp3Y1, ramp3X2, ramp3Y2);

        // Desenho da rampa
        glColor3f(0.0f, 1.0f, 0.0f); // Cor verde para a rampa
        drawRamp(rampX1, rampY1, rampX2, rampY2);

        glColor3f(1.0f, 1.0f, 0.0f); // Cor verde para a rampa
        drawRamp(ramp2X1, ramp2Y1, ramp2X2, ramp2Y2);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    // return 0;
    // gluMainLoop();
    return 0;
}
       

