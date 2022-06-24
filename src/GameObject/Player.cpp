#include "Player.hpp"
#include "Bug.hpp"

Player::Player(Vector2 _pos)
{
    pos = _pos;
    originalPos = pos;
    coins = 0;

    anim.states["idle"] = SpriteSheet("./res/images/player/Idle.png", 15.0f, {180, 180}, {85, 69}, {75, 69});
    anim.states["run"] = SpriteSheet("./res/images/player/Run.png", 15.0f, {180, 180}, {85, 69}, {75, 69});
    anim.states["jump"] = SpriteSheet("./res/images/player/Jump.png", 15.0f, {180, 180}, {85, 69}, {75, 69});
    anim.states["attack"] = SpriteSheet("./res/images/player/Attack1.png", 15.0f, {180, 180}, {85, 69}, {75, 69});
    anim.states["attack2"] = SpriteSheet("./res/images/player/Attack2.png", 15.0f, {180, 180}, {85, 69}, {75, 69});
    anim.states["attack"].looping = false;
    anim.states["attack2"].looping = false;

    anim.SetState("idle");
}

void Player::Start()
{
    name = "Player";
    rect = {pos.x, pos.y, 20, 45};
    color = MAROON;
    debug = true;

    attack_hitbox = {pos.x + 20, pos.y, 25, 45};
    attack_hitbox2 = {pos.x, pos.y + 20, 65, 20};
}

void Player::DrawExtra()
{
    DrawRectangleLines(attack_hitbox.x, attack_hitbox.y, attack_hitbox.width, attack_hitbox.height, WHITE);
    DrawRectangleLines(attack_hitbox2.x, attack_hitbox2.y, attack_hitbox2.width, attack_hitbox2.height, WHITE);
}

void Player::Update()
{
    if (IsKeyPressed(KEY_R))
    {
        pos = {10, 10};
        velocity = {0, 0};
    }

    if (velocity.y > 50.0f)
    {
        fallTime = gameTime;
        grounded = false;
        anim.SetState("jump");
    }

    // apply gravity
    velocity.y += gravity * deltaTime;
    pos.y += velocity.y * deltaTime;
    rect.y = pos.y;

    // movement
    if (IsKeyDown(KEY_LEFT) && !IsKeyDown(KEY_RIGHT))
    {
        if (velocity.x > 0.0f)
            velocity.x = 0.0f;
        
        velocity.x -= speed * deltaTime * acceleration;

        if (velocity.x < -speed)
            velocity.x = -speed;
        
        if (grounded)
        {
            anim.SetState("run");
        }
        anim.flipped = true;
    }
    if (IsKeyDown(KEY_RIGHT) && !IsKeyDown(KEY_LEFT))
    {
        if (velocity.x < 0.0f)
            velocity.x = 0.0f;

        velocity.x += speed * deltaTime * acceleration;

        if (velocity.x > speed)
            velocity.x = speed;
        
        if (grounded)
        {
            anim.SetState("run");
        }
        anim.flipped = false;
    }

    // slow down & stop the player
    if ((!IsKeyDown(KEY_RIGHT) && !IsKeyDown(KEY_LEFT)) || (IsKeyDown(KEY_RIGHT) && IsKeyDown(KEY_LEFT)))
    {
        if ((velocity.x < 0.0f || velocity.x > 0.0f) && !grounded)
            velocity.x = velocity.x + ((0.0f - velocity.x) * deceleration_air);
        if ((velocity.x < 0.0f || velocity.x > 0.0f) && grounded)
            velocity.x = velocity.x + ((0.0f - velocity.x) * deceleration);
        if (fabs(velocity.x) < 0.25f)
            velocity.x = 0.0f;
        
        if (grounded)
            anim.SetState("idle");
    }

    if (attacking && grounded) // slow down the player while attacking
        velocity.x *= 0.75f;

    pos.x += velocity.x;

    // jump
    if ((IsKeyPressed(KEY_SPACE) && grounded))
    {
        pos.y -= 1.0f;
        velocity.y -= jumpVel;
        grounded = false;
        anim.SetState("jump");
    }

    // stop jumping when space is released
    if (IsKeyReleased(KEY_SPACE) && velocity.y < 0.0f)
        velocity.y *= 0.5f;
    
    if (IsKeyPressed(KEY_LEFT_CONTROL) && !attacking)
    {
        anim.SetState("attack");
        attacking = true;
    }

    if (attacking)
    {
        if (anim.states[anim.currentState].looping)
        {
            attacking = false;
        }
    }

    // update hitbox position
    rect.x = pos.x;
    rect.y = pos.y;

    // update attack hitbox position
    if (anim.flipped)
        attack_hitbox.x = pos.x - attack_hitbox.width;
    else
        attack_hitbox.x = pos.x + rect.width;
    attack_hitbox.y = pos.y;

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
        velocity.y *= 0.5f;
        pos.y += col.height;
        rect.y = pos.y;
    }
}