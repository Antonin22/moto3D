#ifndef OBJECT_H
#define OBJECT_H

#include <string>
#include <glm/glm.hpp>
#include "vertexbuffer.h"
#include "texture.h"
#include "uvbuffer.h"
#include <cstring>
#include <GL/gl.h>
#include "stb_image/stb_image.h"


class Object
{
public:
    Object(std::vector< glm::vec3 > vertices, std::vector< glm::vec2 > uvs, std::string texturePath);
    Object(std::string objPath, std::string texturePath);
    ~Object();
    void Bind() const;
    void Unbind() const;
    void Draw() const;
    glm::vec3 position;
    glm::vec3 rotationAngles;
    glm::mat4 getModelMatrix();
    GLuint getTextureID() const;

private:
    VertexBuffer *m_vb;
    UVBuffer *m_uvsb;
    Texture *m_texture;
    VertexBuffer *m_normalsb;
    bool loadOBJ (const char *path, std::vector<glm::vec3> &out_vertices, std::vector<glm::vec2> &out_uvs, std::vector<glm::vec3> &out_normals);


};

#endif // OBJECT_H
