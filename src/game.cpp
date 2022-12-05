#include <game.h>
#include "Settings.h"
#include <shaderprogram.h>
#include <shader.h>
#include <intersection.h>

const char *objNames[] = {
    "plane",
    "zombie"
};
const char *objFiles[] = {
    "./textures/Parktest_triangles.obj",
    "./textures/zombie.obj",
};
int obj_count = 2;

int Game::init(){
    init_window(InitWindowWidth, InitWindowHeight);
    init_renderer(objNames, objFiles, obj_count);

    glutSetCursor(GLUT_CURSOR_NONE);

    world = GameObject(GL_Objs["plane"]);
    add_render_obj(&world);


    spawn_zombie(glm::vec3(-10,10,0));
    start_timer(10000); // 10ms
    window_begin(); // doesn't return
    // no code runs after this
    return 0;
}

void Game::passive_motion_func(int x, int y){
    glm::vec2 mouse_pos(x,y);
    glm::vec2 rotate;
    if(locked_mode) {
        rotate = (mouse_pos - glm::vec2(width/2, height/2)) * mouse_sense;
        x_rotation += rotate.x;
        y_rotation -= rotate.y;
        if(y_rotation < -1.57) y_rotation = -1.57;
        if(y_rotation > 1.57) y_rotation = 1.57;
        direction.x = cos(x_rotation)*cos(y_rotation);
        direction.y = sin(y_rotation);
        direction.z = sin(x_rotation)*cos(y_rotation);
    }
    else if(mouse_states[0] == true)
	{
        rotate = (mouse_pos - prev_mouse_pos) * mouse_sense;
        x_rotation -= rotate.x;
        y_rotation += rotate.y;
        if(y_rotation < -1.57) y_rotation = -1.57;
        if(y_rotation > 1.57) y_rotation = 1.57;
        direction.x = cos(x_rotation)*cos(y_rotation);
        direction.y = sin(y_rotation);
        direction.z = sin(x_rotation)*cos(y_rotation);
	}
    prev_mouse_pos = mouse_pos;
}
void Game::active_motion_func(int x, int y){
    Game::passive_motion_func(x, y);
}

void Game::mouse_func(int button, int state, int x, int y){
    // Key 0: left button
	// Key 1: middle button
	// Key 2: right button
	// Key 3: scroll up
	// Key 4: scroll down

	if( x < 0 || x > width || y < 0 || y > height )
		return;

    // if( button == 3 )
	// {
	// 	// perspZoom += 0.03f;
	// 	position += 0.1f*direction;
	// }
	// else if( button == 4 )
	// {
	// 	// if( perspZoom - 0.03f > 0.0f )
	// 	// 	perspZoom -= 0.03f;
	// 	position -= 0.1f*direction;
	// }

	mouse_states[ button ] = ( state == GLUT_DOWN );

	prev_mouse_pos = glm::vec2(x,y);
}

void Game::keyboard_func( unsigned char key, int x, int y ){
    if(key == 'l' && !kbd_states['l']){
        locked_mode = !locked_mode;
        if(locked_mode){
            glutSetCursor(GLUT_CURSOR_NONE);
        } else{
            glutSetCursor(GLUT_CURSOR_INHERIT);
        }
    } 
    if(key == 'r'){
        x_rotation = 4.75;
        y_rotation = 0;
    }
    kbd_states[key] = true;
}
void Game::key_released( unsigned char key, int x, int y ){
    kbd_states[key] = false;
}

void Game::start_timer(int us){
    std::thread t(&timer, this, us);
    t.detach();
}

void Game::timer(int us){
    auto begin = std::chrono::high_resolution_clock::now();
    auto end = std::chrono::high_resolution_clock::now();
    while(true){
        if(end - begin > std::chrono::microseconds(us)){
            begin = std::chrono::high_resolution_clock::now() + std::chrono::duration<long long, std::nano>(end - begin - std::chrono::microseconds(us));
            std::thread t(tick, this);
            t.join();
        }
        std::this_thread::sleep_for(std::chrono::microseconds(1));
        end = std::chrono::high_resolution_clock::now();
    }
}
void Game::tick(){
    if(kbd_states['w']){
         player.setVelocity(speed * glm::normalize(direction));
        // position += player.getVelocity();
    } 
    if(kbd_states['s']){
        player.setVelocity(-speed * glm::normalize(direction));
        // position -= player.getVelocity();
    } 
    if(kbd_states['a']){
        player.setVelocity(-speed * glm::normalize(glm::cross(direction, glm::vec3(0,1,0))));
        // position -= player.getVelocity();
    } 
    if(kbd_states['d']){
        player.setVelocity(speed * glm::normalize(glm::cross(direction, glm::vec3(0,1,0))));
        // position += player.getVelocity();
    } 
    if(kbd_states['q']){
        player.setVelocity(glm::vec3(0,0,0));
        // position += player.getVelocity();
    } 

    player.move(0.01);
    position = player.getPosition();

}
    
void Game::spawn_zombie(glm::vec3 pos, glm::vec3 front, glm::vec3 up){
    
    int loc = zombies.size();
    zombies.push_back(Zombie(GL_Objs["zombie"]));
    Zombie &z = zombies[loc];
    z.teleport(pos, front, up);
    add_render_obj(&z);
}
