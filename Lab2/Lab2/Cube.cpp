#include "Cube.h"

Cube::Cube(GLuint textureID) : _horizontalAngle(0), _verticalAngle(0), _textureID(textureID), isRotating(false), rotateDir(1), scrollDir(1.0f)
{
	_textureOffset = 0.0f;
}


void Cube::Update(float dt, bool isRotating, int rotateDir)
{
	_horizontalAngle += 30.0f * dt;
	_textureOffset += 0.1f * dt*scrollDir;
	if (_textureOffset > 0.6f || _textureOffset <= 0.0f){
		scrollDir *= -1.0f;
	}
	this->isRotating = isRotating;
	this->rotateDir = rotateDir;
	this->_verticalAngle += 30.0f*dt;

}

void Cube::Draw(GLenum mode)
{
	float offset = 0.25f;

	float leftSide = _textureOffset;
	float rightSide = leftSide + 0.4f;
	float topSide = 0.25f;
	float bottomSide = 0.75f;

	GLenum error = glGetError();

	glPushMatrix();
	error = glGetError();
	{
		glRotatef(_horizontalAngle, 0.0f, 1.0f, 0.0f); // y axis rotate
		if (isRotating) {
			glRotatef(_verticalAngle, 1.0f*rotateDir, 0.0f, 0.0f); //x axis rotate
		}

		glBegin(mode);

		glColor3f(1.0f, 0.0f, 0.0f);
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

		glColor3f(0.0f, 1.0f, 0.0f);
		glTexCoord2f(leftSide, bottomSide);
		glNormal3f(1.0f, 0.0f, 0.0f);
		glVertex3f(offset, -offset, offset);

		glTexCoord2f(leftSide, topSide);
		glNormal3f(1.0f, 0.0f, 0.0f);
		glVertex3f(offset, offset, offset);

		glTexCoord2f(rightSide, topSide);
		glNormal3f(1.0f, 0.0f, 0.0f);
		glVertex3f(offset, offset, -offset);

		glTexCoord2f(rightSide, bottomSide);
		glNormal3f(1.0f, 0.0f, 0.0f);
		glVertex3f(offset, -offset, -offset);

		glColor3f(0.0f, 0.0f, 1.0f);
		glTexCoord2f(leftSide, bottomSide);
		glNormal3f(-1.0f, 0.0f, 0.0f);
		glVertex3f(-offset, -offset, -offset);

		glTexCoord2f(leftSide, topSide);
		glNormal3f(-1.0f, 0.0f, 0.0f);
		glVertex3f(-offset, offset, -offset);

		glTexCoord2f(rightSide, topSide);
		glNormal3f(-1.0f, 0.0f, 0.0f);
		glVertex3f(-offset, offset, offset);

		glTexCoord2f(rightSide, bottomSide);
		glNormal3f(-1.0f, 0.0f, 0.0f);
		glVertex3f(-offset, -offset, offset);

		glColor3f(0.0f, 1.0f, 1.0f);
		glTexCoord2f(leftSide, bottomSide);
		glNormal3f(0.0f, 0.0f, -1.0f);
		glVertex3f(offset, -offset, -offset);

		glTexCoord2f(leftSide, topSide);
		glNormal3f(0.0f, 0.0f, -1.0f);
		glVertex3f(offset, offset, -offset);

		glTexCoord2f(rightSide, topSide);
		glNormal3f(0.0f, 0.0f, -1.0f);
		glVertex3f(-offset, offset, -offset);

		glTexCoord2f(rightSide, bottomSide);
		glNormal3f(0.0f, 0.0f, -1.0f);
		glVertex3f(-offset, -offset, -offset);

		glColor3f(1.0f, 0.0f, 1.0f);
		glTexCoord2f(leftSide, bottomSide);
		glNormal3f(0.0f, 1.0f, 0.0f);
		glVertex3f(-offset, offset, offset);

		glTexCoord2f(leftSide, topSide);
		glNormal3f(0.0f, 1.0f, 0.0f);
		glVertex3f(-offset, offset, -offset);

		glTexCoord2f(rightSide, topSide);
		glNormal3f(0.0f, 1.0f, 0.0f);
		glVertex3f(offset, offset, -offset);

		glTexCoord2f(rightSide, bottomSide);
		glNormal3f(0.0f, 1.0f, 0.0f);
		glVertex3f(offset, offset, offset);

		glColor3f(1.0f, 1.0f, 1.0f);
		glTexCoord2f(leftSide, bottomSide);
		glNormal3f(0.0f, -1.0f, 0.0f);
		glVertex3f(-offset, -offset, -offset);

		glTexCoord2f(leftSide, topSide);
		glNormal3f(0.0f, -1.0f, 0.0f);
		glVertex3f(-offset, -offset, offset);

		glTexCoord2f(rightSide, topSide);
		glNormal3f(0.0f, -1.0f, 0.0f);
		glVertex3f(offset, -offset, offset);

		glTexCoord2f(rightSide, bottomSide);
		glNormal3f(0.0f, -1.0f, 0.0f);
		glVertex3f(offset, -offset, -offset);

		glEnd();
	}
	glPopMatrix();
}