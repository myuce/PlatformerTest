#pragma once
#include "GameObject.hpp"
#include "Player.hpp"
#include "Tile.hpp"

class Jumper : public GameObject
{
public:
    Player *player;
    int direction = -1;
    float velocity;
    float gravity = 500.0f;
    bool grounded = false;
    std::vector<Tile *> tiles;

    Jumper(Vector2 _pos = {0.0f, 0.0f}, int _direction = -1);

    void Start();
    void Update();
    void ResolvePlayerCollision();
    void ResolveTileCollision(Tile *tile);
};
