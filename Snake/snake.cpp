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
