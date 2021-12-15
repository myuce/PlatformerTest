#pragma once
#include "GameObject.hpp"

class Player : public GameObject
{
public:
    int coins;

    // movement
    float gravity = 800.0f;
    float jumpVel = 400.0f;
    float speed = 2.0f;
    Vector2 velocity = {0.0f, 0.0f};
    bool grounded = false;

    Vector2 originalPos;

    Player(Vector2 _pos)
    {
        pos = _pos;
        originalPos = pos;
        coins = 0;
    }

    void Start()
    {
        name = "Player";
        rect = {pos.x, pos.y, 16, 32};
        color = RED;

        debug = true;
    }

    void Update()
    {
        if (IsKeyPressed(KEY_R))
        {
            pos = {10, 10};
            velocity = {0, 0};
        }

        if (velocity.y > 10.0f)
            grounded = false;

        // apply gravity
        velocity.y += gravity * GetFrameTime();
        pos.y += velocity.y * GetFrameTime();
        rect.y = pos.y;

        // movement
        if (IsKeyDown(KEY_LEFT) && !IsKeyDown(KEY_RIGHT))
        {
            velocity.x -= speed * GetFrameTime();
            if (velocity.x < -speed)
                velocity.x = -speed;
        }
        if (IsKeyDown(KEY_RIGHT) && !IsKeyDown(KEY_LEFT))
        {
            velocity.x += speed * GetFrameTime();
            if (velocity.x > speed)
                velocity.x = speed;
        }

        // slow down & stop the player
        if (!IsKeyDown(KEY_RIGHT) && !IsKeyDown(KEY_LEFT))
        {
            if ((velocity.x < 0.0f || velocity.x > 0.0f) && !grounded)
                velocity.x = lerp(velocity.x, 0.0f, 0.01f);
            if ((velocity.x < 0.0f || velocity.x > 0.0f) && grounded)
                velocity.x = lerp(velocity.x, 0.0f, 0.1);
            else if (fabs(velocity.x) < 0.25f)
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
        if (IsKeyReleased(KEY_SPACE) && velocity.y < 0.0f)
            velocity.y *= 0.5f;

        rect.x = pos.x;
        rect.y = pos.y;
    }

    void ResolveTileCollision(GameObject *tile)
    {
        Rectangle col = GetCollisionRec(rect, tile->rect);

        if (col.width == col.height)
            return;

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
};