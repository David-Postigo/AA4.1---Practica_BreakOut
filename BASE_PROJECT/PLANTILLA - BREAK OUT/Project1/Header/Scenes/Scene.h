#pragma once
#include <vector>
#include "GameObject.h"
#include <Windows.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>

#include "Wall.h"
#include "Brick.h"
#include "Pad.h"
#include "Ball.h"

using namespace std;

class Scene
{
protected:
	vector<GameObject*> objects;

public:
	Scene();
	~Scene();

public:
	virtual void Start() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;

};

class GameScene: public Scene
{
	vector<GameObject*> objects;

public:
	Scene();
	~Scene();
private:
	void CreateWalls(std::vector<GameObject*>& objects) {
		for (int i = 0; i < MAP_SIZE; i++) {
			objects.push_back(new Wall(Vector2(i, 0), YELLOW, false));
			objects.push_back(new Wall(Vector2(i, MAP_SIZE - 1), YELLOW, true));

			if (i > 0 && i < MAP_SIZE - 1) {
				objects.push_back(new Wall(Vector2(0, i), YELLOW, false));
				objects.push_back(new Wall(Vector2(MAP_SIZE - 1, i), YELLOW, false));
			}
		}
	}
	void CreateBricks(std::vector<GameObject*>& objects) {
		for (int row = 1; row <= 3; row++) {
			for (int col = 1; col < MAP_SIZE - 1; col++) {
				objects.push_back(new Brick(Vector2(col, row), CYAN));
			}
		}
	}
	void CreatePlayer(std::vector<GameObject*>& objects) {
		objects.push_back(new Pad(Vector2(MAP_SIZE / 2, (MAP_SIZE * 3) / 4), WHITE, 1, MAP_SIZE));
	}
	void CreateBall(std::vector<GameObject*>& objects) {
		objects.push_back(new Ball(Vector2(2, MAP_SIZE / 2), WHITE, objects));
	}
public:
	void Start() override {
		CreateWalls();
		CreateBricks();
		CreatePlayer();
		CreateBall();
	};
	virtual void Update() override {
		bool isPlaying = true;

		while (isPlaying) {
			Sleep(100);

			for (int i = 0; i < objects.size(); i++) {
				objects[i]->Update();
			}

			Render();
		}
	};
	virtual void Render() override {
		system("cls");
		ConsoleSetColor(WHITE, BLACK);

		for (int i = 0; i < objects.size(); i++) {
			objects[i]->Render();
		}

		ConsoleXY(MAP_SIZE, MAP_SIZE);
	};

};