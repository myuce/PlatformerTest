#include "Bat.hpp"

Bat::Bat(Vector2 _pos, int _direction)
{
    pos = _pos;
    size = {18, 18};
    rect = {_pos.x, _pos.y, size.x, size.y};
    direction = -1;
}

void Bat::Start()
{
    name = "Bat";
    debug = true;
    originalPos = pos;
    player = GetObject<Player *>();
    color = PURPLE;
}

void Bat::Update()
{
    // move
    pos.x += direction * 25.0f * GetFrameTime();

    if (Vector2Distance(originalPos, pos) > 200.0f)
        direction *= -1;

    // float
    tempPos = originalPos;
    tempPos.y += sinf(GetTime() * PI * 0.5f) * 32.0f;
    pos.y = tempPos.y;

    if (this->IsTouching(player))
        ResolvePlayerCollision();

    rect.x = pos.x;
    rect.y = pos.y;
}

void Bat::ResolvePlayerCollision()
{
    Rectangle col = GetCollisionRec(rect, player->rect);

    if (col.width > col.height && player->pos.y + col.y > pos.y && player->velocity.y >= -250.0f)
    {
        player->velocity.y = -250.0f;
        Delete();
    }
    else
    {
        player->pos = player->originalPos;
    }
}
