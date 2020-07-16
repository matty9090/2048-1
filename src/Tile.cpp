#include <string>
#include <sstream>
#include <iostream>
#include <stdlib.h>
#include "Tile.h"
#include "TextureHolder.h"

Tile::Tile()
{
	m_ValueMultiplier = 0;
}

void Tile::update(float elapsedTime)
{
	float maximumX = BOARD_LOC + 40.0f + (m_moveTo * 160.0f);
	switch (m_Dir)
	{
	case 1:
		if (m_inAnim)
		{
			if (m_Position.x == maximumX) //If we've moved as far as we need to
			{
				m_inAnim = false;
				m_Position.x = m_StartingPos.x;
				m_isEmpty = true;
			}
			else
			{
				m_Position.x += m_Speed * elapsedTime;
				if (m_Position.x > maximumX)
				{
					m_Position.x = maximumX;
				}
			}
		}
		break;
	case 2:
		//Left
		break;
	case 3:
		//Up
		break;
	case 4:
		//Down
		break;
	}
	m_Sprite.setPosition(m_Position);
}

void Tile::setStartingPos(Vector2f startingPos)
{
	m_StartingPos = startingPos;
}

void Tile::setValue(int val)
{
	m_ValueMultiplier = val;

	//Get the appropriate texture for the value of the tile
	switch (val)
	{
	case 0:
		//This doesn't technically matter since the tile won't be drawn
		//if it doesn't have a value
		m_Texture = TextureHolder::GetTexture("assets/default.png");
		m_isEmpty = true;
		break;
	default:
		int number = pow(2, val);;
		string numStr = to_string(number);
		stringstream ss;
		ss << "assets/tile" << numStr << ".png";
		m_Texture = TextureHolder::GetTexture(ss.str());
		m_isEmpty = false;
		break;
	}
	m_Sprite.setTexture(m_Texture);
}

void Tile::setPosition(Vector2f pos)
{
	m_Position.x = pos.x;
	m_Position.y = pos.y;
	m_Sprite.setPosition(m_Position);
}

void Tile::setCombined(bool dir)
{
	m_beenCombined = dir;
}

void Tile::setMoveTo(int mt)
{
	m_moveTo = mt;
}

void Tile::setAnimate(bool anim, int dir)
{
	m_Dir = dir;
	m_inAnim = anim;
}

void Tile::setSpeed(int currentPos)
{
	m_Speed = m_Speed * abs(m_moveTo - currentPos);
}

bool Tile::isEmpty()
{
	return m_isEmpty;
}

int Tile::getValue()
{
	return m_ValueMultiplier;
}

bool Tile::getCombined()
{
	return m_beenCombined;
}

int Tile::getMoveTo()
{
	return m_moveTo;
}

bool Tile::needsAnimating()
{
	return m_inAnim;
}

Sprite Tile::getSprite()
{
	return m_Sprite;
}