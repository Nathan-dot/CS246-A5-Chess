#include "player.h"
#include "board.h"

Player::Player(Board* board, Colour colour) : board{board}, colour{colour} {}

Player::~Player() {};
