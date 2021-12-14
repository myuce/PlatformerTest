#pragma once
#include <iostream>
#include <string>
#include <math.h>
#include "raylib.h"
#include "raymath.h"
#include "mathextra.hpp"

class GameObject
{
public:
    bool deleted = false;
    bool debug = false;
    Vector2 pos;
    Vector2 size;
    Rectangle rect;
    std::string name;
    Color color;
    std::vector<GameObject *> objects;

    GameObject(){};
    virtual ~GameObject(){};

    virtual void Start() {}
    virtual void Update() {}
    virtual void DrawExtra() {}
    virtual void OnCollision(GameObject *object) {}

    // returns the first game object with the specified type and name
    template <class T>
    T GetObject(const char *name)
    {
        for (int i = 0; i < objects.size(); i++)
            if (objects[i]->name == name && dynamic_cast<T>(objects[i] != nullptr))
                return dynamic_cast<T>(objects[i]);
        return nullptr;
    }

    // returns the first game object with the specified type
    template <class T>
    T GetObject()
    {
        for (int i = 0; i < objects.size(); i++)
            if (dynamic_cast<T>(objects[i]) != nullptr)
                return dynamic_cast<T>(objects[i]);
        return nullptr;
    }

    // returns the first object with the specified type from a GameObject* vector
    template <class T>
    static T GetObject(const char *name, std::vector<GameObject *> &objects)
    {
        for (int i = 0; i < objects.size(); i++)
            if (objects[i]->name == name)
                return dynamic_cast<T>(objects[i]);
        return nullptr;
    }

    // returns a GameObject* vector of objects with the specified name
    template <class T>
    std::vector<T> GetObjects(const char *name)
    {
        std::vector<T> res;
        for (int i = 0; i < objects.size(); i++)
            if (objects[i]->name == name)
                res.push_back(dynamic_cast<T>(objects[i]));
        return res;
    }

    // returns a GameObject* vector of objects with the specified type
    template <class T>
    std::vector<T> GetObjects()
    {
        std::vector<T> res;
        for (int i = 0; i < objects.size(); i++)
            if (dynamic_cast<T>(objects[i]) != nullptr)
                res.push_back(dynamic_cast<T>(objects[i]));
        return res;
    }

    template <class T>
    bool IsTouching(T object)
    {
        return CheckCollisionRecs(rect, object->rect);
    }

    void SetObjectList(std::vector<GameObject *> _objects)
    {
        objects = _objects;
    }

    void UpdateDraw()
    {
        if (debug)
            DrawRectangleRec(rect, color);
    }

    void Delete()
    {
        deleted = true;
    }

    void Delete(GameObject * object)
    {
        object->deleted = true;
    }
};