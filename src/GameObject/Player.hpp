#pragma once
#include "GameObject.hpp"

class Player : public GameObject
{
public:
    int coins = 0;
    float gravity = 800.0f;
    float jumpVel = 420.0f;
    float speed = 3.5f;
    float acceleration = 2.75f;
    float deceleration = 0.2f;
    float deceleration_air = 0.015f;
    Vector2 velocity = {0.0f, 0.0f};
    bool grounded = false;
    bool attacking = false;
    double fallTime;
    Rectangle attack_hitbox;
    Rectangle attack_hitbox2;

    Vector2 originalPos;
    
    Player(Vector2 _pos);

    void Start();
    void Update();
    void DrawExtra();
    void ResolveTileCollision(GameObject *tile);
};