#pragma once
#include "GameObject.hpp"
#include "Player.hpp"

class KillTrigger : public GameObject
{
public:
    Player *player;

    KillTrigger(Vector2 _pos, Vector2 _size);

    void Start();
    void Update();
};
