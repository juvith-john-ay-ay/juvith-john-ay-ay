#include "Inputstate.h"
#include "Tetrisscr.h"


void Idle::handleInput(Tetrisscr * target) 
{
 if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) 
{		
  target->moveTetromino({ -1,0 });		
  target->setInputstate(PlayInputstate::leftPressed);	
}
 else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) 
{		
  target->moveTetromino({ 1,0 });		
  target->setInputstate(PlayInputstate::rightPressed);	
}
 else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) 
{		
  target->setInputstate(PlayInputstate::downPressed);	
}
 else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)) 
{		
  target->rotateTetromino(RotationDirection::CounterClockwise);		
  target->setInputstate(PlayInputstate::cRotationPressed);	
}
 else if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)) 
{		
  target->rotateTetromino(RotationDirection::Clockwise);		
  target->setInputstate(PlayInputstate::rotationPressed);	
}

}

void PlayInputstate::update(const float dt)
{
}

void LeftPressed::handleInput(Tetrisscr * target)
{
 if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) 
{		
  target->setInputstate(PlayInputstate::idle);	
}

}

void RightPressed::handleInput(Tetrisscr * target)
{
 if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) 
{		
  target->setInputstate(PlayInputstate::idle);	
}

}

void DownPressed::handleInput(Tetrisscr * target)
{
 if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) 
{		
  isPressed = false;	
}

 if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && !isPressed && !doubleTapped) 
{		
  target->dropTetromino();		
  doubleTapped = true;	
}
 if((!sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || doubleTapped) && updateTimer >= updateDelay) 
{
// Reset all values and return the state to idle		
  updateTimer = 1.0f;		
  isPressed = true;		
  doubleTapped = false;		
  target->setInputstate(PlayInputstate::idle);	
}

}

void DownPressed::update(const float dt)
{
  	updateTimer += dt;
}

void RotationPressed::handleInput(Tetrisscr * target)
{
//target->rotateTetromino(RotationDirection::Clockwise);
 if(!sf::Keyboard::isKeyPressed(sf::Keyboard::A)) 
{		
  target->setInputstate(PlayInputstate::idle);	
}

}

void CRotationPressed::handleInput(Tetrisscr * target)
{
//target->rotateTetromino(RotationDirection::CounterClockwise);
 if(!sf::Keyboard::isKeyPressed(sf::Keyboard::D)) 
{		
  target->setInputstate(PlayInputstate::idle);	
}

}
 Idle PlayInputstate::idle;
 LeftPressed PlayInputstate::leftPressed;
 RightPressed PlayInputstate::rightPressed;
 DownPressed PlayInputstate::downPressed;
 RotationPressed PlayInputstate::rotationPressed;
 CRotationPressed PlayInputstate::cRotationPressed;

