/***********************************************************************************
**
** OrionApplication.h
**
** Copyright (C) August 2016 Hotride
**
************************************************************************************
*/
//----------------------------------------------------------------------------------
#ifndef ORIONAPPLICATION_H
#define ORIONAPPLICATION_H
//----------------------------------------------------------------------------------
#include "Wisp/WispApplication.h"\
//----------------------------------------------------------------------------------
class COrionApplication : public WISP_APPLICATION::CApplication
{
public:
	COrionApplication() : WISP_APPLICATION::CApplication() {}
	virtual ~COrionApplication() {}
};
//----------------------------------------------------------------------------------
extern COrionApplication g_App;
//----------------------------------------------------------------------------------
#endif
//----------------------------------------------------------------------------------