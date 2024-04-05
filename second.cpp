#include <GL/glew.h>
// #include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <math.h>
#include <vector>
// #include <iostream>

#define SCREEN_WIDTH 480
#define SCREEN_HEIGHT 640


GLFWwindow* window;
GLFWwindow* gOpencGLContext = nullptr;
/**
 * Struct to represent a ball.
 *
 * This struct is used to represent a ball in a 2D space. It contains
 * the coordinates (x, y) and the velocity (vx, vy) of the ball.
 */
typedef struct {
    float x;
    float y;
    float vx;
    float vy;
} Ball;

typedef struct {
    GLfloat x;
    GLfloat y;
    GLfloat x2;
    GLfloat y2;
} Rampa;

const float radius = 10.0f; ////// tamanho da bola
const float gravity = -0.25f;

float ramp2X1 = 150, ramp2Y1 = 50, ramp2X2 = 600, ramp2Y2 = 200; // Coordenadas da rampa2
float ramp3X1 = 0, ramp3Y1 = 100, ramp3X2 = 100, ramp3Y2 = 0; // Coordenadas da rampa2
float rampX1 = 450, rampY1 = 300, rampX2 = 300, rampY2 = 400; // Coordenadas da rampa
    
Rampa ramp1 ={ .x=SCREEN_WIDTH, .y = 0, .x2 = SCREEN_WIDTH, .y2= SCREEN_HEIGHT};// Coordenadas da rampa
Rampa ramp2 ={ .x=450, .y = 0, .x2 = 450, .y2= 550};// Coordenadas da rampa
Rampa ramp3 ={ .x=0, .y = SCREEN_HEIGHT, .x2 = SCREEN_WIDTH, .y2= SCREEN_HEIGHT};// Coordenadas da rampa
Rampa ramp4 ={ .x=0, .y = 0, .x2 = 0, .y2= SCREEN_HEIGHT};// Coordenadas da rampa
Rampa ramp5 ={ .x=0, .y = 0, .x2 = 200, .y2= 0};// Coordenadas da rampa
Rampa ramp6 ={ .x=ramp5.x2+60, .y = 0, .x2 = SCREEN_WIDTH, .y2= 0};// Coordenadas da rampa
Rampa ramp7 ={ .x=ramp5.x2, .y = 0, .x2 = ramp5.x2, .y2= 50};// Coordenadas da rampa

Rampa ramp8 ={ .x=450, .y = SCREEN_HEIGHT, .x2 = SCREEN_WIDTH, .y2= 580};// Coordenadas da rampa

Rampa ramp9 ={ .x=2, .y = 100, .x2 = ramp7.x, .y2= ramp7.y2};// Coordenadas da rampa

Rampa ramp10 ={ .x=ramp6.x, .y = ramp7.y2, .x2 = ramp2.x2, .y2= ramp9.y};// Coordenadas da rampa


Ball ball = {
        .x = 465,  /* The initial x coordinate of the ball */
        .y = 15,  /* The initial y coordinate of the ball */
        .vx = 0,   /* The initial x velocity of the ball */
        .vy = 0    /* The initial y velocity of the ball */
    };

/**
 * Draws a circle using GL_TRIANGLE_FAN.
 *
 * @param cx The x-coordinate of the center of the circle
 * @param cy The y-coordinate of the center of the circle
 * @param r The radius of the circle
 * @param num_segments The number of segments to use for the circle
 */
void drawCircle(GLfloat cx, GLfloat cy, GLfloat r, int num_segments) {
    // Begin the GL_TRIANGLE_FAN primitive
    glBegin(GL_TRIANGLE_FAN);

    // Loop over each segment of the circle
    for (int ii = 0; ii < num_segments; ii++) {
        // Calculate the angle of the current segment
        GLfloat theta = 2.0f * 3.1415926f * (float)ii / (float)num_segments;

        // Calculate the x and y coordinates of the current vertex
        GLfloat x = r * cosf(theta);
        GLfloat y = r * sinf(theta);

        // Add the current vertex to the circle
        glVertex2f(x + cx, y + cy);
    }

    // End the GL_TRIANGLE_FAN primitive
    glEnd();
}

/**
 * Draws a ramp using GL_LINES.
 *
 * @param x1 The x-coordinate of the starting point of the ramp
 * @param y1 The y-coordinate of the starting point of the ramp
 * @param x2 The x-coordinate of the ending point of the ramp
 * @param y2 The y-coordinate of the ending point of the ramp
 */
void drawRamp( float x1, float y1, float x2, float y2) {
    // Set the line width to 9
    glLineWidth(9); 

    // Begin the GL_LINES primitive
    glBegin(GL_LINES);

    // Add the starting point of the ramp
    glVertex2f(x1, y1);

    // Add the ending point of the ramp
    glVertex2f(x2, y2);

    // End the GL_LINES primitive
    glEnd();
}

// void drawRamp( GLfloat <vector> vertexes) {
//     glLineWidth(9); // Define a espessura da linha da rampa
//     glBegin(GL_LINES);
//     glVertex2f(x1, y1);
//     glVertex2f(x2, y2);
//     glEnd();
// }

/**
 * Initializes the GLFW library, creates a window and sets it as the current OpenGL context.
 * Also initializes GLEW and checks for any errors.
 * Exits the program if any of these initializations fail.
 */
void Inicializar (){
    // Initialize GLFW library
    if (!glfwInit()) {
        fprintf(stderr, "Failed to initialize GLFW\n");
        exit(1);
    }

    // Create a window
    window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Rube Goldberg Machine: Bola e Rampa", NULL, NULL);
    if (!window) {
        glfwTerminate();
        fprintf(stderr, "Failed to create GLFW window\n");
        exit(1);
    }

    // Make the created window the current OpenGL context
    glfwMakeContextCurrent(window);

    // Obtain the OpenGL context obtained from GLFW
    gOpencGLContext = glfwGetCurrentContext(); 

    // Check if the OpenGL context was obtained successfully
    if(gOpencGLContext == nullptr){
        fprintf(stderr, "Failed to obtain OpenGL context\n");
        glfwTerminate();
        exit(1);
    }

    // Initialize GLEW
    GLenum err = glewInit();

    // Check if GLEW was initialized successfully
    if (err != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW: %s\n", glewGetErrorString(err));
        glfwTerminate();
        exit(1);
    }
}

/**
 * Handles user input.
 *
 * This function checks if the spacebar key is pressed and if so, it
 * increases the vertical velocity of the ball. It also prints a message
 * to the error stream.
 */
void Input(){
    // Check if the spacebar key is pressed
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
        // Increase the vertical velocity of the ball
        ball.vy += 1.0f;
    }
}

void preDraw(){
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);

    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, SCREEN_WIDTH, 0, SCREEN_HEIGHT, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glClear(GL_COLOR_BUFFER_BIT);

// Atualização da física da bola
    ball.vy += gravity; // Gravidade
    ball.y += ball.vy; // Atualização da posição Y
    ball.x += ball.vx; // Atualização da posição X

    // Detecção de colisão com o chão
    if (ball.y <= radius || ball.x <= radius || ball.y >= SCREEN_HEIGHT - radius) {
        if (ball.y <= radius) ball.y = radius;
        if (ball.x <= radius) ball.x = radius;
        if (ball.y >= SCREEN_HEIGHT - radius) ball.y = SCREEN_HEIGHT - radius;
        ball.vy *= -0.7f;
        ball.vx = 0.0f;
    }
    if(ball.x <= radius){
        ball.x = radius;
        ball.vx =  0.4f;
    }

    if((ball.y >= ramp8.y2 )){
        // ball.vy = gravity;
        ball.vx = ball.vy * 0.5f;
    }

    // // Detecção de colisão com a rampa
    // if (ball.x >= rampX2 && ball.x <= rampX1){
    //     if ( ball.y - radius <= (rampY2 - rampY1) / (rampX2 - rampX1) * (ball.x - rampX1) + rampY1 && ball.y + radius ) {
    //         if (ball.y + radius >= (rampY2 - rampY1) / (rampX2 - rampX1) * (ball.x - rampX1) + rampY1) {
    //             ball.vx = -2.0f; // A bola rolará para a esquerda na rampa
    //             ball.vy = 0; // A velocidade Y é proporcional ao ángulo da rampa
    //         }
    //     }
    // }
    // // printf((rampY2 - rampY1) / (rampX2 - rampX1) * (ball.x - rampX1) + rampY1);


    //     // Detecção de colisão com a rampa
    // if (ball.x <= ramp2X2 && ball.x >= ramp2X1){
    //     if (ball.y - radius <= ((ramp2Y1 - ramp2Y2)/ (ramp2X1 - ramp2X2) * (ball.x - ramp2X1) + ramp2Y1)) {
    //         if(ball.y + radius >= ((ramp2Y1 - ramp2Y2)/ (ramp2X1 - ramp2X2) * (ball.x - ramp2X1) + ramp2Y1)){
    //             ball.vx = -1.7f; // A bola rolará para a direita na rampa
    //             ball.vy = -ball.vy * 0.9f; // A velocidade Y é proporcional ao ângulo da rampa
    //         }
            
    //     }
    // }
    
    //     // 
    // if (ball.x <= ramp3X2 && ball.x >= ramp3X1){
    //     if(ball.y - radius <= (ramp3Y2 - ramp3Y1) / (ramp3X2 - ramp3X1) * (ball.x - ramp3X1) + ramp3Y1) {
    //         if(ball.y + radius >= (ramp3Y2 - ramp3Y1) / (ramp3X2 - ramp3X1) * (ball.x - ramp3X1) + ramp3Y1){
    //             ball.vx = 2.0f; // A bola rolará para a direita na rampa
    //             ball.vy = -ball.vy * 1; // A velocidade Y é proporcional ao ângulo da rampa
    //         }
    //     }
    // }

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
    

}

/**
 * Draws the ball and ramps on the screen.
 * Each function call draws a specific ramp or the ball.
 */
void Draw(){
    // Set the color to red for the ball
    glColor3f(1.0f, 0.0f, 0.0f); 
    // Draw the ball using the provided coordinates and radius
    drawCircle(ball.x, ball.y, radius, 32);

    // Set the color to green for the ramps
    glColor3f(0.0f, 1.0f, 0.0f); 
    // Draw each ramp using the provided coordinates
    drawRamp(ramp1.x, ramp1.y, ramp1.x2, ramp1.y2);
    drawRamp(ramp2.x, ramp2.y, ramp2.x2, ramp2.y2);
    drawRamp(ramp3.x, ramp3.y, ramp3.x2, ramp3.y2);
    drawRamp(ramp4.x, ramp4.y, ramp4.x2, ramp4.y2);
    drawRamp(ramp5.x, ramp5.y, ramp5.x2, ramp5.y2);
    drawRamp(ramp6.x, ramp6.y, ramp6.x2, ramp6.y2);
    drawRamp(ramp7.x, ramp7.y, ramp7.x2, ramp7.y2);
    drawRamp(ramp6.x, ramp7.y, ramp6.x, ramp7.y2);

    // Set the color to white for the last ramp
    glColor3f(1.0f, 1.0f, 1.0f); 
    // Draw the last ramp using the provided coordinates
    drawRamp(ramp8.x, ramp8.y, ramp8.x2, ramp8.y2);

    // Set the color to red for the last 2 ramps
    glColor3f(1.0f, 1.0f, 0.0f); 
    // Draw the last 2 ramps using the provided coordinates
    drawRamp(ramp9.x, ramp9.y, ramp9.x2, ramp9.y2);
    drawRamp(ramp10.x, ramp10.y, ramp10.x2, ramp10.y2);

    // Swap the front and back buffers of the current window
    glfwSwapBuffers(window);
    // Poll for and process events
    glfwPollEvents();
}


/**
 * The main loop of the program.
 * It keeps running as long as the GLFW window is not set to close.
 * It calls the `Input` function to handle user input,
 * the `preDraw` function to prepare the next frame,
 * and the `Draw` function to draw the scene.
 */
void MainLoop(){
    // Loop until the user closes the GLFW window
    while (!glfwWindowShouldClose(window)) {
        // Handle user input (keyboard, mouse, etc.)
        Input();
        
        // Prepare the next frame (clear screen, etc.)
        preDraw();
        
        // Draw the scene (ball, ramps, etc.)
        Draw();
    }
}


/**
 * Cleans up the resources used by the program.
 *
 * This function destroys the GLFW window and terminates the GLFW library.
 *
 */
void CleanUp(){
    // Destroy the GLFW window
    glfwDestroyWindow(window);
    
    // Terminate the GLFW library
    glfwTerminate();
}

/**
 * Entry point of the program.
 *
 * This function initializes the GLFW library, creates a window and sets it as the current OpenGL context,
 * enters the main loop, cleans up the resources used by the program and returns 0.
 *
 * @return 0 indicating successful execution
 */
int main() {
 
    // Initialize GLFW library, create a window and set it as the current OpenGL context
    Inicializar();

    // Enter the main loop, preparing the next frame, handling user input, drawing the scene, and cleaning up
    // the resources used by the program
    MainLoop();
    
    // Clean up the resources used by the program (destroy the GLFW window and terminate the GLFW library)
    CleanUp();

    // Return 0 indicating successful execution
    return 0;
}
       

