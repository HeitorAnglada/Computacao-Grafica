// #include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <math.h>

#define SCREEN_WIDTH 480
#define SCREEN_HEIGHT 640


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
    float x2;

    /**
     * The y component of the velocity of the ball.
     */
    float y2;
} Rampa;




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

void drawRamp( float x1, float y1, float x2, float y2) {
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
    // if (glewInit() != GLEW_OK) {
    //     fprintf(stderr, "Falha ao inicializar GLEW\n");
    //     return -1;
    // }

    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    /*
     * Set the orthographic projection matrix.
     * The function glOrtho() sets up a 2D projection matrix,
     * defining what 2D coordinates map to 3D coordinates.
     *
     * @param left The coordinates for the left vertical clipping plane
     * @param right The coordinates for the right vertical clipping plane
     * @param bottom The coordinates for the bottom horizontal clipping plane
     * @param top The coordinates for the top horizontal clipping plane
     * @param zNear The coordinates for the near depth clipping plane (always -1)
     * @param zFar The coordinates for the far depth clipping plane (always 1)
     */
    glOrtho(0, SCREEN_WIDTH, 0, SCREEN_HEIGHT, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    /*
     * Ball struct to represent the ball in the simulation.
     *
     * @field x The x coordinate of the ball
     * @field y The y coordinate of the ball
     * @field vx The x velocity of the ball
     * @field vy The y velocity of the ball
     */
    Ball ball = {
        .x = 465,  /* The initial x coordinate of the ball */
        .y = 15,  /* The initial y coordinate of the ball */
        .vx = 0,   /* The initial x velocity of the ball */
        .vy = 0    /* The initial y velocity of the ball */
    };
    const float gravity = -0.1f;
    const float radius = 10.0f; ////// tamanho da bola
    float ramp2X1 = 150, ramp2Y1 = 50, ramp2X2 = 600, ramp2Y2 = 200; // Coordenadas da rampa2
    float ramp3X1 = 0, ramp3Y1 = 100, ramp3X2 = 100, ramp3Y2 = 0; // Coordenadas da rampa2
    float rampX1 = 450, rampY1 = 300, rampX2 = 300, rampY2 = 400; // Coordenadas da rampa
    
    Rampa ramp1 ={ .x=480, .y = 0, .x2 = 480, .y2= 640};// Coordenadas da rampa
    Rampa ramp2 ={ .x=450, .y = 0, .x2 = 450, .y2= 550};// Coordenadas da rampa
    Rampa ramp3 ={ .x=0, .y = 640, .x2 = 480, .y2= 640};// Coordenadas da rampa
    Rampa ramp4 ={ .x=0, .y = 0, .x2 = 0, .y2= 640};// Coordenadas da rampa
    Rampa ramp5 ={ .x=0, .y = 0, .x2 = 200, .y2= 0};// Coordenadas da rampa
    Rampa ramp6 ={ .x=ramp5.x2+60, .y = 0, .x2 = 480, .y2= 0};// Coordenadas da rampa
    Rampa ramp7 ={ .x=ramp5.x2, .y = 0, .x2 = ramp5.x2, .y2= 50};// Coordenadas da rampa

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        // Atualização da física da bola
        // ball.vy += gravity; // Gravidade
        ball.y += ball.vy; // Atualização da posição Y
        // ball.x += ball.vx; // Atualização da posição X

        // Detecção de colisão com o chão
        if (ball.y < radius) {
            ball.y = radius; // Reposiciona a bola para não afundar no chão
            // ball.vy = ball.vy * 0.7f; // Inverte a velocidade no eixo Y e aplica amortecimento
            ball.vx = 0.0f; // Aplica uma velocidade inicial no eixo X para a bola rolar
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
        
          // 
        if (ball.x <= ramp3X2 && ball.x >= ramp3X1){
            if(ball.y - radius <= (ramp3Y2 - ramp3Y1) / (ramp3X2 - ramp3X1) * (ball.x - ramp3X1) + ramp3Y1) {
                if(ball.y + radius >= (ramp3Y2 - ramp3Y1) / (ramp3X2 - ramp3X1) * (ball.x - ramp3X1) + ramp3Y1){
                    ball.vx = 2.0f; // A bola rolará para a direita na rampa
                    ball.vy = -ball.vy * 1; // A velocidade Y é proporcional ao ângulo da rampa
                }
            }
        }

        //  // Detecção de colisão com a rampa
        // if (ball.x <= ramp4X2 && ball.x >= ramp4X1){
        //     if( ball.y - radius <= (ramp4Y2 - ramp4Y1) / (ramp4X2 - ramp4X1) * (ball.x - ramp4X1) + ramp4Y1) {
        //         if( ball.y + radius >= (ramp4Y2 - ramp4Y1) / (ramp4X2 - ramp4X1) * (ball.x - ramp4X1) + ramp4Y1){
        //             ball.vx = 2.0f; // A bola rolará para a direita na rampa
        //             ball.vy = -ball.vy * 0.9f; // A velocidade Y é proporcional ao ângulo da rampa
        //         }
        //     }
        // }

        // Desenho da bola
        glColor3f(1.0f, 0.0f, 0.0f); // Cor vermelha
        drawCircle(ball.x, ball.y, radius, 32);

        //  // Desenho da rampa
        glColor3f(0.0f, 1.0f, 0.0f); // Cor verde para a rampa
        // drawRamp(ramp4X1, ramp4Y1, ramp4X2, ramp4Y2);

        glColor3f(1.0f, 1.0f, 1.0f); // Cor verde para a rampa
        drawRamp(ramp3X1, ramp3Y1, ramp3X2, ramp3Y2);

        // Desenho da rampa
        glColor3f(0.0f, 1.0f, 0.0f); // Cor verde para a rampa
        drawRamp(ramp1.x, ramp1.y, ramp1.x2, ramp1.y2);
        drawRamp(ramp2.x, ramp2.y, ramp2.x2, ramp2.y2);
        drawRamp(ramp3.x, ramp3.y, ramp3.x2, ramp3.y2);
        drawRamp(ramp4.x, ramp4.y, ramp4.x2, ramp4.y2);
        drawRamp(ramp5.x, ramp5.y, ramp5.x2, ramp5.y2);
        drawRamp(ramp6.x, ramp6.y, ramp6.x2, ramp6.y2);
        drawRamp(ramp7.x, ramp7.y, ramp7.x2, ramp7.y2);
        drawRamp(ramp6.x, ramp7.y, ramp6.x, ramp7.y2);

        glColor3f(1.0f, 1.0f, 0.0f); // Cor verde para a rampa
        drawRamp(ramp2X1, ramp2Y1, ramp2X2, ramp2Y2);

        glfwSwapBuffers(window);
        glfwPollEvents();
    };
    glfwTerminate();
    // return 0;
    // gluMainLoop();
    return 0;
}
       

