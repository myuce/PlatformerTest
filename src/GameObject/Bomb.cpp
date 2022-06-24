#include "Bomb.hpp"

Bomb::Bomb(Vector2 _pos)
{
    pos = _pos;
    rect = {_pos.x, _pos.y, 16, 16};
    anim.states["move"] = SpriteSheet("./res/images/fireworm/Move.png", 6.0f, {46, 46}, {16, 16}, {16, 16});
    anim.states["explosion"] = SpriteSheet("./res/images/fireworm/Explosion.png", 6.0f, {46, 46}, {16, 16} , {33, 33});
    anim.states["explosion"].looping = false;
    anim.SetState("move");
}

void Bomb::Start()
{
    name = "Bomb";
    color = RED;
    debug = true;
    player = GetObject<Player *>();
    spawnTime = GetTime();
    tiles = GetObjects<Tile *>();
    
    if (direction > 0)
        anim.flipped = false;
    else
        anim.flipped = true;
}

void Bomb::Update()
{
    if (gameTime - spawnTime > 5.0f)
        Delete(this);

    if (this->IsTouching(player) && !deflected)
        player->pos = player->originalPos;
    
    if (CheckCollisionRecs(rect, player->attack_hitbox) && player->attacking && !deflected)
    {
        direction *= -3;
        deflected = true;
    }

    if (this->IsTouching(parent) && deflected)
    {
        Delete(this);
        Delete(parent);
    }
    
    for (auto &tile: tiles)
        if (this->IsTouching(tile))
            Delete(this);

    pos.x += direction * deltaTime * 300.0f;
    rect.x = pos.x;
}
