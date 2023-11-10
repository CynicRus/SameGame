#include <iostream>
#include <string>
#include <cmath>
#include "Game.hpp"

#define xGridSize 16
#define yGridSize 10


Game::Game() : _window(sf::VideoMode(800, 600), "Same Game")
{
	map = new Field(xGridSize, yGridSize);
	srand(time(NULL));
	CurrCell.x = -1; CurrCell.y = -1;
	CurrSel.x = -1; CurrCell.y = -1;

	/*Menu*/
	//this->title = new sf::Text("Invaded", *this->font, 256U);
	//this->title->setOrigin(this->title->getGlobalBounds().width / 2, this->title->getGlobalBounds().height / 2);
	//this->title->setPosition(window->getSize().x / 2, window->getSize().y / 8);

	b1.loadFromFile("resources/b1.png");
	b2.loadFromFile("resources/b2.png");
	b3.loadFromFile("resources/b3.png");
	b4.loadFromFile("resources/b4.png");
	b5.loadFromFile("resources/b5.png");
	b6.loadFromFile("resources/b6.png");

	_shader.loadFromFile("resources/shaders/background.frag", sf::Shader::Fragment);
	_ballShader.loadFromFile("resources/shaders/ballShader1.frag", sf::Shader::Fragment);
	_ballShader.setUniform("size", sf::Vector2f(48, 48));

	_states.shader = &_shader;
	_balls.shader = &_ballShader;

	//ballShader.setUniform("frag_LightAttenuation",10.f);


	_testShape.setSize(sf::Vector2f(800, 600));
	_renderTexture.create(800, 600);

	_font.loadFromFile("resources/XpressiveBlack Regular.ttf");

	_title.setFont(_font);
	_title.setCharacterSize(256);
	_title.setOrigin(_title.getGlobalBounds().width / 2, _title.getGlobalBounds().height / 2);
	_title.setPosition(_window.getSize().x / 5, 0);
	_title.setString("Same");

	_scoreText.setFont(_font);
	_endGameText.setFont(_font);


	sf::Sprite tempBall(b1);
	map->buildCells(0, 90, tempBall.getGlobalBounds());

}

Game::~Game() {
	delete[] map;
}

void Game::increaseScore(int32_t count, int32_t color) {
	int32_t points = 0;
	switch (color)
	{
	case 1:
		points += 2;
		break;
	case 2:
		points += 3;
		break;
	case 3:
		points += 5;
		break;
	case 4:
		points += 4;
		break;
	case 5:
		points += 2;
		break;
	case 6:
		points += 1;
		break;
	default:
		points += 0;
		break;
	}
	score += points * count;
}

void Game::resetSelection() {
	for (size_t i = 0; i <= xGridSize - 1; i++) {
		for (size_t j = 0; j <= yGridSize - 1; j++) {
			map->setSelection(i, j, false);
		}
	}
}

void Game::processEvents()
{
	sf::Event event;

	sf::Clock clock;
	while (_window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			_window.close();

		if (event.type == sf::Event::MouseButtonPressed) {
			sf::Vector2f mouse = _window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));

			if (event.mouseButton.button == sf::Mouse::Left) {
				int32_t mx = mouse.x - 16 - map->getOffsetX();
				int32_t my = mouse.y - 16 - map->getOffsetY();
				int32_t col = static_cast<int32_t>(std::ceil(mx / 48));
				int32_t row = static_cast<int32_t>(std::ceil(my / 48));
				if ((col <= xGridSize - 1) && (row <= yGridSize - 1)) {
					CurrCell.x = col;
					CurrCell.y = row;
				}
			}
		}

		if (event.type == sf::Event::MouseMoved) {
			sf::Vector2f mouse = _window.mapPixelToCoords(sf::Vector2i(event.mouseMove.x, event.mouseMove.y));
			int32_t ox = map->getOffsetX();
			int32_t oy = map->getOffsetY();

			int32_t mx = mouse.x - ox;
			int32_t my = mouse.y - oy;
			int32_t col = static_cast<int32_t>(std::ceil(mx / 48));
			int32_t row = static_cast<int32_t>(std::ceil(my / 48));
			if ((mx > 16 + ox) && (my > 16 + ox)) {
				if ((col > -1 && col <= xGridSize - 1) && ((row > -1) && row <= yGridSize - 1)) {

					if ((col <= xGridSize - 1) && (row <= yGridSize - 1) && (col > -1) && (row > -1)) {
						CurrSel.x = col;
						CurrSel.y = row;
					}
				}
			}
			else
			{
				CurrSel.x = -1;
				CurrSel.y = -1;
				resetSelection();

			}




		}

	}

}

void Game::update(sf::Time deltaTime) {
	_shader.setUniform("resolution", sf::Vector2f(1920.f, 1080.f));
	//float time = / 70000;
	//std::cout << "time: " << time << std::endl;
	_shader.setUniform("time", deltaTime.asSeconds());
	_ballShader.setUniform("time", deltaTime.asSeconds());

	_window.clear();
	_renderTexture.clear();
	_renderTexture.draw(_testShape, &_shader);
	_renderTexture.display();
	_texture = _renderTexture.getTexture();
	sf::Sprite back;
	back.setTexture(_texture);
	_window.draw(back);
	//window.draw(title);
	if ((CurrSel.x > -1) && (CurrSel.y > -1) && (selColor != map->getColor(CurrSel.x, CurrSel.y)))
	{
		resetSelection();
	}

	/*Try to play*/
	if (CurrCell.x > -1) {
		uint32_t count = map->countCellNeighbours(CurrCell.x, CurrCell.y);
		if (count > 0)
		{
			uint32_t c = map->getColor(CurrCell.x, CurrCell.y);
			uint32_t ballCount = map->removeCells(CurrCell.x, CurrCell.y, c);
			increaseScore(ballCount, c);
			CurrSel.x = -1; CurrSel.y = -1;
			CurrCell.x = -1; CurrCell.y = -1;
		}
	}
	if (!gameOver)
	gameOver = map->updateCells();

}

void Game::render() {

	/*draw balls*/
	for (int i = 0; i < xGridSize; i++) {
		for (int j = 0; j < yGridSize; j++) {
			sf::Sprite ball;
			switch (map->getColor(i, j)) {
			case 1:
				ball = sf::Sprite(b1);
				break;
			case 2:
				ball = sf::Sprite(b2);
				break;
			case 3:
				ball = sf::Sprite(b3);
				break;
			case 4:
				ball = sf::Sprite(b4);
				break;
			case 5:
				ball = sf::Sprite(b5);
				break;
			case 6:
				ball = sf::Sprite(b6);
				break;
			default:
				break;
			}
			ball.setPosition(map->getCell(i, j).getXPos() + 16/*sprite width /2*/, map->getCell(i, j).getYPos() + 16/*height / 2*/);

			if ((CurrSel.x == i) && (CurrSel.y == j)) {
				if (map->countCellNeighbours(i, j) > 0) {
					selColor = map->getColor(i, j);
					int32_t sel = map->selectCells(i, j, selColor);
				}
			}
			//ballShader.setUniform("frag_LightOrigin",sf::Vector2f(ball.getPosition().x/2,ball.getPosition().y/2));
			//ballShader.setUniform("color", sf::Vector3f(255,255,255));
			if (map->getCell(i, j).getSelection()) {
				_window.draw(ball, _balls);
			}
			else {
				_window.draw(ball);
			}
		}
	}

	_scoreText.setString("Score: " + std::to_string(score));
	_scoreText.setCharacterSize(48);
	_scoreText.setPosition(16, 10);
	_window.draw(_scoreText);
	if (gameOver) {
		_endGameText.setString("Game Over!");
		_endGameText.setFillColor(sf::Color(115, 13, 115));
		_endGameText.setCharacterSize(64);
		_endGameText.setPosition(220, 200);
		_window.draw(_endGameText);
	}

	_window.display();

}

void Game::run(int minimum_frame_per_seconds)
{
	sf::Clock clock;
	while (_window.isOpen())
	{
		processEvents();
		update(clock.getElapsedTime());
		render();
	}
}

