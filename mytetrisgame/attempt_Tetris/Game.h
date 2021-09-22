#pragma once
#include "Gamestate.h"


class Game : 
public sf::Drawable, public sf::Transformable
{
public:Game(Gamestate* initState);
void update(const float dt);
void handleInput();
void setState(Gamestate* target);

private:
virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;	Gamestate * state;
};

