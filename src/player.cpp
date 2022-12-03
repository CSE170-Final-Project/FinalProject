#include <player.h>

Player::Player(){
    health = 100;
    armor = 0;
}
void Player::swap_weapon(){
    Gun temp;
    temp = active;
    active = inactive;
    inactive = temp;
}
void Player::shoot(){
    active.shoot();
}
void Player::reload(){
    active.reload();
}
void Player::heal(float value){
    if(health > maxHealth){
        value = (value / 10);
    }
    health += value;
}
void Player::damage(float damage){
    if(armor > damage){
        armor -= damage;
    }
    else{
        damage -= armor;
        armor = 0;
    }
    health -= damage;
}