#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;


int width = 50;
int height = 50;
int cell = 500;
int board[50][50];
int boardCalc[50][50];

bool pause = true;



void initializeBoard()
{
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			board[i][j] = 0;
			boardCalc[i][j] = 0;
		}
	}
}

void rules()
{
	int neighbour = 0;

	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			
			neighbour = board[(i - 1) % width][(j - 1) % height] +
				board[i % width][(j - 1) % height] +
				board[(i + 1) % width][(j - 1) % height] +
				board[(i - 1) % width][j % height] +
				board[(i + 1) % width][j % height] +
				board[(i - 1) % width][(j - 1) % height] +
				board[i % width][(j - 1) % height] +
				board[(i + 1) % width][(j - 1) % height];

			if (board[i][j] == 0 && neighbour == 3) {
				boardCalc[i][j] = 1;
			}
			else if (board[i][j] == 1) {
				if (neighbour == 2 || neighbour == 3) {
					boardCalc[i][j] = 1;
				}
				else {
					boardCalc[i][j] = 0;
				}
			}
			else {
				boardCalc[i][j] = board[i][j];
			}
		}
	}

	for (int i = 1; i < width - 1; i++) {
		for (int j = 1; j < height - 1; j++) {
			board[i][j] = boardCalc[i][j];
		}
	}
}


int main()
{

	Clock clock;
	float timer = 0;
	float delay = 100;

	srand(time(0));

	RenderWindow app(VideoMode(width*10, height*10), "Game of Life");

	Texture texture;
	texture.loadFromFile("images/black.jpg");
	Sprite sprite(texture);

	initializeBoard();


	while (app.isOpen()) {

		Vector2i pos = Mouse::getPosition(app);
		int x = pos.x / 10;
		int y = pos.y / 10;

		float time = clock.getElapsedTime().asMilliseconds();
		clock.restart();
		timer += time;

		Event e;

		while (app.pollEvent(e)) {
			if (e.type == Event::Closed) {
				app.close();
			}

			if (e.type == Event::KeyPressed) {
				if (e.key.code == Keyboard::P) {
					pause = !pause;
				}
			}

			if (pause && e.type == Event::MouseButtonPressed) {
				if (e.key.code == Mouse::Left) {
					board[x][y] = 1;
				}
				if (e.key.code == Mouse::Right) {
					board[x][y] = 0;
				}
			}
		}

		if (timer > delay) {
			timer = 0;

			if (!pause) {
				rules();
			}
		}

		// Draw
		app.clear(Color::White);

		for (int i = 0; i < width; i++) {
			for (int j = 0; j < height; j++) {

				if (board[i][j] == 1) {
					sprite.setTextureRect(IntRect(0, 0, 9, 9));
					sprite.setPosition(i*10, j*10);
					app.draw(sprite);
				}
			}
		}

		app.display();
	}

	return 0;
}
