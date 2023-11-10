#include "Cell.hpp"

Cell::Cell(int32_t x, int32_t y, int32_t color) {
	_x = x;
	_y = y;
	_color = color;
	_selected = false;
}
Cell::~Cell() {};

int32_t Cell::getColor() const {
	return _color;
}
void Cell::setColor(int32_t color) {
	_color = color;
}
int32_t Cell::getXPos() const {
	return _x;
}
int32_t Cell::getYPos() const {
	return _y;
}

void Cell::setSelection(bool selection) {
	_selected = selection;
}
bool Cell::getSelection() const {
	return _selected;
}

