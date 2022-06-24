#pragma once
#include "GameObject.hpp"
#include "Player.hpp"
#include "Tile.hpp"
#include "Bomber.hpp"

class Bomb : public GameObject
{
public:
    Player *player;
    int direction = 1;
    float spawnTime;
    bool deflected = false;
    std::vector<Tile *> tiles;
    Bomber *parent;

    Bomb(Vector2 _pos);

    void Start();
    void Update();
};
