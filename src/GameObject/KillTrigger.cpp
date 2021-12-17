#include "KillTrigger.hpp"

KillTrigger::KillTrigger(Vector2 _pos, Vector2 _size)
{
    name = "KillTrigger";
    pos = _pos;
    rect = {_pos.x, _pos.y, _size.x, _size.y};
    color = WHITE;
}

void KillTrigger::Start()
{
    player = GetObject<Player *>();
}

void KillTrigger::Update()
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
