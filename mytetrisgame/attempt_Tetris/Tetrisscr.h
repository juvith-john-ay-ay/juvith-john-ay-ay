#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <random>
#include "Block.h"
#include "Tetromino.h"
#include "Inputstate.h"


class Game;

class Tetrisscr : public sf::Drawable, public sf::Transformable
// Handles the tetrominos and the whole play area
{
public:
  Tetrisscr(const sf::Vector2f& position, const sf::Vector2f& blockSize = { 32.0f,32.0f });
void update(Game* target, const float dt);
void handleInput();
void setInputstate(PlayInputstate& state);
void moveTetromino(const sf::Vector2i& dir);
void dropTetromino();
void rotateTetromino(const RotationDirection direction);

private:
virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
void clearScreen();
void scanLines();
void sfx(sf::SoundBuffer buffer);
void destroyLine(const unsigned y);
void advanceTimer(const float dt);
void resetTimer();
void skipStep();
void drawTetromino();
void newTetromino();
void plantTetromino();
void reset();

bool canMove(const sf::Vector2i& dir);
bool canRotate(const RotationDirection direction);
bool isGameOver();

private:
static constexpr unsigned width{ 10 };
static constexpr unsigned height{ 20 };
static constexpr unsigned borderWidth{ 4 };
static constexpr unsigned borderHeight{ 4 };
static constexpr float updateDelay{ 30.0f };

const sf::Vector2i spawnPosition{ 4,-2 };
const sf::Color boardColor{ sf::Color::Black };
const sf::Color backgroundColor{ sf::Color::Red };
float updateTimer{ 1.0f };	
  sf::RectangleShape background;	
  Block gameBoard[height][width];	
  Tetromino* curTetromino;	
  PlayInputstate* inputState{ &PlayInputstate::idle };	
  std::random_device rd;	
  std::mt19937 rng{ rd() };	
  std::uniform_int_distribution<int> uni{ 2, 6 };
};

