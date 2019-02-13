	/*
	DayZ SA Tomato Gui Admin tool for DayZ Standalone. Contact DayZ-SA-Tomato@Primary-Network.de
	Copyright (C) 2018  DayZ-SA-Tomato
	
	This file is part of DayZ SA Tomato.
	
    DayZ SA Tomato is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    DayZ SA Tomato is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with DayZ SA Tomato.  If not, see <https://www.gnu.org/licenses/>.
	*/
class AdminMenuGuiAbout2 extends ScriptedWidgetEventHandler
{
	
	protected Widget						m_Root;
	protected AdminMenuGui					m_Menu;
	protected MultilineTextWidget m_Text_Txt;
	void AdminMenuGuiAbout2( Widget parent, AdminMenuGui menu )
	{
		m_Root					= GetGame().GetWorkspace().CreateWidgets( "com\\DayZ-SA-Tomato\\scripts\\5_Mission\\core\\modules\\GUI\\Layouts\\Admin_About.layout", parent );
		m_Menu						= menu;
		m_Text_Txt				= MultilineTextWidget.Cast( m_Root.FindAnyWidget( "Text_About_Txt" ) );
	}
	
	void ~AdminMenuGuiAbout2()
	{
		
	}
	
	
	void Focus()
	{
		
	}
	
}
