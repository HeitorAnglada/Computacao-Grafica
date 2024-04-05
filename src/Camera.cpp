#include "camera/Camera.hpp"
#include "glm/gtc/matrix_transform.hpp"


Camera::Camera(){
    mEye = glm::vec3(0.0f, 0.0f, 0.0f);
    mViewDirection = glm::vec3(0.0f, 0.0f, -1.0f);
    // Assume we start on perfectly level ground
    mUpVecttor = glm::vec3(0.0f, 1.0f, 0.0f);
}

/// The ultimate view matrix of the camera
glm::mat4 Camera::GetViewMatrix() const {
        return glm::lookAt(mEye, mEye + mViewDirection, mUpVecttor);
}
void Camera::MoveForward(float speed){
    mEye.z += speed;

}

void Camera::MoveBackward(float speed){
    mEye.z -= speed;
    
}
void Camera::MoveRight(float speed){}

void Camera::MoveLeft(float speed){}

// void Camera::MoveUp();