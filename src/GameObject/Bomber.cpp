#include "Bomber.hpp"
#include "Bomb.hpp"

Bomber::Bomber(Vector2 _pos, int _direction)
{
    pos = _pos;
    direction = _direction;
    rect = {_pos.x, _pos.y, 8, 8};
}

void Bomber::Start()
{
    name = "Bomber";
    color = YELLOW;
    debug = true;
    lastFired = GetTime();
}

void Bomber::Update()
{
    if (gameTime - lastFired > 2.0f)
    {
        Bomb *bomb = Spawn<Bomb>({this->pos});
        bomb->direction = this->direction;
        bomb->parent = this;
        lastFired = gameTime;
    }
}
