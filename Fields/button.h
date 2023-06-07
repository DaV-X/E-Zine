#pragma once
#include "fields.h"

namespace fields {
	class button
	{
	private:
		sf::RectangleShape *shape;
		sf::Text *text;

		int fontSize;
		float x, y;
		int width, height;
		float extraSize;
		unsigned short state;
		bool isPressedOutside;

		//Functions
		void animation(float *dt);
	public:
		//Constructor and Destructor
		button(float x, float y, sf::Font* font, int size, sf::Color color,const char* string, bool active = true);
		~button();
		//Functions
		void render(sf::RenderTarget* Target);
		void update(sf::Vector2f *MouseViewPos,float *dt);
		void update(sf::Vector2i *MousePos,float *dt);
		unsigned short getState();
	};
}