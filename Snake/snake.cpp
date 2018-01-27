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
			switch (CheckPosition(pieces[current]->GetX(), pieces[current]->GetY()))
			{
			case SNAKE_BODY:
				running = false;
				break;
			case SNAKE_APPLE:
				DeleteApple(pieces[current]->GetX(), pieces[current]->GetY());
				AddPiece();
				break;
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

int Snake::CheckPosition(unsigned x, unsigned y)
{
	for (Apple* apple : apples) //Check for apple first
	{
		if (apple->GetX() == x && apple->GetY() == y)
		{
			return SNAKE_APPLE;
		}
	}

	for (unsigned i = 0; i < pieces.size(); i++)
	{
		SnakePiece* piece = pieces[i];
		if (piece->GetX() == x && piece->GetY() == y)
		{
			if (i == 0)
				return SNAKE_HEAD;
			else
				return SNAKE_BODY;
		}
	}

	return SNAKE_NONE;
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
	} while (CheckPosition(neu->GetX(), neu->GetY()) != SNAKE_NONE); //Check for empty pos

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
