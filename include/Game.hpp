#pragma once
#include <SFML/Graphics.hpp>
#include "Cell.hpp"
#include "Field.hpp"

struct Point {
	int32_t x, y = -1;
};

enum GameState
{
	GAME_STATE_NONE,
	GAME_STATE_PLAYING,
	GAME_STATE_MENU,
	GAME_STATE_PAUSED,
	GAME_STATE_GAMEOVER
};

enum GameType {
	GAME_TYPE_LEGACY,
	GAME_TYPE_INFINITY
};

class Game
{
private:
	sf::RenderWindow _window;
	sf::Shader _shader, _ballShader;
	sf::RectangleShape _testShape;
	sf::RenderTexture _renderTexture;
	sf::Texture _texture;
	sf::Font _font;
	sf::Text _scoreText, _endGameText, _title;
	sf::RenderStates _states, _balls;
	sf::Texture a1, b1, b2, b3, b4, b5, b6;
	Field* map;
	GameState state = GAME_STATE_NONE;
	GameType _gameType = GAME_TYPE_LEGACY;


	Point CurrCell;
	Point CurrSel;
	Point Offset;
	int32_t score = 0;
	int32_t selColor = -1;
	bool clickb = false;
	bool gameOver = false;
	void increaseScore(int32_t count, int32_t color);
	void resetSelection();

public:
	Game();
	~Game();

	Game(const Game&) = delete;
	Game& operator=(const Game&) = delete;
	void run(int minimum_frame_per_seconds);
	void processEvents();
	void update(sf::Time deltaTime); 
	void render();
};

