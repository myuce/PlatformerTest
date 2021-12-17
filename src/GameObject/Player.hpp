#pragma once
#include "GameObject.hpp"

class Player : public GameObject
{
public:
    int coins = 0;
    float gravity = 800.0f;
    float jumpVel = 400.0f;
    float speed = 2.0f;
    Vector2 velocity = {0.0f, 0.0f};
    bool grounded = false;

    Vector2 originalPos;

    Player(Vector2 _pos);

    void Start();
    void Update();
    void ResolveTileCollision(GameObject *tile);
};