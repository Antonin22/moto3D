#include "pointlight.h"
#include <glm/gtc/type_ptr.hpp>

PointLight::PointLight(const glm::vec3& position, const glm::vec3& color, float power)
    : position(position), color(color), power(power)
{

}

void PointLight::Bind(Shader *shader) {
    shader->setUniform3fv("lightPosition", position);
    shader->setUniform3fv("lightColor", color);
    shader->setUniform1f("lightIntensity", power);
}

void PointLight::setPosition(const glm::vec3& position) {
    this->position = position;
}
