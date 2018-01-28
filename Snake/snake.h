#pragma once
#include <vector>
#include <Windows.h>

#include "imgui/imgui.h"

class SnakePiece
{
public:
	SnakePiece(unsigned setX, unsigned setY) : x{ setX }, y{ setY } {};

	SnakePiece& operator+=(const std::vector<int> vel)
	{
		x += vel[0];
		y -= vel[1]; //Subtract cause we draw it this way

		return *this;
	}

	unsigned GetX() const
	{
		return x;
	}

	void SetX(unsigned setX)
	{
		x = setX;
	}

	unsigned GetY() const
	{
		return y;
	}

	void SetY(unsigned setY)
	{
		y = setY;
	}

	void SetPosition(const SnakePiece* piece)
	{
		x = piece->GetX();
		y = piece->GetY();
	}

private:
	unsigned x;
	unsigned y;
};

class Apple
{
public:
	Apple(unsigned w, unsigned h) : x{ rand() % (w - 1) }, y{ rand() % (h - 1) } {};

	unsigned GetX() const
	{
		return x;
	}

	unsigned GetY() const
	{
		return y;
	}

private:
	unsigned x;
	unsigned y;
};

enum
{
	SNAKE_NONE = 0,
	SNAKE_HEAD = 1,
	SNAKE_BODY,
	SNAKE_APPLE,
};

class Snake
{
public:
	//Game Related
	std::vector<SnakePiece*> pieces;

	std::vector<int> velocity;

	std::vector<Apple*> apples;

	void Init(unsigned w, unsigned h);

	void UpdatePositions();

	void AddPiece();

	void SetVelocity(int x, int y);

	std::vector<int> CheckPosition(unsigned x, unsigned y);

	bool ResultNone(std::vector<int> results);

	bool ResultHead(std::vector<int> results);

	bool ResultBody(std::vector<int> results);

	bool ResultApple(std::vector<int> results);

	bool IsOutOfBounds(unsigned x, unsigned y);

	bool IsRunning()
	{
		return running;
	}

	void AddApple(unsigned w, unsigned h);

	void DeleteApple(unsigned num);
	void DeleteApple(unsigned x, unsigned y);

	//Drawing and stuff
	void Start();
	void Run();

	void DrawFilledRect(ImDrawList* drawlist, unsigned x, unsigned y, ImVec4 color);
	void Draw();

	void CheckControls();
	void CheckAppleSpawn();

private:
	bool running = false;
};