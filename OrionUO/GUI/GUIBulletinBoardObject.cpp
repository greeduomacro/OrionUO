/***********************************************************************************
**
** GUIBulletinBoardObject.h
**
** Copyright (C) August 2016 Hotride
**
************************************************************************************
*/
//----------------------------------------------------------------------------------
#include "GUIBulletinBoardObject.h"
#include "../Managers/MouseManager.h"
#include "../Managers/FontsManager.h"
#include "../OrionUO.h"
//----------------------------------------------------------------------------------
CGUIBulletinBoardObject::CGUIBulletinBoardObject(const uint &serial, const int &x, const int &y, const string &text)
: CBaseGUI(GOT_BB_OBJECT, serial, 0, 0, x, y), m_Text(text)
{
	m_MoveOnDrag = true;
	g_FontManager.GenerateA(9, m_Texture, text.c_str(), 0x0386);
}
//----------------------------------------------------------------------------------
CGUIBulletinBoardObject::~CGUIBulletinBoardObject()
{
	m_Texture.Clear();
}
//----------------------------------------------------------------------------------
void CGUIBulletinBoardObject::Draw(const bool &checktrans)
{
	CGLTexture *th = g_Orion.ExecuteGump(0x1523);

	if (th != NULL)
		th->Draw(m_X, m_Y, checktrans);

	m_Texture.Draw(m_X + 23, m_Y + 1);
}
//----------------------------------------------------------------------------------
bool CGUIBulletinBoardObject::Select()
{
	int x = g_MouseManager.Position.X - m_X;
	int y = g_MouseManager.Position.Y - m_Y;

	return (x >= 0 && y >= 0 && x < 230 && y < 18);
}
//----------------------------------------------------------------------------------
