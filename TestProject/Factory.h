#pragma once
#include <vector>
#include <map>
struct entity;

class Factory
{
    static std::vector<entity> entities;
    static std::vector<int> addEntities;
    static std::vector<int> remEntities;
    static std::map<std::string, std::vector<int>> scene;
    static std::string currentScene;

    static void killEntity(int);
    static int dupEntity(int);

    static int makeBall(...);
    static int makeDinosaur(...);
    static int makeMonkey(...);
    static int makeChicken(...);

    // Fun stuff!
    int make(std::string parseableData);
    std::string makeScene(std::string parseableData);
    void serialize(std::string outfilename);
};