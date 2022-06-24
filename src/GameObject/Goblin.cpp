#include "Goblin.hpp"

Goblin::Goblin(Vector2 _pos)
{
    pos = _pos;
    rect = {_pos.x, _pos.y, 30, 35};
    anim.states["idle"] = SpriteSheet("./res/images/goblin/Idle.png", 10.0f, {150, 150}, {57, 67}, {57, 67});
    anim.states["attack"] = SpriteSheet("./res/images/goblin/Attack.png", 30.0f, {150, 150}, {57, 67}, {57, 67});
    anim.states["attack"].looping = false;
    anim.states["death"] = SpriteSheet("./res/images/goblin/Death.png", 10.0f, {150, 150}, {57, 67}, {57, 67});
    anim.SetState("idle");
}

void Goblin::Start()
{
    name = "Goblin";
    color = YELLOW;
    player = GetObject<Player *>();
    tiles = GetObjects<Tile *>();
    attackTime = GetTime();
    attack_hitbox = {pos.x - 25, pos.y, 95, 35};
}

void Goblin::Update()
{
    attack_hitbox.x = pos.x - 25;
    attack_hitbox.y = pos.y;
    
    if (pos.x > player->pos.x)
        direction = -1;
    else
        direction = 1;

    anim.flipped = direction == 1 ? false : true;

    // apply gravity
    velocity += gravity * deltaTime;
    pos.y += velocity * deltaTime;
    rect.y = pos.y;
    if (!grounded) // increase falling speed each frame
        velocity += 20.0f * deltaTime;

    for (auto &tile : tiles)
        if (this->IsTouching(tile))
            this->ResolveTileCollision(tile);

    anim.SetState("idle");

    if (Vector2Distance({player->pos.x + 10, player->pos.y + 20}, {pos.x + 15, pos.y + 17}) < 50 && !attacking && alive && gameTime - attackTime >= 2)
    {
        attacking = true;
        anim.SetState("attack");
        attackTime = gameTime;
    }

    if (attacking)
    {
        if (anim.states[anim.currentState].looping)
        {
            attacking = false;
        }
    }

    rect.x = pos.x;
    rect.y = pos.y;
}

void Goblin::ResolveTileCollision(Tile *tile)
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

        anim.flipped = true;
    }
    // enemy is on the right side of the tile
    else if (col.width <= col.height && pos.x > tile->pos.x)
    {
        if (direction == -1)
            direction = 1;
        pos.x += col.width;
        pos.x += 1.0f;
        rect.x = pos.x;

        anim.flipped = false;
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

void Goblin::DrawExtra()
{
    DrawRectangleLines(attack_hitbox.x, attack_hitbox.y, attack_hitbox.width, attack_hitbox.height, WHITE);
}