#include "Bug.hpp"

Bug::Bug(Vector2 _pos = {0.0f, 0.0f}, int _direction = -1)
{
    pos = _pos;
    size = {18, 18};
    rect = {_pos.x, _pos.y, size.x, size.y};
    direction = -1;
}

void Bug::Start()
{
    name = "Bug";
    debug = true;
    player = GetObject<Player *>();
    tiles = GetObjects<Tile *>();
    color = BLACK;
}

void Bug::Update()
{
    // apply gravity
    velocity += gravity * deltaTime;
    pos.y += velocity * deltaTime;
    rect.y = pos.y;
    if (!grounded) // increase falling speed each frame
        velocity += 20.0f * deltaTime;

    // move
    pos.x += direction * 30.0f * deltaTime;

    if (this->IsTouching(player))
        ResolvePlayerCollision();

    for (auto &tile : tiles)
        if (this->IsTouching(tile))
            this->ResolveTileCollision(tile);

    rect.x = pos.x;
    rect.y = pos.y;
}

void Bug::ResolvePlayerCollision()
{
    Rectangle col = GetCollisionRec(rect, player->rect);

    if (col.width == col.height)
        return;

    if (col.width > col.height && player->pos.y + col.y > pos.y && player->velocity.y >= -250.0f)
    {
        if (IsKeyDown(KEY_SPACE))
            player->velocity.y = -350.0f;
        else
            player->velocity.y = -250.0f;

        Delete();
    }
    else
    {
        player->pos = player->originalPos;
    }
}

void Bug::ResolveTileCollision(Tile *tile)
{
    Rectangle col = GetCollisionRec(rect, tile->rect);

    // enemy is on the left side of the tile
    if (col.width <= col.height && pos.x < tile->pos.x)
    {
        if (direction == 1)
            direction = -1;
        
        pos.x -= col.width;
        pos.x -= 1.0f;
        rect.x = pos.x;
    }
    // enemy is on the right side of the tile
    else if (col.width <= col.height && pos.x > tile->pos.x)
    {
        if (direction == -1)
            direction = 1;
        pos.x += col.width;
        pos.x += 1.0f;
        rect.x = pos.x;
    }

    // enemy is above the tile
    if (col.width >= col.height && tile->pos.y > pos.y)
    {
        velocity = 0.0f;
        pos.y -= col.height;
        rect.y = pos.y;
        grounded = true;
    }
    // enemy is below the tile
    else if (col.width >= col.height && tile->pos.y < pos.y)
    {
        velocity = 0.0f;
        pos.y += col.height;
        rect.y = pos.y;
    }
}
