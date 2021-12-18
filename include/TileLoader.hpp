#pragma once
#include "raylib.h"
#include "json.hpp"
#include <string>
#include <cstring>
#include <vector>
#include <fstream>
#include <sstream>
#include <unordered_map>

namespace Tiled
{
    class Tileset
    {
    public:
        int columns;
        std::string image;
        Texture2D texture;
        Vector2 imageSize;
        int margin;
        std::string name;
        int spacing;
        int tileCount;
        std::string tiledVersion;
        Vector2 tileSize;
        std::string Type;
        std::string version;
        int firstgid;

        Tileset(const char *filePath, int _firstgid)
        {
            // load and parse the json file
            std::ifstream file(filePath);
            auto data = nlohmann::json::parse(file);

            // load the image and set other properties
            columns = data["columns"];
            image = data["image"];
            imageSize = {data["imagewidth"], data["imageheight"]};
            margin = data["margin"];
            name = data["name"];
            spacing = data["spacing"];
            tileCount = data["tilecount"];
            tiledVersion = data["tiledversion"];
            tileSize = {data["tilewidth"], data["tileheight"]};
            Type = data["type"];
            version = data["version"];
            std::string path = "./res/";
            path += image.erase(0, 3);
            texture = LoadTexture(path.c_str());
            firstgid = _firstgid;
        }

        void Draw(int i, Vector2 pos)
        {
            i = i - firstgid;
            int x = (i % columns) * tileSize.x;
            int y = (i / columns) * tileSize.y;
            DrawTextureRec(texture, {(float) x, (float) y, tileSize.x, tileSize.y}, pos, WHITE);
        }

        ~Tileset()
        {
            std::cout << "Deleting tileset" << image << std::endl;
            UnloadTexture(texture);
        }
    };

    class TileLayer
    {
        public:
        int id;
        int height;
        int width;
        int x;
        int y;
        int tileCount;
        std::string name;
        int *data;

        TileLayer(nlohmann::json layer)
        {
            id = layer["id"];
            width = layer["width"];
            height = layer["height"];
            tileCount = width * height;
            name = layer["name"];
            x = layer["x"];
            y = layer["y"];
            data = (int *) malloc(sizeof(int) * tileCount);
            for (int i = 0; i < tileCount; i++)
                data[i] = layer["data"][i];
        }

        ~TileLayer()
        {
            std::cout << "Deleting tile layer " << id << std::endl;
            free(data);
        }
    };
    
    class ObjectGroup
    {
        public:
        nlohmann::json data;

        ObjectGroup(nlohmann::json layer)
        {
            data = layer;
        }
    };

    Color hex2rgb(std::string hex)
    {
        hex.erase(0, 1);
        unsigned int rgb;
        std::stringstream ss;
        ss << std::hex << hex;
        ss >> rgb;
        return
        {
            (unsigned char) ((rgb >> 16) & 0xFF),
            (unsigned char) ((rgb >> 8) & 0xFF),
            (unsigned char) ((rgb) & 0xFF),
            255
        };
    }

    class Tilemap
    {
        public:
        int width;
        int height;
        int tilewidth;
        int tileheight;
        int compressionlevel;
        bool infinite;

        int tilesetCount = 0;
        Color backgroundcolor = {255, 255, 255, 255};
        
        std::vector<Tileset *> tilesets;
        std::vector<TileLayer *> tileLayers;
        std::vector<ObjectGroup> objectGroups;

        Tilemap(const char* mapFile)
        {
            std::ifstream file(mapFile);
            auto mapData = nlohmann::json::parse(file);
            width = mapData["width"];
            height = mapData["height"];
            tilewidth = mapData["tilewidth"];
            tileheight = mapData["tileheight"];
            compressionlevel = mapData["compressionlevel"];
            infinite = mapData["infinite"];

            if (mapData.find("backgroundcolor") != mapData.end())
                backgroundcolor = hex2rgb(mapData["backgroundcolor"]);

            for (auto &tileset : mapData["tilesets"])
            {
                int firstgid = tileset["firstgid"];
                std::string source = tileset["source"];
                source.erase(0, 3);
                std::string path = "./res/" + source;
                tilesets.push_back(new Tileset(path.c_str(), firstgid));
                tilesetCount++;
            }

            for (auto &layer : mapData["layers"])
            {
                if (layer["type"] == "objectgroup")
                    objectGroups.push_back(ObjectGroup(layer));
                else if (layer["type"] == "tilelayer")
                    tileLayers.emplace_back(new TileLayer(layer));
            }
        }

        void Draw()
        {
            for (auto &layer : tileLayers)
            {
                for (int i = 0; i < layer->tileCount; i++)
                {
                    if (layer->data[i] == 0)
                        continue;

                    int tile = layer->data[i];
                    
                    for (auto &tileset : tilesets)
                    {
                        if (tile >= tileset->firstgid && tile < tileset->firstgid + tileset->tileCount)
                        {
                            float x = (i % width) * tilewidth;
                            float y = (i / width) * tileheight;
                            tileset->Draw(tile, {x, y});
                            break;
                        }
                    }

                }
            }
        }

        ~Tilemap()
        {
            std::cout << "Deleting tilesets" << std::endl;
            for (auto &tileset: tilesets)
                delete tileset;
            
            std::cout << "Deleting tile layers" << std::endl;
            for (auto &tileLayer: tileLayers)
                delete tileLayer;
        }
    };
}
