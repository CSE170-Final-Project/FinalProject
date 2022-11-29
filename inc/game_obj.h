#ifndef GAME_OBJ_H
#define GAME_OBJ_H
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <GL/gl.h>
#include <shader.h>
#include <shaderprogram.h>
#include <vector>
#include <geometry.h>
#include <glm/mat4x4.hpp>

struct GL_Obj{
    GLuint VAO;
    GLuint VBO[7];
    int vertex_count;
    // [Vertex, Normals, TexCoord, instance m1, instance m2, instance m3, instance m4] 
};

class GameObject{
    Hitbox h;
    glm::vec3 pos;
    glm::vec3 front;
    glm::vec3 up;
    GL_Obj gl_obj;

    glm::vec3 velocity;

public:
    GameObject();
    GameObject(GL_Obj);
    void teleport(glm::vec3 pos, glm::vec3 front, glm::vec3 up);
    void move(float t);
    void draw(ShaderProgram shader);
    void setVelocity(glm::vec3 vel);
    glm::vec3 getVelocity();
    
};

#endif