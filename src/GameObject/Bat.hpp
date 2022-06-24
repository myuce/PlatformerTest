#pragma once
#include "GameObject.hpp"
#include "Player.hpp"
#include "Tile.hpp"

class Bat : public GameObject
{
public:
    Player *player;
    int direction = -1;
    Vector2 originalPos;
    Vector2 tempPos;
    bool alive = true;
    Vector2 velocity = {0, 0};
    double deathTime;

    Bat(Vector2 _pos = {0.0f, 0.0f}, int _direction = -1);

    void Start();
    void Update();
};
