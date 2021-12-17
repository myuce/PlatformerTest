#pragma once
#include "GameObject.hpp"
#include "Player.hpp"

class Tile : public GameObject
{
public:
    Player *player;

    Tile(Vector2 _pos, Vector2 _size);

    void Start();
    void Update();
};
