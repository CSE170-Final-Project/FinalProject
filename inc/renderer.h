#ifndef RENDERER_H
#define RENDERER_H
#include "window.h"
#include <GL/glut.h>
#include <game_obj.h>
#include <glm/vec2.hpp>
#include <vector>
#include <map>

class Renderer : public Window{
protected:
    bool locked_mode = true;
    glm::vec3 position;
    glm::vec3 direction;
    float x_rotation = 4.75, y_rotation = 0;
    ShaderProgram shader;
    glm::mat4 PerspectiveMatrix, ViewMatrix;
    std::map<const char*, GL_Obj> GL_Objs;
    std::vector<GameObject*> render_objs;
public:
    int init_renderer(const char **objNames, const char **objFiles, int objc);
    GL_Obj get_gl_obj(const char *name);
    int GL_load_obj(const char *objName, const char *objFile);
    int GL_load_obj(const char *objName, std::vector<std::string> materials, std::vector<glm::vec3> verts, std::vector<glm::vec3> norms, std::vector<glm::vec3> textures);
    virtual void display_func();
    void add_render_obj(GameObject *obj);
    void remove_render_obj(GameObject *obj);
};

#endif