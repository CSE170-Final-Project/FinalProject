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



// void GameObject::loadCollisionPlanes(const char *collision_file){
//     // std::ifstre  am ifs(objFile, std::ios_base::in);    
//     printf("started loading: %s\n", collision_file);
//     FILE *file = fopen(collision_file, "r");
//     if(!file) {
//         printf("could not open file %s\n", collision_file);
//         return;
//     }
//     std::vector<glm::vec3> starting_vertices;
//     std::vector<int> index_vertices;

//     std::vector<glm::vec3> final_verticies;

//     starting_vertices.push_back(glm::vec3(0, 0, 0));

//     int line_number = 0;
//     char buff[256] = {0};  
//     while(!feof(file)){
//         int line_len = 0;
//         memset(&buff[0], 0, 256);
//         fscanf(file, "%[^\n]\n", &buff[0]);
//         // if(line_number++ % 10000 == 0)
//         //     printf("LINE %d: %s\n", line_number, &buff[0]);
//         switch (buff[0]) {
//             case 'v' : {
//                 switch (buff[1]) {
//                     case 't' : {
//                         float x, y;
//                         sscanf(&buff[0], "vt %f %f", &x, &y);
//                         // printf("vt %f %f\n", x, y);
//                         starting_texCoords.push_back(glm::vec2(x,y));
//                     } break; // texcoords
//                     case 'n' : {
//                         float x, y, z;
//                         sscanf(&buff[0], "vn %f %f %f", &x, &y, &z);
//                         //printf("vn %f %f %f\n", x, y, z);
//                         starting_normals.push_back(glm::vec3(x,y,z));
//                     } break; // normals
//                     default : { // points
//                         float x, y, z;
//                         sscanf(&buff[0], "v %f %f %f\n", &x, &y, &z);
//                         //printf("v %f %f %f\n", x, y, z);
//                         starting_vertices.push_back(glm::vec3(x,y,z));
//                     } break;
//                 }
//             } break;
//             case 'f' : {
//                 std::vector<int> v;
//                 std::vector<int> n;
//                 std::vector<int> t;
//                 int a = 0, b = 0, c = 0;
//                 enum MODE{
//                     NONE = -1,
//                     VTN = 0,
//                     VT_ = 1,
//                     V_N = 2,
//                     V__ = 3
//                 };
//                 int mode = NONE;
//                 if(sscanf(&buff[0], "f %d/%d/%d ", &a, &b, &c) == 3){
//                     mode = VTN;
//                 }
//                 else if(sscanf(&buff[0], "f %d//%d ", &a, &b, &c) == 2){
//                     mode = V_N;
//                 }

//                 else if(sscanf(&buff[0], "f %d/%d ", &a, &b, &c) == 2){
//                     mode = VT_;
//                 }
//                 else if(sscanf(&buff[0], "f %d ", &a, &b, &c) == 1){
//                     mode = V__;
//                 }
                
//                 else return 1;
//                 const char *patterns[] = {" %d/%d/%d ", " %d//%d ", " %d/%d ", " %d "};
//                 int offset = 0;
//                 while(true){
//                     //advance to next whitespace;
//                     while(buff[offset] != ' ' && buff[offset] != '\n' && buff[offset] != '\0') offset++;
//                     if(buff[offset] == '\0') break;
                    
//                     a = 0; b = 0; c = 0;
//                     sscanf(&buff[offset], patterns[mode], &a, &b, &c);
//                     if(mode == VTN){
//                         v.push_back(a);
//                         t.push_back(b);
//                         n.push_back(c);
//                     }else if(mode == VT_){
//                         v.push_back(a);
//                         t.push_back(b);
//                         n.push_back(0);
//                     }else if(mode == V_N){
//                         v.push_back(a);
//                         t.push_back(0);
//                         n.push_back(b);
//                     }else if(mode == V__){
//                         v.push_back(a);
//                         t.push_back(0);
//                         n.push_back(0);
//                     }else{

//                     }
//                     offset++;
//                 }
                
//                 if(v.size() > 3){
//                     int order[] = {0, 1, 2, 0, 2, 3};
//                     for(int i = 0; i < 6; i++){
//                         index_vertices.push_back(v[order[i]]);
//                         index_normals.push_back(n[order[i]]);
//                         index_texCoords.push_back(t[order[i]]);
//                         final_texIDs.push_back(current_texture);
//                     }
//                 } else{
//                     for(int i = 0; i < 3; i++){
//                         index_vertices.push_back(v[i]);
//                         index_normals.push_back(n[i]);
//                         index_texCoords.push_back(t[i]);
//                         final_texIDs.push_back(current_texture);
//                     }
//                 }
//             } break;
//             case 'u' :{
//                 std::string material_img_file(obj_file);
//                 std::string material_name(&buff[7]);
//                 current_texture = -1;
//                 for(int i = 0; i < material_names.size(); i++){
//                     if(material_names[i] == material_name){
//                         current_texture = i;
//                     } 
//                 }
//                 if(current_texture == -1){
//                     material_img_file = material_img_file.substr(0, material_img_file.find_last_of('/') + 1);
//                     material_img_file.append(material_name.c_str());
//                     material_img_file.append(".png");
//                     current_texture = material_names.size();
//                     material_files.push_back(material_img_file);
//                     material_names.push_back(material_name);
//                 }

//             }
//             default : {} // skip
//         }
//     }
    
    
//     for(int i = 0; i < index_vertices.size(); i++){
//         final_verticies.push_back(starting_vertices[index_vertices[i]]);
//         final_normals.push_back(starting_normals[index_normals[i]]);
//         final_texCoords.push_back(glm::vec3(starting_texCoords[index_texCoords[i]], final_texIDs[i]));
//     }


// }

void GameObject::loadHitbox(glm::vec3 origin, glm::vec3 size){
    glm::vec3 p[8]; 
    for(int i = 0; i < 8; i++) p[i] = origin + size * glm::vec3((i >> 2)&1, (i >> 1)&1, i&1);
    int order[6] = {TOP, BOTTOM, LEFT, RIGHT, FRONT, BACK};
    int a[6]     = {  2,      0,    1,     0,     4,    0}; 
    int b[6]     = {  3,      4,    5,     2,     6,    1}; 
    int c[6]     = {  6,      1,    3,     4,     5,    3}; 
    int d[6]     = {  7,      5,    7,     6,     7,    2}; 
    for(int i = 0; i < 6; i++) {
        h.faces[order[i]].A = p[a[i]];
        h.faces[order[i]].B = p[b[i]];
        h.faces[order[i]].C = p[c[i]];
        h.faces[order[i]].D = p[d[i]];
    }
} 