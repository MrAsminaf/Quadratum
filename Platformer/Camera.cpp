#include "Camera.h"

Camera::Camera()
	:
	m_view(sf::FloatRect(200,200,514,300))
{
	
	m_view.setCenter(300,300);
}

sf::View & Camera::GetView()
{
	return m_view;
}
