#include <iostream>
#include <vector>
#include <cmath>
#include "raylib.h"

#include "TileLoader.hpp"

#include "GameObject/GameObject.hpp"
#include "GameObject/Player.hpp"
#include "GameObject/Tile.hpp"
#include "GameObject/Coin.hpp"
#include "GameObject/Bug.hpp"
#include "GameObject/Bat.hpp"
#include "GameObject/Jumper.hpp"
#include "GameObject/KillTrigger.hpp"

int main()
{
    const int screenWidth = 960;
    const int screenHeight = 500;

    InitWindow(screenWidth, screenHeight, "Platformer test");

    // create objects
    std::vector<GameObject *> objects;
    objects.reserve(2048);
    // load tile map
    Tiled::Tilemap *tilemap = new Tiled::Tilemap("./res/levels/Level1.json");

    for (auto &layer : tilemap->objectGroups)
    {
        for (auto &object : layer.data["objects"])
        {
            if (object["name"] == "Player")
                objects.emplace_back(new Player({object["x"], object["y"]}));
            else if (object["name"] == "Coin")
                objects.emplace_back(new Coin({object["x"], object["y"]}));
            else if (object["name"] == "Bug")
                objects.emplace_back(new Bug({object["x"], object["y"]}, -1));
            else if (object["name"] == "Jumper")
                objects.emplace_back(new Jumper({object["x"], object["y"]}, -1));
            else if (object["name"] == "Bat")
                objects.emplace_back(new Bat({object["x"], object["y"]}, -1));
            else if (object["name"] == "KillTrigger")
                objects.emplace_back(new KillTrigger({object["x"], object["y"]}, {object["width"], object["height"]}));
            else
                objects.emplace_back(new Tile({object["x"], object["y"]}, {object["width"], object["height"]}));
        }
    }

    for (auto &object : objects)
    {
        object->SetObjectList(&objects);
        object->Start();
    }

    Player *player = GameObject::GetObject<Player *>("Player", &objects);

    Camera2D camera = {0};
    camera.target = {screenWidth / 2.0f, screenHeight / 2.0f};
    camera.offset = {screenWidth / 2.0f, screenHeight / 2.0f};
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    SetTargetFPS(60);

    float deltaTime;
    float gameTime;
    while (!WindowShouldClose())
    {
        deltaTime = GetFrameTime();
        gameTime = GetTime();
        // update objects
        for (int i = 0; i < objects.size(); i++)
        // for (auto &object : (*objects))
        {
            objects[i]->deltaTime = deltaTime;
            objects[i]->gameTime = gameTime;
            objects[i]->Update();
        }

        // delete "deleted" objects
        for (int i = 0; i < objects.size(); i++)
        {
            if (objects[i]->deleted)
            {
                delete objects[i];
                objects.erase(objects.begin() + i--);
            }
        }

        // update camera
        camera.target.x = roundf(player->pos.x);
        if (camera.target.x < screenWidth / 2)
            camera.target.x = roundf(screenWidth / 2);

        // start drawing tiles and objects
        BeginMode2D(camera);
        ClearBackground(tilemap->backgroundcolor);

        tilemap->Draw();

        for (auto &object : objects)
        {
            object->UpdateDraw();
            object->DrawExtra();
        }

        EndMode2D();

        BeginDrawing();

        DrawText(TextFormat("Coins: %i", player->coins), 10, 10, 10, WHITE);
        DrawText(TextFormat("Total number of objects: %i", objects.size()), 10, 25, 10, WHITE);
        DrawText(TextFormat("Grounded: %s", player->grounded ? "true" : "false"), 10, 40, 10, WHITE);
        DrawText(TextFormat("Pos: x: %f y: %f", player->rect.x, player->rect.y), 10, 55, 10, WHITE);
        DrawText(TextFormat("Velocity: x: %f y: %f", player->velocity.x, player->velocity.y), 10, 70, 10, WHITE);
        DrawText(TextFormat("FPS: %i", GetFPS()), 10, 85, 10, WHITE);

        EndDrawing();
    }

    for (int i = 0; i < objects.size(); i++)
    {
        delete objects[i];
        objects.erase(objects.begin() + i--);
    }
    // unload tilemap
    delete tilemap;
    return 0;
}