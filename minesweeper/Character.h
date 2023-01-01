#pragma once
#include <iostream>
#include <vector>


class Character
{
public:
	Character(short y, short x);

	void run(std::vector<std::vector<Character*>>& board);
	
	void findBomb(std::vector<std::vector<Character*>>& board);

	short getX();
	short getY();
	short getId();
	bool getHide();
	bool getFlag();

	void setId(short id);
	void setHide(bool hide);
	void setFlag(bool b);
	void updateDir();

private:
	short x = -1;
	short y = -1;
	short id = 0;
	bool hide = true;
	bool is_flaged = false;
	std::vector<std::vector<int>> directons
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
};

