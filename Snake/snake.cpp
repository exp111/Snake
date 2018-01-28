#include "snake.h"

#include "main.h"

void Snake::Init(unsigned w, unsigned h)
{
	//Init Head
	SnakePiece* first = new SnakePiece(w, h);
	pieces.push_back(first);

	//Init Velocity
	//X
	velocity.push_back(0);
	//Y
	velocity.push_back(1);

	//Start the game
	running = true;
}

void Snake::UpdatePositions()
{
	//Do Update
	for (int current = pieces.size() - 1; current >= 0; current--)
	{
		if (current > 0)
		{
			pieces[current]->SetPosition(pieces[current - 1]);
		}
		else
		{
			*pieces[current] += velocity;


			//Check for Collision with Body/Apple or Border
			auto results = CheckPosition(pieces[current]->GetX(), pieces[current]->GetY());
			
			if (ResultBody(results))
				running = false;
			
			if (ResultApple(results))
			{
				DeleteApple(pieces[current]->GetX(), pieces[current]->GetY());
				AddPiece();
			}

			if (IsOutOfBounds(pieces[current]->GetX(), pieces[current]->GetY()))
				running = false;
		}
	}
}

void Snake::AddPiece()
{
	SnakePiece* neu = new SnakePiece(pieces[pieces.size() - 1]->GetX(), pieces[pieces.size() - 1]->GetY());
	pieces.push_back(neu);
}

void Snake::SetVelocity(int x, int y)
{
	velocity[0] = x;
	velocity[1] = y;
}

std::vector<int> Snake::CheckPosition(unsigned x, unsigned y)
{
	std::vector<int> result;

	for (unsigned i = 0; i < pieces.size(); i++)
	{
		SnakePiece* piece = pieces[i];
		if (piece->GetX() == x && piece->GetY() == y)
		{
			if (i == 0)
				result.push_back(SNAKE_HEAD);
			else
				result.push_back(SNAKE_BODY);
		}
	}

	for (Apple* apple : apples) //Check for apple first
	{
		if (apple->GetX() == x && apple->GetY() == y)
		{
			result.push_back(SNAKE_APPLE);
		}
	}

	return result;
}

bool Snake::ResultNone(std::vector<int> results)
{
	return results.size() == 0;
}

bool Snake::ResultHead(std::vector<int> results)
{
	for (auto result : results)
	{
		if (result == SNAKE_HEAD)
			return true;
	}

	return false;
}

bool Snake::ResultBody(std::vector<int> results)
{
	for (auto result : results)
	{
		if (result == SNAKE_BODY)
			return true;
	}

	return false;
}

bool Snake::ResultApple(std::vector<int> results)
{
	for (auto result : results)
	{
		if (result == SNAKE_APPLE)
			return true;
	}

	return false;
}

bool Snake::IsOutOfBounds(unsigned x, unsigned y)
{
	return  x < 0 || y < 0 || x >= boardWidth || y >= boardHeight;
}

void Snake::AddApple(unsigned w, unsigned h)
{
	Apple* neu;
	do
	{
		neu = new Apple(w, h);
	} while (!ResultNone(CheckPosition(neu->GetX(), neu->GetY()))); //Check for empty pos

	apples.push_back(neu);
}

void Snake::DeleteApple(unsigned num)
{
	apples.erase(apples.begin() + num);
}

void Snake::DeleteApple(unsigned x, unsigned y)
{
	for (unsigned i = 0; i < apples.size(); i++)
	{
		Apple* apple = apples[i];
		if (apple->GetX() == x && apple->GetY() == y)
		{
			DeleteApple(i);
		}
	}
}

void Snake::Start()
{
	Init(boardWidth / 2, boardHeight / 2);
}

void Snake::Run()
{
	static int timer = 0;
	if (IsRunning())
	{
		if (timer > 10)
		{
			UpdatePositions();
			CheckAppleSpawn();
			timer = 0;
		}
		timer++;
		Draw();
		CheckControls();
	}
	else
	{
		//reset Game
		pieces.erase(pieces.begin(), pieces.end());
		apples.erase(apples.begin(), apples.end());
		velocity.erase(velocity.begin(), velocity.end());
	}
}

void Snake::DrawFilledRect(ImDrawList* drawlist, unsigned x, unsigned y, ImVec4 color)
{
	ImVec2 winpos = ImGui::GetWindowPos();
	const static float titleBarHeight = ImGui::GetTextLineHeight() + ImGui::GetStyle().FramePadding.y * 2.0f;
	drawlist->AddRectFilled(ImVec2(winpos.x + x*tileWidth, winpos.y + titleBarHeight + y*tileHeight), ImVec2(winpos.x + (x + 1)*tileWidth, winpos.y + titleBarHeight + (y + 1)*tileHeight), ImGui::GetColorU32(color));
}

void Snake::Draw()
{
	ImGui::Begin("Snake");
	const static float titleBarHeight = ImGui::GetTextLineHeight() + ImGui::GetStyle().FramePadding.y * 2.0f;
	ImGui::SetWindowSize(ImVec2(boardWidth * tileWidth, boardHeight * tileHeight + titleBarHeight));

	auto drawlist = ImGui::GetWindowDrawList();
	for (unsigned y = 0; y < boardHeight; y++)
	{
		for (unsigned x = 0; x < boardWidth; x++)
		{
			auto result = CheckPosition(x, y);

			if (ResultNone(result))
				//draw black tile
				DrawFilledRect(drawlist, x, y, ImVec4(0, 0, 0, 255));
			else if (ResultHead(result))
				//draw head -> white with eyes
				DrawFilledRect(drawlist, x, y, ImVec4(255, 255, 255, 255));
			else if (ResultBody(result))
				//draw body -> white
				DrawFilledRect(drawlist, x, y, ImVec4(255, 255, 255, 255));
			else if (ResultApple(result))
				//draw apple -> white
				DrawFilledRect(drawlist, x, y, ImVec4(255, 255, 255, 255));
		}
	}

	ImGui::End();
}

void Snake::CheckControls()
{
	if (IsKeyDown(VK_UP))
		SetVelocity(0, 1);
	else if (IsKeyDown(VK_RIGHT))
		SetVelocity(1, 0);
	else if (IsKeyDown(VK_DOWN))
		SetVelocity(0, -1);
	else if (IsKeyDown(VK_LEFT))
		SetVelocity(-1, 0);

#ifdef _DEBUG
	if (IsKeyDown(VK_CONTROL))
		AddPiece();
#endif //_DEBUG
}

void Snake::CheckAppleSpawn()
{
	if (rand() % 100 + 1 < appleChance) //1 to 100
	{
		AddApple(boardWidth, boardHeight);
	}
}