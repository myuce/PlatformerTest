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

    Bat(Vector2 _pos, int _direction = -1);

    void Start();
    void Update();
    void ResolvePlayerCollision();
};
