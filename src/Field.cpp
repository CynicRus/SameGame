#include "Field.hpp"

Field::Field(int32_t xGridSize, int32_t yGridSize) {
	_xGridSize = xGridSize;
	_yGridSize = yGridSize;
	Cells = new Cell * [xGridSize];
}
Field::~Field()
{
	for (int i = 0; i < _xGridSize; i++)
	{
		for (int32_t j = 0; j < _yGridSize; j++)
		{
			freeCell(Cells[i][j]);
		}
	}
	delete[] Cells;
	Cells = NULL;
}

int32_t Field::getXSize() const {
	return _xGridSize;
}
int32_t Field::getYSize() const {
	return _yGridSize;
}
int32_t Field::getOffsetX() const {
	return _offsetX;
}
int32_t Field::getOffsetY() const {
	return _offsetY;
}

Cell Field::getCell(int32_t x, int32_t y) const {
	return Cells[x][y];
}

void Field::setSelection(int32_t x, int32_t y, bool selection) {
	Cells[x][y].setSelection(selection);
}

void Field::setColor(int32_t x, int32_t y, int32_t color) {
	Cells[x][y].setColor(color);
}

void Field::buildCells(int32_t offsetX, int32_t offsetY, sf::FloatRect bounds) {
	_offsetX = offsetX;
	_offsetY = offsetY;
	for (int32_t i = 0; i <= _xGridSize - 1; i++)
	{
		Cells[i] = new Cell[_yGridSize];
		for (int32_t j = 0; j <= _yGridSize - 1; j++)
		{
			int32_t random = 1 + rand() % 6;
			Cell _Cell = Cell{ offsetX + i * static_cast<int32_t>(std::trunc(bounds.width)), offsetY + j * static_cast<int32_t>(std::trunc(bounds.height)), random };
			Cells[i][j] = _Cell;
		}
	}


}


int32_t Field::countCellNeighbours(int32_t x, int32_t y) {

	int32_t color = Cells[x][y].getColor();
	int32_t count = 0;

	if (color > 0)
	{

		if ((x > 0) && (Cells[x - 1][y].getColor() == color))
			count++;
		if ((x < _xGridSize - 1) && (Cells[x + 1][y].getColor() == color))
			count++;
		if ((y > 0) && (Cells[x][y - 1].getColor() == color))
			count++;
		if ((y < _yGridSize - 1) && (Cells[x][y + 1].getColor() == color))
			count++;

		return count;

	}

	return 0;
}

int32_t Field::removeCells(int32_t x, int32_t y, int32_t color) {
	if (Cells[x][y].getColor() == color)
	{
		Cells[x][y].setSelection(false);
		int32_t count = 1;
		Cells[x][y].setColor(0);
		if (x > 0)
			count += removeCells(x - 1, y, color);
		if (x < _xGridSize - 1)
			count += removeCells(x + 1, y, color);
		if (y > 0)
			count += removeCells(x, y - 1, color);
		if (y < _yGridSize - 1)
			count += removeCells(x, y + 1, color);
		return count;
	}

	return 0;
}
bool Field::noAvailableSteps() {

	for (int32_t col = 0; col < _xGridSize; col++)
	{
		for (int32_t row = _yGridSize - 1; row >= 0; row--)
		{
			int32_t nColor = Cells[col][row].getColor();
			if (nColor == 0)
				break;
			else
			{
				if (row - 1 >= 0 &&
					Cells[col][row - 1].getColor() == nColor)
					return false;
				else if (col + 1 < _xGridSize &&
					Cells [col + 1][row].getColor() == nColor)
					return false;
			}
		}
	}

	return true;

}

int32_t Field::getColor(int32_t x, int32_t y) const {
	return Cells[x][y].getColor();
}


int32_t Field::selectCells(int32_t x, int32_t y, int32_t color) {
	if ((Cells[x][y].getColor() == color) && (!Cells[x][y].getSelection()))
	{
		Cells[x][y].setSelection(true);

		int32_t count = 1;

		if ((x > 0) && (!Cells[x - 1][y].getSelection()))
			count += selectCells(x - 1, y, color);
		if ((x < _xGridSize - 1) && (!Cells[x + 1][y].getSelection()))
			count += selectCells(x + 1, y, color);
		if ((y > 0) && (!Cells[x][y - 1].getSelection()))
			count += selectCells(x, y - 1, color);
		if ((y < _yGridSize - 1) && (!Cells[x][y + 1].getSelection()))
			count += selectCells(x, y + 1, color);
		return count;
	}

	return 0;
}
bool Field::updateCells() {
	int32_t m = 0;
	//top-down
	for (int row = 0; row < _xGridSize; row++)
	{
		int32_t emptyRowIndex = _yGridSize - 1;
		int32_t nextOccupiedRowIndex = emptyRowIndex;
		while (nextOccupiedRowIndex >= 0 && emptyRowIndex >= 0)
		{
			while (emptyRowIndex >= 0 &&
				Cells[row][emptyRowIndex].getColor() != 0)
				emptyRowIndex--;
			if (emptyRowIndex >= 0)
			{
				nextOccupiedRowIndex = emptyRowIndex - 1;
				while (nextOccupiedRowIndex >= 0 &&
					Cells[row][nextOccupiedRowIndex].getColor() == 0)
					nextOccupiedRowIndex--;
				if (nextOccupiedRowIndex >= 0)
				{
					Cells[row][emptyRowIndex].setColor(Cells[row][nextOccupiedRowIndex].getColor());
					Cells[row][nextOccupiedRowIndex].setColor(0);
				}
			}
		}
	}

	for (int col = 0; col < _yGridSize; col++)
	{
		int emptyColIndex = 0;
		int nextOccupiedColIndex = emptyColIndex;
		while (nextOccupiedColIndex <= _xGridSize - 1 && emptyColIndex <= _xGridSize - 1)
		{
			while (emptyColIndex <= _xGridSize - 1 &&
				Cells[emptyColIndex][col].getColor() != 0)
				emptyColIndex++;
			if (emptyColIndex <= _xGridSize - 1)
			{
				nextOccupiedColIndex = emptyColIndex + 1;
				while (nextOccupiedColIndex <= _xGridSize - 1 &&
					Cells[nextOccupiedColIndex][col].getColor() == 0)
					nextOccupiedColIndex++;
				if (nextOccupiedColIndex <= _xGridSize - 1)
				{
					Cells[emptyColIndex][col].setColor(Cells[nextOccupiedColIndex][col].getColor());
					Cells[nextOccupiedColIndex][col].setColor(0);
				}
			}
		}

	}
	return noAvailableSteps();
}
