#include <game_obj.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include "intersection.h"
#include "Settings.h"

void GameObject::teleport(glm::vec3 pos, glm::vec3 front, glm::vec3 up){
    this->pos = pos;
    this->front = front;
    this->up = up; 
}
void GameObject::move(float t){
    pos += (velocity * t);
    
    bool hit_something = 0;
    // for(int i = 0; i < collision_planes.size(); i++){
    //     if(Box_Plane(h, *collision_planes[i])){
    //         pos -= (velocity * t);
    //         glm::vec3 norm = glm::normalize(glm::cross(collision_planes[i]->B - collision_planes[i]->A, collision_planes[i]->C - collision_planes[i]->A));
    //         velocity -= glm::dot(velocity, norm) * norm;
    //         return;
    //     }
    // }
    
    if(dot(velocity, velocity) < 0.0001){
        velocity = glm::vec3(0,0,0);
    }

    velocity *= hit_something ? (1 - floor_friction) : (1 - air_resistance);
    // velocity -= glm::vec3(0, 9.81f * t, 0);
}
void GameObject::setVelocity(glm::vec3 vel){
    velocity = vel;
}
glm::vec3 GameObject::getVelocity(){
    return velocity;
}
glm::vec3 GameObject::getPosition(){
    return pos;
}
void GameObject::draw(ShaderProgram shader){
    glm::mat4 model_matrix(
        glm::vec4(glm::normalize(front), 0), // transforms x axis to front axis
        glm::vec4(glm::normalize(up), 0), // transforms y axis to up axis
        glm::vec4(glm::normalize(glm::cross(front, up)),0), // transforms z axis to right axis
        glm::vec4(pos, 1));
    // glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D_ARRAY, gl_obj.texID);
    // shader.SetUniform("texID", 0);
    shader.SetUniform("modelMatrix", glm::value_ptr(model_matrix), 4, GL_FALSE, 1);
    glBindVertexArray(gl_obj.VAO);
    // printf("globj: %d-%d\n", gl_obj.VAO, gl_obj.vertex_count);
    glDrawArrays(GL_TRIANGLES, 0, gl_obj.vertex_count);
    // glDrawArrays(GL_TRIANGLES, 0, gl_obj.vertex_count);
}
GameObject::GameObject(GL_Obj gl_obj){
    this->gl_obj = gl_obj;
    this->pos = glm::vec3(0,0,0);
    this->front = glm::vec3(1,0,0);
    this->up = glm::vec3(0,1,0);
}
GameObject::GameObject(){}