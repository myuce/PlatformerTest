#pragma once
#include "GameObject.hpp"
#include "Player.hpp"

class Coin : public GameObject
{
public:
    Player *player;
    Vector2 originalPos;
    Vector2 tempPos;

    Coin(Vector2 _pos)
    {
        pos = _pos;
        rect = {_pos.x, _pos.y, 8, 8};
    }

    void Start()
    {
        name = "coin";
        color = YELLOW;
        debug = true;
        player = GetObject<Player *>();
        originalPos = pos;
    }

    void Update()
    {
        if (this->IsTouching(player))
        {
            player->coins++;
            deleted = true;
        }
    }
};
