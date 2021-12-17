#pragma once
#include "GameObject.hpp"
#include "Player.hpp"

class Coin : public GameObject
{
public:
    Player *player;
    Vector2 originalPos;
    Vector2 tempPos;

    Coin(Vector2 _pos);

    void Start();
    void Update();
};
