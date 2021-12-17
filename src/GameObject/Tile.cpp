#include "Tile.hpp"

Tile::Tile(Vector2 _pos, Vector2 _size)
{
    name = "Tile";
    pos = _pos;
    rect = {_pos.x, _pos.y, _size.x, _size.y};
    color = WHITE;
}

void Tile::Start()
{
    player = GetObject<Player *>();
}

void Tile::Update()
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
