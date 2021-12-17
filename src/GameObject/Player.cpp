#include "Player.hpp"
#include "Bug.hpp"

Player::Player(Vector2 _pos)
{
    pos = _pos;
    originalPos = pos;
    coins = 0;
}

void Player::Start()
{
    name = "Player";
    rect = {pos.x, pos.y, 16, 32};
    color = RED;

    debug = true;
}

void Player::Update()
{
    if (IsKeyPressed(KEY_R))
    {
        pos = {10, 10};
        velocity = {0, 0};
    }

    if (velocity.y > 50.0f)
        grounded = false;

    // apply gravity
    velocity.y += gravity * deltaTime;
    pos.y += velocity.y * deltaTime;
    rect.y = pos.y;

    // movement
    if (IsKeyDown(KEY_LEFT) && !IsKeyDown(KEY_RIGHT))
    {
        if (velocity.x > 0.0f)
            velocity.x -= (speed * deltaTime) * 2.0f;
        else
            velocity.x -= speed * deltaTime;

        if (velocity.x < -speed)
            velocity.x = -speed;
    }
    if (IsKeyDown(KEY_RIGHT) && !IsKeyDown(KEY_LEFT))
    {
        if (velocity.x < 0.0f)
            velocity.x += (speed * deltaTime) * 2.0f;
        else
            velocity.x += speed * deltaTime;

        if (velocity.x > speed)
            velocity.x = speed;
    }

    // slow down & stop the player
    if ((!IsKeyDown(KEY_RIGHT) && !IsKeyDown(KEY_LEFT)) || (IsKeyDown(KEY_RIGHT) && IsKeyDown(KEY_LEFT)))
    {
        if ((velocity.x < 0.0f || velocity.x > 0.0f) && !grounded)
            velocity.x = velocity.x + ((0.0f - velocity.x) * 0.01f);
        if ((velocity.x < 0.0f || velocity.x > 0.0f) && grounded)
            velocity.x = velocity.x + ((0.0f - velocity.x) * 0.1f);
        if (fabs(velocity.x) < 0.25f)
            velocity.x = 0.0f;
    }

    pos.x += velocity.x;

    // jump
    if (IsKeyPressed(KEY_SPACE) && grounded)
    {
        pos.y -= 1.0f;
        velocity.y -= jumpVel;
        grounded = false;
    }
    // stop jumping when space is released
    if (IsKeyReleased(KEY_SPACE) && velocity.y < 0.0f)
        velocity.y *= 0.5f;

    rect.x = pos.x;
    rect.y = pos.y;
}

void Player::ResolveTileCollision(GameObject *tile)
{
    Rectangle col = GetCollisionRec(rect, tile->rect);

    if (col.width == col.height)
    {
        if (tile->pos.y > pos.y)
        {
            velocity.y = 0.0f;
            grounded = true;
        }
        else
        {
            if (velocity.y < 0.0f)
                velocity.y = 0.0f;
        }
        return;
    }

    // player is on the left side of the tile
    if (col.width < col.height && pos.x < tile->pos.x)
    {
        if (velocity.x > 0.0f)
            velocity.x = 0.0f;

        pos.x -= col.width;
        rect.x = pos.x;
    }
    // player is on the right side of the tile
    else if (col.width < col.height && pos.x > tile->pos.x)
    {
        if (velocity.x < 0.0f)
            velocity.x = 0.0f;
            
        pos.x += col.width;
        rect.x = pos.x;
    }

    // player is above the tile
    if (col.width > col.height && tile->pos.y > pos.y)
    {
        velocity.y = 0.0f;
        pos.y -= col.height;
        rect.y = pos.y;
        grounded = true;
    }
    // player is below the tile
    else if (col.width > col.height && tile->pos.y < pos.y)
    {
        velocity.y = 0.0f;
        pos.y += col.height;
        rect.y = pos.y;
    }
}