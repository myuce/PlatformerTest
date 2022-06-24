#pragma once
#include "GameObject.hpp"
#include "Player.hpp"

class Bomber : public GameObject
{
public:
    Player *player;
    Vector2 originalPos;
    Vector2 tempPos;
    int direction = 1;
    float lastFired = 0.0f;

    Bomber(Vector2 _pos, int _direction);

    void Start();
    void Update();
};
