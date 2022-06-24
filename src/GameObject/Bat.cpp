#include "Bat.hpp"

Bat::Bat(Vector2 _pos, int _direction)
{
    pos = _pos;
    size = {18, 18};
    rect = {_pos.x, _pos.y, size.x, size.y};
    direction = _direction;
}

void Bat::Start()
{
    name = "Bat";
    originalPos = pos;
    player = GetObject<Player *>();
    color = PURPLE;

    anim.states["idle"] = SpriteSheet("./res/images/bat/Bat_Fly.png", 10.0f, {64, 64}, {23, 24}, {23, 24});
    anim.SetState("idle");
    anim.flipped = true;
}

void Bat::Update()
{
    // move
    if (alive)
    {
        pos.x += direction * 25.0f * GetFrameTime();

        if (Vector2Distance(originalPos, pos) > 200.0f)
        {
            direction *= -1;
            anim.flipped = direction == 1 ? false : true;
        }

        // float
        tempPos = originalPos;
        tempPos.y += sinf(GetTime() * PI * 0.5f) * 32.0f;
        pos.y = tempPos.y;

        if (this->IsTouching(player))
            player->pos = player->originalPos;
        
        if (CheckCollisionRecs(rect, player->attack_hitbox) && player->attacking)
        {
            alive = false;
            anim.flipped = true;
            anim.flipped_vertical = true;
            velocity.x = player->anim.flipped ? -100.0f : 100.0f;
            velocity.y = -300.0f;
            deathTime = gameTime;
        }
    }
    else
    {
        // apply gravity after death
        velocity.y += 800.0f * deltaTime;
        pos.y += velocity.y * deltaTime;
        pos.x += velocity.x * deltaTime;
        rect.y = pos.y;
    }

    if (!alive && gameTime - deathTime > 5)
        Delete(this);

    rect.x = pos.x;
    rect.y = pos.y;
}

