#pragma once
namespace GL
{
	void SetupOrtho();
	void RestoteGL();
	void DrawFilledRect();
	void DrawLine(float fromX, float fromY, float toX, float toY, float lineWidth, const GLubyte color[3]);
	DrawEspBox(float posX, float posY, float distance, const GLubyte color[3], const char* const name, const int healthPercent);

};

