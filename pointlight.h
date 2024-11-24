#ifndef POINTLIGHT_H
#define POINTLIGHT_H

#include <glm/glm.hpp>
#include <stdlib.h>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include "shader.h"

class PointLight {
public:
    glm::vec3 position;
    glm::vec3 color;
    float power;

    PointLight(const glm::vec3& position, const glm::vec3& color, float power);

    void Bind(Shader *shader);
    void setPosition(const glm::vec3& position);

};

#endif
