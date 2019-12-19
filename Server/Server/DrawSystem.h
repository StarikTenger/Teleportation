#pragma once
#include <map>
#include <SFML/Graphics.hpp>
#include "Color.h"
#include "System.h"
#include "Camera.h"
#include "Mouse.h"

class DrawSystem {
public:
	sf::RenderWindow* window;
	Camera cam;
	System* system;
	bool fullscreenMode = 0;
	DrawSystem();
	~DrawSystem();
	Mouse mouse;
	double w, h;
	double blockSize = 1;


	void draw();
	void drawScene();
	void drawInterface();
	sf::Font font;
	
//private:
	//basics
	Color fromHSV(double H, double S, double V);
	void fillRect(double x, double y, double width, double height, Color color);
	void fillCircle(double x, double y, double r, Color color);
	void strokeRect(double x, double y, double width, double height, Color color);
	void line(double x, double y, double x1, double y1, Color color);
	void image(std::string name, double x, double y, double width, double height, double angle);
	void image(std::string name, double x, double y, double width, double height, double angle, Color color);
	void image(std::string name, double x, double y, double width, double height, double angle, double d);
	void text(std::string text, double x, double y, int size, Color color);
	//objects
	
	//load
	std::map<std::string, sf::Texture*> textures;
	void loadTexture(std::string name, std::string path);
	void loadTextures();
};

