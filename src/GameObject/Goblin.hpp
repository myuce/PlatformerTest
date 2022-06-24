#pragma once
#include "GameObject.hpp"
#include "Player.hpp"
#include "Tile.hpp"

class Goblin : public GameObject
{
public:
    Player *player;
    std::vector<Tile *> tiles;
    bool alive = true;
    bool grounded;
    bool attacking = false;
    int direction = -1;
    float velocity;
    float gravity = 800.0f;
    Goblin(Vector2 _pos);
    double attackTime;
    Rectangle attack_hitbox;

    void Start();
    void Update();
    void DrawExtra();
    void ResolveTileCollision(Tile * tile);
};
