#pragma once
#include <SFML/Graphics.hpp>
#include "Enum.h"


class Tetrisscr;
class Idle;
class LeftPressed;
class RightPressed;
class DownPressed;
class RotationPressed;
class CRotationPressed;

class PlayInputstate
{
public:
virtual void handleInput(Tetrisscr* target) = 0;
virtual void update(const float dt);
static Idle idle;
static LeftPressed leftPressed;
static RightPressed rightPressed;
static DownPressed downPressed;
static RotationPressed rotationPressed;
static CRotationPressed cRotationPressed;

private:
};

class Idle : public PlayInputstate
{
public:
virtual void handleInput(Tetrisscr* target);
};

class LeftPressed : public PlayInputstate
{
public:
virtual void handleInput(Tetrisscr* target);

private:
};

class RightPressed : public PlayInputstate
{
public:
virtual void handleInput(Tetrisscr* target);

private:
};

class RotationPressed : public PlayInputstate
{
public:
virtual void handleInput(Tetrisscr* target);

private:
};

class CRotationPressed : public PlayInputstate
{
public:
virtual void handleInput(Tetrisscr* target);

private:
};
class DownPressed : public PlayInputstate
{
public:
virtual void handleInput(Tetrisscr* target);
virtual void update(const float dt);

private:
bool isPressed{ true };
bool doubleTapped{ false };
static constexpr float updateDelay{ 15.0f };
float updateTimer{ 1.0f };
};

