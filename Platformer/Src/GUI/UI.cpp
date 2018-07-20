#include "UI.h"

UI::UI()
{
	InitHealth();
}

void UI::Update(const sf::RenderWindow & main_window)
{
	for (Heart& obj : m_heartsArray)
	{
		obj.sprite.setPosition(main_window.mapPixelToCoords(sf::Vector2i(WindowWidth - (35 * (3 - obj.id)), 10.f)));
	}
}

void UI::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	for (auto& item : m_heartsArray)
		target.draw(item.sprite, states);
}

void UI::InitHealth()
{
	if (!m_heartTexture.loadFromFile("Res/darker_heart.png"))
		std::cerr << "Could not open darker_heart.png" << std::endl;

	int heart_id_count = 0;
	for (Heart& obj : m_heartsArray)
	{
		obj.id = heart_id_count;
		obj.sprite.setTexture(m_heartTexture);
		obj.sprite.setPosition(sf::Vector2f(WindowWidth - (16 * (3 - heart_id_count)), 10.f));
		obj.isActive = true;

		++heart_id_count;
	}
}
