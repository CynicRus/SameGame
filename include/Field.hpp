#pragma once
#include <SFML/Graphics.hpp>
#include <cstdint>
#include <cmath>
#include "Cell.hpp"

template <typename T, typename ...As>
inline void freeCell(T &ojt) {
    ojt.~T();
}

class Field
{
private:
	Cell** Cells;
	int32_t _xGridSize;
	int32_t _yGridSize;
	int32_t _offsetX, _offsetY;
public:
	Field(int32_t xGridSize, int32_t yGridSize);
	~Field();
	void buildCells(int32_t offsetX, int32_t offsetY, sf::FloatRect bounds);
	int32_t countCellNeighbours(int32_t x, int32_t y);
	int32_t removeCells(int32_t x, int32_t y, int32_t color);
	bool noAvailableSteps();
	int32_t selectCells(int32_t x, int32_t y, int32_t color);
	bool updateCells();
	int32_t getColor(int32_t x, int32_t y) const;
	void setColor(int32_t x, int32_t y, int32_t color);
	Cell getCell(int32_t x, int32_t y) const;
	void setSelection(int32_t x, int32_t y, bool selection);

	int32_t getXSize() const;
	int32_t getYSize() const;
	int32_t getOffsetX() const;
	int32_t getOffsetY() const;
};

