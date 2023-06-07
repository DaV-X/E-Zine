#include "select.h"

fields::select::select(char Size, std::string* Text, sf::Font& Font, int FontSize,
	int X, int Y)
{
	int MaxWidth{};
	x = X;
	y = Y;
	active = false;
	pressed = false;
	hoverField = 0;
	fontClr.r = 255;
	fontClr.g = 255;
	fontClr.b = 255;

	height = 0;
	isPressedOutside = false;

	size = Size;
	lines = new sf::Text[Size];
	for (int i = 0;i<Size;i++) {
		lines[i].setFont(Font);
		lines[i].setCharacterSize(FontSize);
		lines[i].setString(Text[i]);
		lines[i].setOrigin(lines[i].getLocalBounds().width/2.f, lines[i].getLocalBounds().height / 2.f+ lines[i].getLocalBounds().top);
		if(i==0)
			lines[i].setPosition(x, y);
		else
			lines[i].setPosition(x, lines[i-1].getGlobalBounds().top+ lines[i - 1].getGlobalBounds().height+ lines[i].getGlobalBounds().height/2 + 5);
		height += lines[i].getGlobalBounds().height+5;
		if (lines[i].getLocalBounds().width > MaxWidth) 
			MaxWidth = lines[i].getLocalBounds().width;
	}


	rect.setOutlineThickness(2);
	rect.setOutlineColor(sf::Color::Black);
	rect.setFillColor(sf::Color(125,125,125));
	rect.setSize(sf::Vector2f(MaxWidth+20, lines[0].getGlobalBounds().height+5));
	rect.setOrigin(rect.getSize().x/2, rect.getSize().y / 2);
	rect.setPosition(x,y);
}
fields::select::~select()
{
	for (int i = 0;i<size;i++) {
		delete &(lines[i]);
	}
}
//Render
void fields::select::render(sf::RenderTarget& Target)
{
	Target.draw(rect);
	Target.draw(lines[0]);
	if (active) {
		for (int i = 1;i<size;i++) {
			Target.draw(lines[i]);
		}
	}
}
//Update
void fields::select::update(sf::Vector2f& MouseWindowPos)
{
	if (rect.getGlobalBounds().contains(MouseWindowPos) && !isPressedOutside) {
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			if (!active) {
				active = true;
				pressed = true;
				rect.setSize(sf::Vector2f(rect.getSize().x, height));
			}
			else if(pressed == false){
				pressed = true;
				//swap lines
				std::string tempString = lines[0].getString();
				lines[0].setString(lines[hoverField].getString());
				lines[hoverField].setString(tempString);
				lines[0].setOrigin(lines[0].getLocalBounds().width / 2.f, lines[0].getLocalBounds().height / 2.f + lines[0].getLocalBounds().top);
				lines[hoverField].setOrigin(lines[hoverField].getLocalBounds().width / 2.f,
					lines[hoverField].getLocalBounds().height / 2.f + lines[hoverField].getLocalBounds().top);
			}
		}
		else if(pressed == true) {
			pressed = false;
		}
	}
	else
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			this->isPressedOutside = true;
		}
		else if(this->isPressedOutside) {
			this->isPressedOutside = false;
			pressed = false;
		}
		if (active) {
			active = false;
			rect.setSize(sf::Vector2f(rect.getSize().x, lines[0].getGlobalBounds().height+5));
		}
	}
	if (active) {
		for (int i = 0;i<size;i++) {
			if (lines[i].getGlobalBounds().contains(MouseWindowPos)) {
				lines[hoverField].setFillColor(sf::Color(fontClr.r, fontClr.g, fontClr.b));
				hoverField = i;
				lines[hoverField].setFillColor(sf::Color(fontClr.r-50,fontClr.g-50,fontClr.b-50));
				break;
			}
		}
		
	}
}

void fields::select::update(sf::Vector2i& MouseWindowPos)
{
	if (rect.getGlobalBounds().contains(sf::Vector2f(MouseWindowPos)) && !isPressedOutside) {
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			if (!active) {
				active = true;
				pressed = true;
				rect.setSize(sf::Vector2f(rect.getSize().x, height));
			}
			else if (pressed == false) {
				pressed = true;
				//swap lines
				std::string tempString = lines[0].getString();
				lines[0].setString(lines[hoverField].getString());
				lines[hoverField].setString(tempString);
				lines[0].setOrigin(lines[0].getLocalBounds().width / 2.f, lines[0].getLocalBounds().height / 2.f + lines[0].getLocalBounds().top);
				lines[hoverField].setOrigin(lines[hoverField].getLocalBounds().width / 2.f,
					lines[hoverField].getLocalBounds().height / 2.f + lines[hoverField].getLocalBounds().top);
			}
		}
		else if (pressed == true) {
			pressed = false;
		}
	}
	else
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			this->isPressedOutside = true;
		}
		else if (this->isPressedOutside) {
			this->isPressedOutside = false;
			pressed = false;
		}
		if (active) {
			active = false;
			rect.setSize(sf::Vector2f(rect.getSize().x, lines[0].getGlobalBounds().height + 5));
		}
	}
	if (active) {
		for (int i = 0; i < size; i++) {
			if (lines[i].getGlobalBounds().contains(sf::Vector2f(MouseWindowPos))) {
				lines[hoverField].setFillColor(sf::Color(fontClr.r, fontClr.g, fontClr.b));
				hoverField = i;
				lines[hoverField].setFillColor(sf::Color(fontClr.r - 50, fontClr.g - 50, fontClr.b - 50));
				break;
			}
		}

	}
}

std::string fields::select::getActive()
{
	return lines[0].getString();
}

int fields::select::getIntActive()
{
	return active;
}
