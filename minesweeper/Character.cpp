#include "Character.h"

Character::Character(short y, short x) {
	this->x = x;
	this->y = y;
}

void Character::run(std::vector<std::vector<Character*>>& board) {
	updateDir();
	if (this->is_flaged) { return ; }
	if (this->getId() == 9) {
		for (short i = 0; i < board.size(); i++)
		{
			for (short j = 0; j < board[0].size(); j++)
			{
				if (board[i][j]->getId() == 9)  board[i][j]->setHide(false);
			}
		}
	}
	else {
		for (short i = 0; i < directons.size(); i++)
		{
			short X = directons[i][0];
			short Y = directons[i][1];

			if (X >= 0				&& Y >= 0 &&
				X < board[0].size() && Y < board.size())
			{
				if (this->id == 0 && board[Y][X]->getId() != 9 && board[Y][X]->getHide()) {
					this->setHide(false);
					board[Y][X]->run(board);
				}
				else this->setHide(false);
			}
		}
	}
}

void Character::findBomb(std::vector<std::vector<Character*>>& board) {
	short count = 0;
	updateDir();
	if (this->getId() != 9) {
		for (short i = 0; i < directons.size(); i++)
		{
			short X = directons[i][0];
			short Y = directons[i][1];
			if (X >= 0 && Y >= 0 &&
				X < board[0].size() && Y < board.size())
			{
				if (board[Y][X]->getId() == 9) {
					count++;
				}
			}
		}
		this->id = count;
	}
	else {
		count = this->id;
	}
}

short Character::getX() { return this->x; }
short Character::getY() { return this->y; }
short Character::getId() { return this->id; }
bool Character::getHide() { return this->hide; }
bool Character::getFlag() { return this->is_flaged; }


void Character::setFlag(bool b) { this->is_flaged = b; }
void Character::setId(short id) { this->id = id; }
void Character::setHide(bool hide) { this->hide = hide; }

void Character::updateDir() {
	directons =
	{
		{this->x - 1 , this->y - 1},
		{this->x     , this->y - 1},
		{this->x + 1 , this->y - 1},
		{this->x - 1 , this->y	 },
		{this->x + 1 , this->y	 },
		{this->x - 1 , this->y + 1},
		{this->x     , this->y + 1},
		{this->x + 1 , this->y + 1}
	};
}