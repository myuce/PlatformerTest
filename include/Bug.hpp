#pragma once
#include "GameObject.hpp"
#include "Player.hpp"
#include "Tile.hpp"

class Bug : public GameObject
{
public:
    Player *player;
    int direction = -1;
    float velocity;
    float gravity = 500.0f;
    bool grounded = false;
    std::vector<Tile *> tiles;

    Bug(Vector2 _pos, int _direction)
    {
        pos = _pos;
        size = {18, 18};
        rect = {_pos.x, _pos.y, size.x, size.y};
        direction = -1;
    }

    void Start()
    {
        name = "Bug";
        debug = true;
        player = GetObject<Player *>();
        tiles = GetObjects<Tile *>();
        color = BLACK;
    }

    void Update()
    {
        // apply gravity
        velocity += gravity * GetFrameTime();
        pos.y += velocity * GetFrameTime();
        rect.y = pos.y;
        if (!grounded) // increase falling speed each frame
            velocity += 20.0f * GetFrameTime();

        // move
        pos.x += direction * 30.0f * GetFrameTime();

        if (this->IsTouching(player))
            ResolvePlayerCollision();

        for (auto &tile : tiles)
            if (this->IsTouching(tile))
                ResolveTileCollision(tile);

        rect.x = pos.x;
        rect.y = pos.y;
    }

    void ResolvePlayerCollision()
    {
        Rectangle col = GetCollisionRec(rect, player->rect);

        if (col.width > col.height && player->pos.y + col.y > pos.y && player->velocity.y >= -250.0f)
        {
            player->velocity.y = -250.0f;
            deleted = true;
        }
        else
        {
            player->pos = player->originalPos;
        }
    }

    void ResolveTileCollision(Tile *tile)
    {
        Rectangle col = GetCollisionRec(rect, tile->rect);

        // enemy is on the left side of the tile
        if (col.width <= col.height && pos.x < tile->pos.x)
        {
            direction *= -1;
            pos.x -= col.width;
            pos.x -= 1.0f;
            rect.x = pos.x;
        }
        // enemy is on the right side of the tile
        else if (col.width <= col.height && pos.x > tile->pos.x)
        {
            direction *= -1;
            pos.x += col.width;
            pos.x += 1.0f;
            rect.x = pos.x;
        }

        // enemy is above the tile
        if (col.width >= col.height && tile->pos.y > pos.y)
        {
            if (velocity < -3.0f) // avoid sticking to platforms while jumping next to them
                return;

            velocity = 0.0f;
            pos.y -= col.height;
            rect.y = pos.y;
            grounded = true;
        }
        // enemy is below the tile
        else if (col.width >= col.height && tile->pos.y < pos.y)
        {
            if (velocity > 3.0f) // avoid sticking to platforms while falling
                return;

            velocity = 0.0f;
            pos.y += col.height;
            rect.y = pos.y;
        }
    }
};
