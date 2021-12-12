#pragma once
#include "GameObject.hpp"
#include "Player.hpp"

class Tile : public GameObject
{
public:
    Player *player;

    Tile(Vector2 _pos, Vector2 _size)
    {
        name = "Tile";
        pos = _pos;
        rect = {_pos.x, _pos.y, _size.x, _size.y};
        color = WHITE;
    }

    void Start()
    {
        player = GetObject<Player *>();
    }

    void Update()
    {
        if (this->IsTouching(player))
        {
            this->color = GREEN;
            player->ResolveTileCollision(this);
        }
        else
        {
            this->color = WHITE;
        }
    }
};