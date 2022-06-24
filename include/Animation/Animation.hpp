#include "raylib.h"
#include <unordered_map>
#include <string>

class SpriteSheet
{
    public:
    Vector2 frameSize;
    Vector2 offset;
    Vector2 offset_flipped;
    Texture2D texture;
    float FPS;
    int frame;
    int frameCount;
    double lastTime;
    int columns;
    bool looping = true;
    bool finished = false;

    SpriteSheet() {}

    SpriteSheet(const char* path, int _FPS, Vector2 _size, Vector2 _offset = {0, 0}, Vector2 _offset2 = {0, 0}, int _frames = 0)
    {
        texture = LoadTexture(path);
        FPS = _FPS;
        frame = 0;
        frameSize = _size;
        offset = _offset;
        offset_flipped = _offset2;

        columns = texture.width / (int) frameSize.x;

        if (_frames == 0)
            frameCount = columns * (texture.height / (int) frameSize.y);
        else
            frameCount = _frames;
    }

    void Draw(Vector2 pos, bool flipped = false, bool flipped_vertical = false)
    {
        if (flipped)
        {
            pos.x -= offset_flipped.x;
            pos.y -= offset_flipped.y;
        }
        else
        {
            pos.x -= offset.x;
            pos.y -= offset.y;
        }

        int x = (frame % columns) * frameSize.x;
        int y = (frame / columns) * frameSize.y;
        int dir = flipped ? -1 : 1;
        int dir_vertical = flipped_vertical ? -1 : 1;

        if (frame == frameCount - 1 && !looping)
            finished = true;


        if ((GetTime() - lastTime) >= (1 / FPS))
        {
            frame = ++frame % frameCount;
            lastTime = GetTime();
        }

        DrawTextureRec(texture, {(float) x, (float) y, frameSize.x * dir, frameSize.y * dir_vertical}, pos, WHITE);
    }

    ~SpriteSheet()
    {
        // UnloadTexture(texture);
    }
};

class Animation
{
    public:
    std::unordered_map<std::string, SpriteSheet> states;
    std::string currentState;
    bool flipped = false;
    bool flipped_vertical = false;

    void SetState(const char* newState)
    {
        if (states.size() != 0)
        {
            if (!states[currentState].looping && !states[currentState].finished)
                return;
        }

        if (currentState != newState)
        {
            states[currentState].finished = false;

            currentState = newState;
            states[currentState].frame = 0;
        }
    }

    void Draw(Vector2 pos)
    {
        states[currentState].Draw(pos, flipped, flipped_vertical);
    }
};
