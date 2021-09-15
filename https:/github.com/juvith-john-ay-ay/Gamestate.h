#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include "Tetrisscr.h"

//#include "Game.h"

class Game;
class Play;
class MainMenu;
class GameOver;

class Gamestate : public sf::Drawable, public sf::Transformable
// An interface for different states of the game f.e. Play, Menu, etc.
{
public:
virtual void update(Game* target, const float dt) = 0;
virtual void handleInput(Game* target) = 0;
static Play play;
static MainMenu menu;
static GameOver gameover;

private:
virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;
};

class Play : public Gamestate
// Play the game!
{
public:
  Play(const sf::Vector2f& position, const sf::Vector2u& areaSize = { 10,20 }, const sf::Vector2f& blockSize = { 32.0f,32.0f });
void update(Game* target, const float dt);
void handleInput(Game* target);

private:
virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;	
  Tetrisscr tetris;
};

class MainMenu : public Gamestate
{
public:
  MainMenu(const sf::Vector2f& position);
void update(Game* target, const float dt);
void handleInput(Game* target);

private:
virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;	
  sf::Text title;	
  sf::Text prompt;	
  sf::Font font;
};

class GameOver : public Gamestate
{
public:
  GameOver(const sf::Vector2f& position);
void update(Game* target, const float dt);
void handleInput(Game* target);

private:
virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;	
  sf::Text title;	
  sf::Text prompt;	
  sf::Font font;
};

