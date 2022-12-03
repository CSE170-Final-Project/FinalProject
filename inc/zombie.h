#ifndef ZOMBIE_H
#define ZOMBIE_H

#include <game_obj.h>

enum Zombie_Parts{
    TORSO = 0,
    HEAD = 1,
    LEFT_ARM = 2,
    RIGHT_ARM = 3,
    LEFT_LEG = 4,
    RIGHT_LEG = 5
};

class Zombie : public GameObject{
    GameObject parts[6];

    Curve path;

    float health;

public:
    Zombie(GL_Obj);
    void drop_limb(enum Zombie_Parts);
    void pathfind();

    void take_damage(int damage);

    void kill();
    
};

#endif