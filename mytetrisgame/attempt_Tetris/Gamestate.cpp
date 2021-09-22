#include "Gamestate.h"
#include "Game.h"


  Play::Play(const sf::Vector2f& position, const sf::Vector2u& areaSize,const sf::Vector2f& blockSize)	
  :tetris(position,blockSize)
{
}

void Play::update(Game* target, const float dt)
{	
  tetris.update(target, dt);
}
void Play::handleInput(Game* target)
{	
  tetris.handleInput();
}
void Play::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
  	states.transform *= getTransform();	
    target.draw(tetris);
}
  Play Gamestate::play{ {200.0f,100.0f} };
  MainMenu Gamestate::menu{ {300.0f,200.0f} };
  GameOver Gamestate::gameover{ {300.0f,
200.0f} };
MainMenu::MainMenu(const sf::Vector2f & position)
{
 if(!font.loadFromFile("calibri.ttf")) 
{		
  std::cout << "Failed to loading font file!" << std::endl;	
}
  title.setFont(font);	
  title.setCharacterSize(65);	
  title.setString("TETRIS");	
  title.setOrigin({ title.getGlobalBounds().width/2,title.getGlobalBounds().height/2 });
  title.setPosition(position);	
  prompt.setFont(font);	
  prompt.setString("Press F5 to start!");	
  prompt.setOrigin({ prompt.getGlobalBounds().width/2,prompt.getGlobalBounds().height/2 });	
  prompt.setPosition(position.x, position.y + 100.0f);
}

void music(sf::Music music)
{
    if(!music loadFromFile("tetris.ogg"))
    {
        std::cout << "Failed to loading music file" << std::endl;
    }
    title.setMusic(music);
}

void MainMenu::update(Game* target, const float dt)
{
// Nothing to see here!
}

void MainMenu::handleInput(Game* target)
{
 if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::F5)) 
{		
  std::cout << "Game start requested!" << std::endl;		
  target->setState(&Gamestate::play);	
}

}

void MainMenu::draw(sf::RenderTarget & target, sf::RenderStates states) const
{	
  states.transform *= getTransform();	
  target.draw(title);	
  target.draw(prompt);
}
GameOver::GameOver(const sf::Vector2f & position)
{
 if(!font.loadFromFile("calibri.ttf")) 
{		
std::cout << "Failed to loading font file!" << std::endl;	
}	
  title.setFont(font);	
  title.setCharacterSize(65);	
  title.setString("GAME OVER");	
  title.setOrigin({ title.getGlobalBounds().width / 2,title.getGlobalBounds().height / 2 });	
  title.setPosition(position);	
  prompt.setFont(font);	
  prompt.setString("Press F5 to restart!");	
  prompt.setOrigin({ prompt.getGlobalBounds().width / 2,prompt.getGlobalBounds().height / 2 });	
  prompt.setPosition(position.x, position.y + 100.0f);
}

void music(sf::Music music)
{
    if(!music openFromfile("game-over.mp3"))
    {
        std::cout << "Failed to opening the music file" << std::endl;
    }
    title.setMusic(music);
    
}

void GameOver::update(Game * target, const float dt)
{
}

void GameOver::handleInput(Game * target)
{
 if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::F5)) 
{		
  target->setState(&Gamestate::play);	
}

}

void GameOver::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
  states.transform *= getTransform();	
  target.draw(title);	
  target.draw(prompt);
}

