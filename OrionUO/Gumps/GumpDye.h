/***********************************************************************************
**
** GumpDye.h
**
** Copyright (C) August 2016 Hotride
**
************************************************************************************
*/
//----------------------------------------------------------------------------------
#ifndef GUMPDYE_H
#define GUMPDYE_H
//----------------------------------------------------------------------------------
#include "GumpSelectColor.h"
//----------------------------------------------------------------------------------
class CGumpDye : public CGumpSelectColor
{
private:
	ushort GetCurrentColor();

	CGUITilepic *m_Tube;

public:
	CGumpDye(uint serial, short x, short y, ushort graphic);
	virtual ~CGumpDye();

	virtual void UpdateContent();

	virtual void OnSelectColor(const ushort &color);

	GUMP_BUTTON_EVENT_H;
	GUMP_SLIDER_CLICK_EVENT_H;
	GUMP_SLIDER_MOVE_EVENT_H;
};
//----------------------------------------------------------------------------------
#endif
//----------------------------------------------------------------------------------
