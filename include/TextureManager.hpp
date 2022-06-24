#include "raylib.h"
#include <string>
#include <unordered_map>

class TextureManager
{
    public:
    std::unordered_map<std::string, Texture2D> textures;

    Texture2D Load(const char *path)
    {
        if (textures.find(path) != textures.end())
            return textures[path];
        
        textures[path] = LoadTexture(path);
        return textures[path];
    }

    void Unload(const char *texture)
    {
        if (textures.find(texture) != textures.end())
            UnloadTexture(textures[texture]);
        else
            std::cout << "Texture " << texture << " not found." << std::endl;
    }

    ~TextureManager()
    {
        for (auto &texture: textures)
        {
            UnloadTexture(texture.second());
        }
    }
};
