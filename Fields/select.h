#pragma once
#include "fields.h"
#include <iostream>

namespace fields {
	class select
	{
		sf::RectangleShape rect;
		sf::Text *lines;
		sf::Color fontClr;
		char size;
		char active;
		int height;
		int x, y;
		short hoverField;
		bool isPressedOutside;
		bool pressed;
	public:
		//Constructor and Destructor
		select(char Size, std::string* Text, sf::Font& Font, int FontSize,
			int x, int y);
		~select();
		//Render && update
		void render(sf::RenderTarget& Target);
		void update(sf::Vector2f& MouseWindowPos);
		void update(sf::Vector2i& MouseWindowPos);
		//Accessors
		std::string getActive();
		int getIntActive();
	};
}