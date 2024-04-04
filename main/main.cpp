#include <SDL2/SDL.h>
#include <glad/glad.h>
#include <iostream>

// Global Variables
int gScreenHeight = 480;
int gScreenWidth = 640;

SDL_Window* gGraphicsApplicationWindow = nullptr;
SDL_GLContext gOpencGLContext = nullptr;

bool gQuit = false; // if true, quit the program

void GetOpenGlVersionInfo(){
    std::cout << "Version: " << glGetString(GL_VERSION) << std::endl;
    std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
    std::cout << "Vendor: " << glGetString(GL_VENDOR) << std::endl;
    std::cout << "Shader Language: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
}

void InitializePrograms(){
    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        exit(1);
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
    
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    gGraphicsApplicationWindow = SDL_CreateWindow("Tutorial",0,0, gScreenHeight, gScreenWidth, SDL_WINDOW_OPENGL);

    if(gGraphicsApplicationWindow == nullptr){
        std::cout << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        exit(1);
    }

    gOpencGLContext = SDL_GL_CreateContext(gGraphicsApplicationWindow);

    if(gOpencGLContext == nullptr){
        std::cout << "OpenGL context could not be created! SDL Error: " << SDL_GetError() << std::endl;
        exit(1);
    }

    // init glad
    if(!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)){
        std::cout << "Failed to initialize GLAD" << std::endl;
        exit(1);
    }
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
void PreDraw(){}

void Draw(){}


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

int main(){
    InitializePrograms();
    
    MainLoop();

    CleanUp();
    return 0;
}