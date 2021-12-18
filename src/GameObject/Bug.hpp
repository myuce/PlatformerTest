#pragma once
#include "GameObject.hpp"
#include "Player.hpp"
#include "Tile.hpp"

class Bug : public GameObject
{
public:
    Player *player;
    int direction = -1;
    float velocity = 0.0f;
    float gravity = 500.0f;
    bool grounded = false;
    std::vector<Tile *> tiles;

    Bug(Vector2 _pos, int _direction = -1);
 
    void Start();
    void Update();
    void ResolveTileCollision(Tile *tile);
    void ResolvePlayerCollision();
};
