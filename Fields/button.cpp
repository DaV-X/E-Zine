#include "button.h"

//Constructor and Destructor
fields::button::button(float x, float y, sf::Font* font, int size, sf::Color color,const char* string, bool active)
{
	shape = nullptr;

	text = new sf::Text();
	text->setFont(*font);
	text->setCharacterSize(size);
	text->setFillColor(sf::Color(color));
	text->setString(string);
	text->setOrigin(text->getLocalBounds().width/2, text->getLocalBounds().height / 2);
	text->setPosition(x,y);

	fontSize = size;
	this->x = x;
	this->y = y;
	extraSize = 0.f;
	isPressedOutside = false;

	if (active)
		state = IDLE;
	else
	{
		state = DISACTIVE;
		text->setFillColor(color);
		shape->setFillColor(sf::Color(255, 255, 255, 100));
	}
}
fields::button::~button()
{
	delete this->text;
	delete this->shape;
}

//Functions
void fields::button::render(sf::RenderTarget* Target)
{
	if(shape !=nullptr)
		Target->draw(*shape);
	if(text!=nullptr)
		Target->draw(*text);
}
void fields::button::update(sf::Vector2f *MouseViewPos, float *dt)
{
	if (this->state != DISACTIVE) {
		if (shape != nullptr && shape->getGlobalBounds().contains(*MouseViewPos)) {
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !this->isPressedOutside)
				this->state = ACTIVE;
			else if (this->state != HOVER)
				this->state = HOVER;
		}
		else if (text->getGlobalBounds().contains(*MouseViewPos)) {
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !this->isPressedOutside)
				this->state = ACTIVE;
			else if (this->state != HOVER)
				this->state = HOVER;
		}
		else
		{
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				this->isPressedOutside = true;
			if (this->state == HOVER)
				this->state = IDLE;
		}

		if (this->isPressedOutside && !sf::Mouse::isButtonPressed(sf::Mouse::Left))
			this->isPressedOutside = false;
		this->animation(dt);
	}
}
void fields::button::update(sf::Vector2i* MousePos, float* dt)
{
	if (this->state != DISACTIVE) {
		if (shape != nullptr && shape->getGlobalBounds().contains(sf::Vector2f(*MousePos))) {
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !this->isPressedOutside)
				this->state = ACTIVE;
			else if (this->state != HOVER)
				this->state = HOVER;
		}
		else if (text->getGlobalBounds().contains(sf::Vector2f(*MousePos))) {
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !this->isPressedOutside)
				this->state = ACTIVE;
			else if (this->state != HOVER)
				this->state = HOVER;
		}
		else
		{
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				this->isPressedOutside = true;
			if (this->state == HOVER)
				this->state = IDLE;
		}

		if (this->isPressedOutside && !sf::Mouse::isButtonPressed(sf::Mouse::Left))
			this->isPressedOutside = false;
		this->animation(dt);
	}
}
unsigned short fields::button::getState()
{
	if (state == ACTIVE) {
		this->state = IDLE;
		this->isPressedOutside = true;
		return ACTIVE;
	}
	return state;
}

void fields::button::animation(float* dt)
{
	if (this->state == HOVER && this->extraSize < 6.f){
		extraSize += 50.f * (*dt);
		if (extraSize > 6.0f)
			extraSize = 6.0f;
		if (text != nullptr) {
			text->setCharacterSize(fontSize + extraSize);
			text->setOrigin(text->getLocalBounds().width / 2, text->getLocalBounds().height / 2);
			text->setPosition(x,y);
		}
	}
	else if (this->state == IDLE && this->extraSize > 0.f) {
		extraSize -= 50.f * (*dt);
		if (this->extraSize < 0.f)
			this->extraSize = 0.f;
		if (text != nullptr) {
			text->setCharacterSize(fontSize + extraSize);
			text->setOrigin(text->getLocalBounds().width / 2, text->getLocalBounds().height / 2);
			text->setPosition(x, y);
		}
	}
}