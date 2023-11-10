#pragma once
#include <cstdint>
class Cell
{
private:
	int32_t _x, _y = 0;
	int32_t _color = 0 ;
	bool _selected = false;
public:
	Cell() {};
	Cell(int32_t x, int32_t y, int32_t color);
	~Cell();

	int32_t getColor() const;
	void setColor(int32_t color);
	int32_t getXPos() const;
	int32_t getYPos() const;

	void setSelection(bool selection); //< set the rotation
    bool getSelection() const;

};

