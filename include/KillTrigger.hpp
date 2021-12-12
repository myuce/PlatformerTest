#pragma once
#include "GameObject.hpp"
#include "Player.hpp"

class KillTrigger : public GameObject
{
public:
    Player *player;

    KillTrigger(Vector2 _pos, Vector2 _size)
    {
        name = "KillTrigger";
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
            player->pos = player->originalPos;
        }
        else
        {
            this->color = WHITE;
        }
    }
};