#include "Coin.hpp"

Coin::Coin(Vector2 _pos)
{
    pos = _pos;
    rect = {_pos.x, _pos.y, 8, 8};
}

void Coin::Start()
{
    name = "coin";
    color = YELLOW;
    debug = true;
    player = GetObject<Player *>();
    originalPos = pos;
}

void Coin::Update()
{
    if (this->IsTouching(player))
    {
        player->coins++;
        deleted = true;
    }
}
