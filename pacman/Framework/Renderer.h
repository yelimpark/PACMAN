#pragma once

class Renderer {
private:
	char ** screen;
	int screenSizeX;
	int screenSizeY;

	void clear();
public:
	Renderer(int screenSizeX, int screenSizeY);

	bool InitializeRenderer();

	/// <summary>
	/// ���� �׸���.
	/// </summary>
	/// <returns> </returns>
	void Render(char * screenIn[]);

	~Renderer();
};

