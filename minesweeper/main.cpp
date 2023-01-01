#include <iostream>
#include <vector>
#include <string>

#include "Character.h"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

// window var's
unsigned int width = 800;
unsigned int height = 600;
bool isFullScreen = false;
//1920, 1080, sf::Style::Fullscreen
sf::RenderWindow window(sf::VideoMode(width, height), "minesweeper");


// map resources
short wi = 17, he = 17;

std::vector<std::vector<Character*>> board(he, std::vector<Character*>(wi));
float side = (height - 40) / he;
float paddingUp = height - (he * side);
float paddingLeft = width - (wi * side);

std::vector<sf::RectangleShape> lines;

// my var's

short level = 0;
short bombs = 0;

sf::Font font;

void drawing_board();
void CharsShow();
void clearMemory();
void addBombs(short );
void settingSet();
void winCheck();

int main() {
    

    font.loadFromFile("arial.ttf");


	window.setFramerateLimit(60);
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::MouseButtonPressed) {
                short mouseX = sf::Mouse::getPosition(window).x;
                short mouseY = sf::Mouse::getPosition(window).y;

                if (level == 0) {
                    if (mouseX > (paddingLeft * 0.85) && mouseX < (paddingLeft * 1.5) + paddingLeft * 0.85) {
                        if ((mouseY > paddingUp) && mouseY < (paddingUp * 2.5)) {
                            level = 1;
                            settingSet();
                            break;
                        }
                        else if ((mouseY > paddingUp * 3.5) && mouseY < paddingUp * 5) {
                            level = 2;
                            settingSet();
                            break;
                        }
                        else if ((mouseY > paddingUp * 6) && mouseY < paddingUp * 7.5) {
                            level = 3;
                            settingSet();
                            break;
                        }
                    }
                }
                else {
                    if (mouseX > 5 && mouseX < 25) {
                        if (mouseY > 5 && mouseY < 25) {
                            level = 0;
                        }
                    }
                    short ArrPosX = (mouseX - paddingLeft/2) / side;
                    short ArrPosY = (mouseY - paddingUp/2) / side;

                    if (ArrPosX >= 0 && ArrPosY >= 0 &&
                        ArrPosX < board[0].size() && ArrPosY < board.size())
                    {
                        bool flag = board[ArrPosY][ArrPosX]->getFlag();

                        if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) board[ArrPosY][ArrPosX]->setFlag(!flag);
                        else board[ArrPosY][ArrPosX]->run(board);
                    }
                    winCheck();
                }
                
            }

            if (event.type == sf::Event::KeyReleased) {
                if (event.key.code == sf::Keyboard::Escape) {
                    window.close();
                }
            }

            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        // Events : end

        window.clear(sf::Color(80, 80, 80, 255));

        if (level == 0)
        {
            std::vector<sf::RectangleShape> levels;
            std::vector<sf::Text> lvltxt;
            for (short i = 0; i < 3; i++)
            {
                sf::RectangleShape levelr(sf::Vector2f(paddingLeft * 1.5, paddingUp * 1.5));
                levelr.setFillColor(sf::Color(20, 20, 20, 255));
                levelr.setPosition(sf::Vector2f(paddingLeft * 0.85, paddingUp + paddingUp * (2.5 * i)));

                sf::Text leveltxt("Level " + std::to_string(i+1), font);
                leveltxt.setPosition(sf::Vector2f( (paddingLeft * 0.85) * 1.6 , (paddingUp + paddingUp * (2.5 * i) + 25 ) ) );
                leveltxt.setFillColor(sf::Color(255,255,255,255));

                levels.push_back(levelr);
                lvltxt.push_back(leveltxt);
            }

            for (short i = 0; i < 3; i++)
            {
                window.draw(levels[i]);
                window.draw(lvltxt[i]);
            }
        }
        else {
            drawing_board();

            sf::RectangleShape back(sf::Vector2f(20, 20));
            back.setFillColor(sf::Color(20, 20, 20, 255));
            back.setPosition(sf::Vector2f(5, 5));

            sf::Text backtxt("<", font, 16);
            backtxt.setPosition(sf::Vector2f(10, 5));
            backtxt.setFillColor(sf::Color(255, 255, 255, 255));

            window.draw(back);
            window.draw(backtxt);
        }
		window.display();
	}
    clearMemory();

	return 0;
}

//                                                          Functions 

void drawing_board() {
    CharsShow();
    // lines clear
    lines = {};

    side = (height - 40) / he;
    paddingUp = height - (he * side);
    paddingLeft = width - (wi * side);

    // vertical lines
    for (short i = 0; i <= wi; i++) {
        sf::RectangleShape line(sf::Vector2f(height - paddingUp, 3));
        line.setFillColor(sf::Color(0, 0, 0, 255));
        line.rotate(90);
        line.setPosition(sf::Vector2f((paddingLeft / 2) + (side * i),
            paddingUp / 2));

        lines.push_back(line);
    }


    // horizontal lines
    for (short i = 0; i <= he; i++) {
        sf::RectangleShape line(sf::Vector2f(width - paddingLeft, 3));
        line.setFillColor(sf::Color(0, 0, 0, 255));
        line.setPosition(sf::Vector2f(paddingLeft / 2.f,
            (paddingUp / 2.f) + (side * i)));

        lines.push_back(line);
    }

    // board lines
    for (short i = 0; i < lines.size(); i++) {
        window.draw(lines[i]);
    }
}
void CharsShow() {
    sf::RectangleShape rect(sf::Vector2f(side,side));
    //board coloring
    for (short i = 0; i < he; i++)
    {
        for (short j = 0; j < wi; j++)
        {
            if(board[i][j]->getHide()){
                if (board[i][j]->getFlag()) {
                    rect.setFillColor(sf::Color(224, 232, 46, 255));
                    rect.setPosition(j * side + paddingLeft / 2, i * side + paddingUp / 2);
                }
                else {
                    rect.setFillColor(sf::Color(50, 50, 50, 255));
                    rect.setPosition(j * side + paddingLeft / 2, i * side + paddingUp / 2);
                }
                window.draw(rect);
            }
            else {
                sf::Text text("", font, 18);
                rect.setFillColor(sf::Color(80, 80, 80, 255));
                rect.setPosition(j * side + paddingLeft / 2, i * side + paddingUp / 2);

                if (board[i][j]->getId() == 9) {
                    text.setString(std::to_string(board[i][j]->getId()));
                    text.setPosition(j * side + paddingLeft / 2, i * side + paddingUp / 2);
                    rect.setFillColor(sf::Color(255,0,0,255));
                }
                else if (board[i][j]->getId() != 0) {
                    text.setString(std::to_string(board[i][j]->getId()));
                    text.setPosition(j * side + paddingLeft / 2, i * side + paddingUp / 2);
                }

                window.draw(rect);
                window.draw(text);
            }
        }
    }
}
void clearMemory() {
    for (short i = 0; i < he; i++) {
        for (short j = 0; j < wi; j++)
        {
            delete board[i][j];
        }
    }
}
void addBombs(short _bombs) {
    srand(time(NULL));
    for (short i = 0; i < he; i++) {
        for (short j = 0; j < wi; j++)
        {
            board[i][j] = new Character(i, j);
        }
    }
    for (short i = 0; i <= _bombs; i++)
    {
        short x = rand() % 17;
        short y = rand() % 17;

        board[y][x]->setId(9);
    }

    for (short i = 0; i < he; i++) {
        for (short j = 0; j < wi; j++)
        {
            board[i][j]->findBomb(board);
        }
    }
}
void settingSet() {
    bombs = 10 + (level * 10);
    addBombs(bombs);
}
void winCheck() {
    short count = 0;
    for (short i = 0; i < he; i++)
        for (short j = 0; j < wi; j++)
            if (board[i][j]->getFlag() && board[i][j]->getId() == 9)
                count++;

    if (count == bombs) level = 0;
}