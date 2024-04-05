// Third Party Includes
#include <SDL2/SDL.h>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

// C++ Standard Templates Library (STL)
#include <iostream>
#include <vector>
#include <string>
#include <fstream>

// Global Variables
int gScreenWidth = 640;
int gScreenHeight = 480;

SDL_Window* gGraphicsApplicationWindow = nullptr;
SDL_GLContext gOpencGLContext = nullptr;

bool gQuit = false; // if true, quit the program

//vao
GLuint gVertexArrayObject = 0;

//vbo
GLuint gVertexBufferObject = 0;
//ibo
//this use to store the indexes
GLuint gIndexBufferObject = 0;

GLuint gGraphicsPipelineProgram = 0;

static void GLClearErrors(){
    while(glGetError() != GL_NO_ERROR){}
}

// returns true if there are no OpenGL errors
static bool GLCheckErrorStatus(const char* function, int line){
    while (GLenum error = glGetError()){
        std::cout << "OpenGL Error: " << error << " in " << function << " at line " << line << std::endl;
        return false;
    }
    return true;
}

#define GLCheck(x) GLClearErrors(); x; GLCheckErrorStatus(#x, __LINE__);

std::string LoadShaderAsString(const std::string& filename){
    // Load the shader source code from the file
    std::string result = "";

    std::string line = "";

    std::ifstream myFile(filename.c_str());
    if(myFile.is_open()){
        while(std::getline(myFile, line)){
            result += line + '\n';
        }
        myFile.close();
    }

    return result;
}

GLuint CompilShaders(GLuint type, const std::string& source){
    
    GLuint shaderObject;
    
    if(type == GL_VERTEX_SHADER){
        shaderObject = glCreateShader(GL_VERTEX_SHADER);
    }else if(type == GL_FRAGMENT_SHADER){
        shaderObject = glCreateShader(GL_FRAGMENT_SHADER);
    }
    const char* src = source.c_str();
    glShaderSource(shaderObject, 1, &src, nullptr);
    glCompileShader(shaderObject);

    int result;
    glGetShaderiv(shaderObject, GL_COMPILE_STATUS, &result);

    if(result == GL_FALSE){
        int length;
        glGetShaderiv(shaderObject, GL_INFO_LOG_LENGTH, &length);

        char* errorMessage = new char[length];
        glGetShaderInfoLog(shaderObject, length, &length, errorMessage);
        if(type == GL_VERTEX_SHADER){
            std::cout << "Failed to compile vertex shader!" << errorMessage << std::endl;
        }else if(type == GL_FRAGMENT_SHADER){
            std::cout << "Failed to compile fragment shader!" << errorMessage << std::endl;
        }
        delete[] errorMessage;
        glDeleteShader(shaderObject);

        return 0;
    }
        
    return shaderObject;
}

GLuint CreateShaderProgram(const std::string& vertexshaderssource, const std::string& fragmentshadersource){
    GLuint programObject = glCreateProgram();
    GLuint myVertexShader = CompilShaders(GL_VERTEX_SHADER, vertexshaderssource);
    GLuint myFragmentShader = CompilShaders(GL_FRAGMENT_SHADER, fragmentshadersource);
    glAttachShader(programObject, myVertexShader);
    glAttachShader(programObject, myFragmentShader);
    glLinkProgram(programObject);

    //validate ou program
    glValidateProgram(programObject);

    return programObject;
}


/**
 * Function to create the graphics pipeline.
 * It loads the vertex and fragment shader sources,
 * creates a program object, attaches the shaders to the program,
 * and links the program.
 */
void CreateGraphicsPipeline(){
    // Load the vertex and fragment shader sources
    std::string fragmentShaderSource = LoadShaderAsString("./shaders/frag.glsl");
    std::string vertexShaderSource = LoadShaderAsString("./shaders/vert.glsl");

    // Create a program object for our shader and compile the shaders
    gGraphicsPipelineProgram = CreateShaderProgram(vertexShaderSource, fragmentShaderSource);
}

void GetOpenGlVersionInfo(){
    std::cout << "Version: " << glGetString(GL_VERSION) << std::endl;
    std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
    std::cout << "Vendor: " << glGetString(GL_VENDOR) << std::endl;
    std::cout << "Shader Language: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
}

/**
 * Function to specify the vertex data for the graphics pipeline.
 * It generates a vertex array object (VAO), and binds it. Then, it generates and binds a buffer,
 * and fills it with the vertex data. Finally, it enables the vertex attribute array, and sets the
 * vertex attribute pointer.
 */
void VertexSpecification() {
    // Define the vertex positions
    const std::vector<GLfloat> verticexData = {
        // 1 vertex
        -0.5f, -0.5f, 0.0f,  //left vertex  position
        1.0f, 0.0f, 0.0f,  // color 1
        // 1 vertex
        0.5f, -0.5f, 0.0f,   //right vertex  position
        0.0f, 1.0f, 0.0f,   // color 2
        // 2 vertex
        -0.5f,  0.5f, 0.0f,   //top vertex  position
        0.0f,  0.0f, 1.0f,   // color 3 
        // 3 vertex
        // 0.5f, -0.5f, 0.0f,  //rigth vertex  position
        // 0.0f, 1.0f, 0.0f,  // color 1
        0.5f, 0.5f, 0.0f,   //top-right vertex  position
        0.0f, 0.0f, 1.0f,   // color 2
        // -0.5f,  0.5f, 0.0f,   //top-left vertex  position
        // 0.0f,  0.0f, 1.0f    // color 3 
    };

    // Generate and bind the vertex array object (VAO)
    glGenVertexArrays(1, &gVertexArrayObject);
    glBindVertexArray(gVertexArrayObject);

    // Generate and bind the vertex array object (VAO) buffer
    glGenBuffers(1, &gVertexBufferObject);
    glBindBuffer(GL_ARRAY_BUFFER, gVertexBufferObject);

    // Fill the buffer with the vertex data
    glBufferData(GL_ARRAY_BUFFER, verticexData.size() * sizeof(GLfloat),
                  verticexData.data(), GL_STATIC_DRAW);

    // Generate and bind the index buffer object (IBO)
    const std::vector<GLuint> indexBufferData = {2,0,1,3,1,2};

    // Setup the index buffer object (IBO)
    glGenBuffers(1, &gIndexBufferObject);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gIndexBufferObject);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexBufferData.size() * sizeof(GLuint),
                 indexBufferData.data(), GL_STATIC_DRAW);
    
    // Enable the vertex attribute array
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    // Set the vertex attribute pointer
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GL_FLOAT) * 6, (void*)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(GL_FLOAT) * 6, (GLvoid*)(3 * sizeof(GL_FLOAT)));

    // Unbind the vertex array object (VAO) and disable the vertex attribute array

    glBindVertexArray(0);
    // Unbind the vertex array object (VAO) and disable the vertex attribute array
    glDisableVertexAttribArray(0);
}

/**
 * Initializes the programs and sets up the SDL and OpenGL contexts.
 * Prints error messages and exits the program if any initialization fails.
 * 
 * @throws None
 */
void InitializePrograms(){
    // Initialize SDL video subsystem
    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        exit(1);
    }

    // Set OpenGL context major and minor versions
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
    
    // Set OpenGL context profile to core
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    
    // Enable double buffering
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    
    // Set OpenGL depth size to 24 bits
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    // Create SDL window with OpenGL context
    gGraphicsApplicationWindow = SDL_CreateWindow("Tutorial",0,0, gScreenWidth, gScreenHeight, SDL_WINDOW_OPENGL);

    // Check if window creation was successful
    if(gGraphicsApplicationWindow == nullptr){
        std::cout << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        exit(1);
    }

    // Create OpenGL context
    gOpencGLContext = SDL_GL_CreateContext(gGraphicsApplicationWindow);

    // Check if OpenGL context creation was successful
    if(gOpencGLContext == nullptr){
        std::cout << "OpenGL context could not be created! SDL Error: " << SDL_GetError() << std::endl;
        exit(1);
    }

    // Initialize GLAD with OpenGL function loader
    if(!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)){
        std::cout << "Failed to initialize GLAD" << std::endl;
        exit(1);
    }

    // Print OpenGL version information
    GetOpenGlVersionInfo();
}

void Input(){
    SDL_Event e;

    while(SDL_PollEvent(&e)!=0){
        if(e.type == SDL_QUIT){
            std::cout << "SDL_QUIT" << std::endl;
            gQuit = true;
        }
    }
}

void PreDraw(){
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);

    glViewport(0, 0, gScreenWidth, gScreenHeight);
    glClearColor(0.5f, 0.6f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(gGraphicsPipelineProgram);
}

void Draw(){
    glBindVertexArray(gVertexArrayObject);
    glBindBuffer(GL_ARRAY_BUFFER, gVertexBufferObject);
    // glDrawArrays(GL_TRIANGLES, 0, 6);
    GLCheck(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0));
}

void MainLoop(){
    while(!gQuit){
        Input();

        PreDraw();

        Draw();

        //update screen
        SDL_GL_SwapWindow(gGraphicsApplicationWindow);
        // PostDraw();
        }
    }
    
void CleanUp(){
    SDL_DestroyWindow(gGraphicsApplicationWindow);
    // SDL_GL_DeleteContext(gOpencGLContext);
    SDL_Quit();
}

/**
 * The main function of the program.
 * It initializes the programs, specifies the vertex data,
 * creates the graphics pipeline, enters the main loop,
 * and cleans up after the program exits.
 *
 * @param argc the number of command line arguments
 * @param argv an array of command line arguments
 *
 * @return 0 indicating successful execution
 */
int main(int argc, char* argv[]){
    // Initializes the programs
    InitializePrograms();
    
    // Specifies the vertex data
    VertexSpecification();

    // Creates the graphics pipeline
    CreateGraphicsPipeline();

    // Enters the main loop
    MainLoop();

    // Cleans up after the program exits
    CleanUp();
    
    // Returns 0 indicating successful execution
    return 0;
}
