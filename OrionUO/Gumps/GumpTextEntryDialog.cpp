/***********************************************************************************
**
** GumpTextEntryDialog.cpp
**
** Copyright (C) August 2016 Hotride
**
************************************************************************************
*/
//----------------------------------------------------------------------------------
#include "GumpTextEntryDialog.h"
#include "../Managers/GumpManager.h"
#include "../OrionUO.h"
#include "../Screen stages/GameBlockedScreen.h"
#include "../Network/Packets.h"
//----------------------------------------------------------------------------------
CGumpTextEntryDialog::CGumpTextEntryDialog(uint serial, short x, short y, uchar variant, int maxLength, string text, string description)
: CGump(GT_TEXT_ENTRY_DIALOG, serial, x, y), m_Text(text), m_Description(description),
m_Variant(variant), m_MaxLength(maxLength), m_ParentID(0), m_ButtonID(0),
m_TextField(NULL), m_Entry(NULL)
{
	m_NoMove = true;
	m_Blocked = true;

	if (!g_GrayMenuCount)
	{
		g_Orion.InitScreen(GS_GAME_BLOCKED);
		g_GameBlockedScreen.Code = 2;
	}

	g_GrayMenuCount++;
}
//----------------------------------------------------------------------------------
CGumpTextEntryDialog::~CGumpTextEntryDialog()
{
}
//----------------------------------------------------------------------------------
void CGumpTextEntryDialog::PrepareContent()
{
	if (m_TextField != NULL && m_Entry != NULL)
	{
		ushort newGraphic = 0x0475; //Text field

		if (g_EntryPointer == &m_Entry->m_Entry)
			newGraphic = 0x0477; //Text field (active)
		else if (g_SelectedObject.Object() == m_Entry)
			newGraphic = 0x0476; //Text field (lighted)

		if (m_TextField->Graphic != newGraphic)
		{
			m_TextField->Graphic = newGraphic;
			m_WantRedraw = true;
		}
	}
}
//----------------------------------------------------------------------------------
void CGumpTextEntryDialog::UpdateContent()
{
	Clear();

	Add(new CGUIGumppic(0x0474, 0, 0));

	CGUIText *text = (CGUIText*)Add(new CGUIText(0x0386, 60, 50));
	text->CreateTextureA(2, m_Text);

	text = (CGUIText*)Add(new CGUIText(0x0386, 60, 108));
	text->CreateTextureA(2, m_Description);

	CGump *gumpEntry = g_GumpManager.GetTextEntryOwner();

	if (gumpEntry != NULL)
		gumpEntry->WantRedraw = true;

	m_TextField = (CGUIGumppic*)Add(new CGUIGumppic(0x0477, 60, 130));
	m_TextField->Serial = ID_GTED_TEXT_FIELD;

	m_Entry = (CGUITextEntry*)Add(new CGUITextEntry(ID_GTED_TEXT_FIELD, 0x0386, 0x0386, 0x0386, 71, 137, 0, false, 1));
	m_Entry->m_Entry.MaxLength = m_MaxLength;
	m_Entry->m_Entry.NumberOnly = (m_Variant == 2);
	m_Entry->CheckOnSerial = true;
	g_EntryPointer = &m_Entry->m_Entry;

	Add(new CGUIButton(ID_GTED_BUTTON_OKAY, 0x047B, 0x047D, 0x047C, 117, 190));

	if (!m_NoClose)
		Add(new CGUIButton(ID_GTED_BUTTON_CANCEL, 0x0478, 0x047A, 0x0479, 204, 190));
}
//----------------------------------------------------------------------------------
void CGumpTextEntryDialog::GUMP_BUTTON_EVENT_C
{
	if (serial == ID_GTED_BUTTON_OKAY) //Button okay
		SendTextEntryDialogResponse(true);
	else if (serial == ID_GTED_BUTTON_CANCEL) //Button cancel
		SendTextEntryDialogResponse(false);
}
//----------------------------------------------------------------------------------
void CGumpTextEntryDialog::OnCharPress(const WPARAM &wParam, const LPARAM &lParam)
{
	if (m_Variant == 2) //������ �����
	{
		if (wParam >= '0' && wParam <= '9')
		{
			g_EntryPointer->Insert(wParam);

			int val = atoi(g_EntryPointer->c_str());

			if (val > m_MaxLength)
				g_EntryPointer->Remove(true);
			else
				m_WantRedraw = true;
		}
	}
	else if (m_Variant == 1) //��� ������, �� � ������������ �� �����
	{
		if (g_EntryPointer->Length() < m_MaxLength)
		{
			g_EntryPointer->Insert(wParam);
			m_WantRedraw = true;
		}
	}
}
//----------------------------------------------------------------------------------
void CGumpTextEntryDialog::OnKeyDown(const WPARAM &wParam, const LPARAM &lParam)
{
	switch (wParam)
	{
		case VK_RETURN:
		case VK_ESCAPE:
		{
			SendTextEntryDialogResponse(wParam == VK_RETURN);

			break;
		}
		case VK_HOME:
		case VK_END:
		case VK_LEFT:
		case VK_RIGHT:
		case VK_BACK:
		case VK_DELETE:
		{
			g_EntryPointer->OnKey(this, wParam);
			m_WantRedraw = true;

			break;
		}
		default:
			break;
	}
}
//----------------------------------------------------------------------------------
void CGumpTextEntryDialog::SendTextEntryDialogResponse(bool mode)
{
	if (!m_RemoveMark && m_Entry != NULL) //�������������� ������ ��� ���������� ���� ����� ������ � �����
	{
		//���������� ����� �� ����� ������
		CPacketTextEntryDialogResponse(this, &m_Entry->m_Entry, mode).Send();
	}

	//������� �������������� ����
	m_RemoveMark = true;
}
//----------------------------------------------------------------------------------
