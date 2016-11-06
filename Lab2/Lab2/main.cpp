#include <SFML/Graphics.hpp>
#include <SFML\OpenGL.hpp>

#include "cube.h"

int main(int argc, char *argv)
{
	sf::RenderWindow window(sf::VideoMode(400, 400), "Paul's Lab 2", sf::Style::Titlebar | sf::Style::Close);

	sf::Image sadBronco;
	sadBronco.loadFromFile("res/bronco2.jpg");

	sf::Image background;
	background.loadFromFile("res/lolcat_airplane.jpg");

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
	glDepthFunc(GL_LESS);
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CW);

	GLuint sadBroncoTextureID;
	glGenTextures(1, &sadBroncoTextureID);

	glBindTexture(GL_TEXTURE_2D, sadBroncoTextureID);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, sadBronco.getSize().x, sadBronco.getSize().y, 0, GL_RGBA, GL_UNSIGNED_BYTE,
		sadBronco.getPixelsPtr()
	);

	/* Telling OpenGL that we want our active texture to magnify and minimize in
	* linear fashion. */
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	/* Telling OpenGL how we want to represent our texture when we try to draw past its bounds. */
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	GLuint backgroundTextureID;
	glGenTextures(1, &backgroundTextureID);
	glBindTexture(GL_TEXTURE_2D, backgroundTextureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, background.getSize().x, background.getSize().y, 0, GL_RGBA, GL_UNSIGNED_BYTE,
		background.getPixelsPtr()
	);

	/* Telling OpenGL that we want our active texture to magnify and minimize in
	* linear fashion. */
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	/* Telling OpenGL how we want to represent our texture when we try to draw past its bounds. */
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	float positionZ = 0.5f;
	float angle = 0.0f;
	GLenum currentMode = GL_TRIANGLES;
	int rotateDir = 1; //changes to -1 to reverse x axis rotation
	bool isRotating = false;
	sf::Event sfEvent;
	sf::Clock appTimer;
	Cube cube = Cube(sadBroncoTextureID);
	while (window.isOpen()) {
		float deltaTime = appTimer.restart().asSeconds();
		while (window.pollEvent(sfEvent)) {
			if (sfEvent.type == sf::Event::Closed) {
				window.close();
			}
			if (sfEvent.type == sf::Event::KeyPressed) {
				if (sfEvent.key.code == sf::Keyboard::Num1) {
					currentMode = GL_TRIANGLES;
				}
				else if (sfEvent.key.code == sf::Keyboard::Num2) {
					currentMode = GL_TRIANGLE_FAN;
				}
				else if (sfEvent.key.code == sf::Keyboard::Num3) {
					currentMode = GL_TRIANGLE_STRIP;
				}
				else if (sfEvent.key.code == sf::Keyboard::Num4) {
					currentMode = GL_QUADS;
				}
				else if (sfEvent.key.code == sf::Keyboard::Num5) {
					currentMode = GL_TRIANGLE_FAN;
				}
				else if (sfEvent.key.code == sf::Keyboard::Up) {
					isRotating = true;
				}
				else if (sfEvent.key.code == sf::Keyboard::Down) {
					isRotating = true;
					rotateDir = -1;
				}
			}
			else if (sfEvent.type == sf::Event::KeyReleased) {
				if (sfEvent.key.code == sf::Keyboard::Up || sfEvent.key.code == sf::Keyboard::Down) {
					isRotating = false;
				}
			}
		}

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		GLenum error = glGetError();
		float offset = 1.0f;

		GLfloat position[] = { positionZ, -0.1, positionZ, 0.0f };
		glLightfv(GL_LIGHT0, GL_POSITION, position);

		//draw background
		glBindTexture(GL_TEXTURE_2D, backgroundTextureID);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, background.getSize().x, background.getSize().y, 0, GL_RGBA, GL_UNSIGNED_BYTE,
			background.getPixelsPtr()
		);
		glPushMatrix();
		glBegin(GL_QUADS);

		float leftSide = 0.0f;
		float rightSide = 1.0f;
		float topSide = 0.0f;
		float bottomSide = 1.0f;

		// Cube
		glTexCoord2f(leftSide, bottomSide);
		glNormal3f(0.0f, 0.0f, 1.0f);
		glVertex3f(-offset, -offset, offset);
		glTexCoord2f(leftSide, topSide);
		glNormal3f(0.0f, 0.0f, 1.0f);
		glVertex3f(-offset, offset, offset);
		glTexCoord2f(rightSide, topSide);
		glNormal3f(0.0f, 0.0f, 1.0f);
		glVertex3f(offset, offset, offset);
		glTexCoord2f(rightSide, bottomSide);
		glNormal3f(0.0f, 0.0f, 1.0f);
		glVertex3f(offset, -offset, offset);
		glEnd();

		glPushMatrix();

		//draw cube
		glBindTexture(GL_TEXTURE_2D, sadBroncoTextureID);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, sadBronco.getSize().x, sadBronco.getSize().y, 0, GL_RGBA, GL_UNSIGNED_BYTE,
			sadBronco.getPixelsPtr()
			);
		cube.Update(deltaTime, isRotating, rotateDir);
		cube.Draw(currentMode);

		window.display();
	}

	return 0;
}