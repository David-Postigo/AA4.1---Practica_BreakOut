#include <Windows.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>

#include "Wall.h"
#include "Brick.h"
#include "Pad.h"
#include "Ball.h"
#include "Scene.h"

#define MAP_SIZE 15

int main() {
    srand((unsigned int)time(NULL));
    int sceneActive = 0;
    std::vector<GameObject*> objects;

    //Carga de escenas
    scenes.push_back(new GameScene());
    while (true)
    {
        scenes[sceneActive].Start();
        scenes[sceneActive].Update();
    }

    return 0;
}
