#include "Tetrisscr.h"
#include "Game.h"
#include <iostream>
#include <thread>


Tetrisscr::Tetrisscr(const sf::Vector2f & position,const sf::Vector2f& blockSize) 

{
// Initialize the backround	
  background.setFillColor(backgroundColor);	
  background.setSize({ (blockSize.x + borderWidth)*(width)+borderWidth,(blockSize.y + borderHeight)*(height)+borderHeight });	
  background.setPosition({ position.x - borderWidth, position.y - borderHeight });
// Initialize the gameBoard
 for(unsigned iY = 0; iY < height; ++iY) 
{
  for(unsigned iX = 0; iX < width; ++iX) 
 {
  gameBoard[iY][iX] = (Block({ position.x + (blockSize.x + borderWidth)*iX,	position.y + (blockSize.y + borderHeight)*iY },blockSize));		
 }	

}
// Set initial tetromino	
  curTetromino = &Tetromino::iTetromino;	
  curTetromino->setPosition(spawnPosition);	
  curTetromino->setAngle(Angle::North);
}

void Tetrisscr::update(Game* target, const float dt)
{
// Check for gameover
if(isGameOver()) 
{
  reset();		
  target->setState(&Gamestate::gameover);	
}
// Update the inputState	
  inputState->update(dt);
// Delay update until timer is set
while(updateTimer >= updateDelay) 
{	
  	updateTimer -= updateDelay;
// Move the currentTetromino down by one
if(canMove({ 0,1 })) 
{
  moveTetromino({ 0,1 });	
}
else 
 {
  plantTetromino();
  newTetromino();		
 }	

}
// Update every block one by one
 for(auto& row : gameBoard) 
{
  for(auto& block : row) 
 {			
  block.update(dt);		
 }	

}
// Scan lines
  scanLines();
// Update the timer
  advanceTimer(dt);
}

void Tetrisscr::handleInput()
{
  	inputState->handleInput(this);
}

void Tetrisscr::setInputstate(PlayInputstate & state)
{	
  inputState = &state;
}

void Tetrisscr::advanceTimer(const float dt)
{	
  updateTimer += dt;
}

void Tetrisscr::resetTimer()
{
  	updateTimer = 1.0f;
}

void Tetrisscr::skipStep()
{	
  updateTimer = updateDelay;
}

void Tetrisscr::drawTetromino()
// Draw the currentTetromino in the correct position (and ignore out of bounds pixels)
{
const std::vector<std::vector<bool>> shape{ curTetromino->getShape(curTetromino->getAngle()) };
 for(int iY = 0; iY < 4; ++iY) 
{
  for(int iX = 0; iX < 4; ++iX) 
{
bool isOutX{ iX + curTetromino->getPosition().x < 0 || iX + curTetromino->getPosition().x >= width };
bool isOutY{ iY + curTetromino->getPosition().y < 0 || iY + curTetromino->getPosition().y >= height };
 if(!isOutX && !isOutY) 
{				
  Block& target{ gameBoard[curTetromino->getPosition().y + iY][curTetromino->getPosition().x + iX] };
 if(shape[iY][iX]) 
{					
  target.setColor(curTetromino->getColor());				
}
 else if(!target.isPlanted())
    {					
  target.setColor(boardColor);			
}			

}		

}

}

}

void Tetrisscr::newTetromino()
{	
  curTetromino->setPosition(spawnPosition);
const int nextTetromino = uni(rng);
 switch(nextTetromino)	
 {
 case 0:		
  curTetromino = &Tetromino::oTetromino;
 break;
 case 1:		
  curTetromino = &Tetromino::iTetromino;
 break;
 case 2:		
  curTetromino = &Tetromino::sTetromino;
 break;
 case 3:		
  curTetromino = &Tetromino::zTetromino;
 break;
 case 4:		
  curTetromino = &Tetromino::jTetromino;
 break;
 case 5:		
  curTetromino = &Tetromino::lTetromino;
 break;
 case 6:		
  curTetromino = &Tetromino::tTetromino;
 break;	
 }	
  curTetromino->setAngle(Angle::North);
  clearScreen();
  drawTetromino();
}

void Tetrisscr::plantTetromino()
// Marks the tetromino as fallen, static, you know?
{
 for(int iY = 0; iY < 4; ++iY) 
{
  for(int iX = 0; iX < 4; ++iX) 
{
 if(curTetromino->getShape(curTetromino->getAngle())[iY][iX]) 
{
const int blockX{ curTetromino->getPosition().x + iX };
const int blockY{ curTetromino->getPosition().y + iY };				
  gameBoard[blockY][blockX].plant();			
}	
	
}
	
}

}

void Tetrisscr::reset()
{
 for(int iY = 0; iY < height; ++iY) 
{
  for(int iX = 0; iX < width; ++iX) 
 {			
  gameBoard[iY][iX].unplant();			
  gameBoard[iY][iX].setColor(backgroundColor);	
 }

}
  newTetromino();
}

void Tetrisscr::rotateTetromino(const RotationDirection direction)
{
 if(!canRotate(direction)) 
 return;	
  curTetromino->rotate(direction);
  clearScreen();
  drawTetromino();
}

void Tetrisscr::moveTetromino(const sf::Vector2i & dir)
// Checks if tetromino can move and then does so if allowed
{
 if(canMove(dir)) 
 {		
  curTetromino->move(dir);
  clearScreen();
  drawTetromino();	
 }

}

void Tetrisscr::dropTetromino()
// Makes the tetromino fall straight down instantaniously
{
 for(int i = 0; i < height; ++i) 
{
 if(canMove({ 0,1 })) 
{
  moveTetromino({ 0,1 });		
}
 else 
{
  plantTetromino();
  newTetromino();
  resetTimer();
 break;		
}

}

}

bool Tetrisscr::canMove(const sf::Vector2i & dir)
{
 for(int iY = 0; iY < 4; ++iY) 
{
  for(int iX = 0; iX < 4; ++iX) 
{
bool isOutX{ iX + curTetromino->getPosition().x < 0 ||						iX + curTetromino->getPosition().x >= width };
bool isOutY{ iY + curTetromino->getPosition().y < 0 ||						iY + curTetromino->getPosition().y >= height };
// If the checked block is already out of bounds, don't bother to check
 if(isOutX || isOutY) 
 continue;
bool isBlock{ curTetromino->getShape(curTetromino->getAngle())[iY][iX] == true };
int targetX{ curTetromino->getPosition().x + iX + dir.x };
int targetY{ curTetromino->getPosition().y + iY + dir.y };
// If at the checked coordinate there is a piece of currentTetromino, check collision
 if(!isBlock) 
 continue;
// If we are trying to go out of bounds, return false
if(targetX < 0 || targetX >= width || targetY >= height) 
{
 return false;			
}
// If there is already a block, return false
 else if(gameBoard[targetY][targetX].isPlanted()) 
{
 return false;			
}		

}

}
// Otherwise we're good to go
 return true;
}
bool Tetrisscr::canRotate(const RotationDirection direction)
{
  Angle potentialAngle = curTetromino->getAngle();
 switch(direction)	
{
 case RotationDirection::Clockwise:		
  potentialAngle = static_cast<Angle>(curTetromino->getAngle() + 1 > 3 ? 0 : curTetromino->getAngle() + 1);
 break;
 case RotationDirection::CounterClockwise:		
  potentialAngle = static_cast<Angle>(curTetromino->getAngle() - 1 < 0 ? 3 : curTetromino->getAngle() - 1);
 break;	
}
 for(int iY = 0; iY < 4; ++iY) 
{
  for(int iX = 0; iX < 4; ++iX) 
{
bool isOutX{ iX + curTetromino->getPosition().x < 0 ||				iX + curTetromino->getPosition().x >= width };
bool isOutY{ iY + curTetromino->getPosition().y < 0 ||				iY + curTetromino->getPosition().y >= height };
// If the checked block is already out of bounds, don't bother to check
bool isBlock{ curTetromino->getShape(potentialAngle)[iY][iX] == true };
int targetX{ curTetromino->getPosition().x + iX };
int targetY{ curTetromino->getPosition().y + iY };
// If at the checked coordinate there is a piece of currentTetromino, check collision
 if(!isBlock) 
 continue;
// If we are trying to rotate out of bounds, move the tetromino away
 while(targetX < 0) 
{
  moveTetromino({ 1,0 });				
    ++targetX;			
}
 while(targetX >= width) 
{
  moveTetromino({ -1,0 });			
  	--targetX;			
}
 if(targetX < 0 || targetX >= width ||	targetY >= height) 
{
 return false;			
}
// If there is already a block, return false
 else if(gameBoard[targetY][targetX].isPlanted()) 
{
 return false;			
}		

}

}
 return true;
}

bool Tetrisscr::isGameOver()
{
 if(curTetromino->getPosition().y < -1) 
{
 if(!canMove({ 0,1 })) 
{
 return true;		
}

}
 return false;
}

void Tetrisscr::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
  states.transform *= getTransform();
// Draw backround	
  target.draw(background);
// Draw every block one by one
 for(const auto& row : gameBoard) 
{
  for(const auto& block : row) 
{			
  target.draw(block);		
}	

}

}

void Tetrisscr::clearScreen()
// Clears the gameBoard from previous frame junk
{
 for(unsigned iY = 0; iY < height; ++iY) 
{
  for(unsigned iX = 0; iX < width; ++iX) 
{
 if(!gameBoard[iY][iX].isPlanted()) 
{				
  gameBoard[iY][iX].setColor(boardColor);			

}		

}

}

}

void Tetrisscr::scanLines()
{
 for(unsigned iY = 0; iY < height; ++iY) 
{
  for(unsigned iX = 0; iX < width; ++iX) 
{
// If one of the blocks is empty, ignore the rest of the line and continue to the next
 if(!gameBoard[iY][iX].isPlanted()) 
{
 break;			
}
// Otherwise if every block in current y-coordinate is planted, we destroy the line
else if(iX == width-1) 
{				
  std::cout << "LINES CLEARED " << std::endl;
  destroyLine(iY);
break;			
}		

}

}

}

void Tetrisscr::sfx(sf::SoundBuffer buffer)
{
  if(!buffer.loadFromFile("clear.wav"))
  {
    std::cout << "Failed to load sfx file" << std::endl;
  }
}

void Tetrisscr::destroyLine(const unsigned y)
{
 for(int iX = 0; iX < width; ++iX) 
{
// Go from down to up and pull every block down by one
  for(int iY = y; iY > 1; --iY) 
{
// Copy the attributes from block above the target block
 auto& target{ gameBoard[iY][iX] };			
  target.setColor(gameBoard[iY - 1][iX].getColor());
 if(!gameBoard[iY - 1][iX].isPlanted()) 
{				
  target.unplant();			
}
 else 
{				
  target.plant();			
}		

}

}

}

