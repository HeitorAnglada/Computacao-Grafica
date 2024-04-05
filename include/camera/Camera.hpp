#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class Camera{
    public:
    // Default constructor
    Camera();
    
    /// The ultimate view matrix of the camera
    glm::mat4 GetViewMatrix() const;
    void MoveForward(float speed);
    void MoveBackward(float speed);
    void MoveRight(float speed);
    void MoveLeft(float speed);
    // void MoveUp();
    // void MoveDown();

    private:
        glm::vec3 mEye;
        glm::vec3 mViewDirection;
        glm::vec3 mUpVecttor;
        /// The ultimate view matrix of the camera
        glm::mat4 mViewMatrix;
};
#endif