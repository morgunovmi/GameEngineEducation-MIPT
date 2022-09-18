#pragma once

#include "Input.h"

struct ControlConfig {
	Keyboard::Key moveLeft = Keyboard::A;
	Keyboard::Key moveRight = Keyboard::D;
	Keyboard::Key moveForward = Keyboard::W;
	Keyboard::Key moveBack = Keyboard::S;
	Keyboard::Key moveDown = Keyboard::LControl;
	Keyboard::Key moveUp = Keyboard::Space;
};