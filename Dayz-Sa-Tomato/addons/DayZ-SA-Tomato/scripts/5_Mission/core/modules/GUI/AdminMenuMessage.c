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
class AdminMenuMessage extends UIScriptedMenu
{
	ref AdminMenuManager AMenuM;
	protected MultilineTextWidget m_MessageBox_Text;
	string MyText;
	// int CURRENT_STAMP;
	
	
	void AdminMenuMessage(string myText)
	{
		MyText = myText;
		SetID(7001);
		GetGame().GetCallQueue( CALL_CATEGORY_SYSTEM ).CallLater( this.MessageClose, 1000, true );
	}
	
	override void Update(float tome) 
	{
		
	}
	
	void MessageClose()
	{
		this.Close();
	}
	
	
	
	override Widget Init()
	{
		layoutRoot		= GetGame().GetWorkspace().CreateWidgets( "com\\DayZ-SA-Tomato\\scripts\\5_Mission\\core\\modules\\GUI\\Layouts\\MessageBox.layout", null );
		SetID(7001);
		m_MessageBox_Text = TextWidget.Cast( layoutRoot.FindAnyWidget( "MessageBox_Text" ) );
		m_MessageBox_Text.SetText(MyText);
		return layoutRoot;
	}
	
	void ~AdminMenuMessage()
	{
		GetGame().GetCallQueue( CALL_CATEGORY_SYSTEM ).Remove( this.MessageClose );
		this.Close();
	}
	
	override bool OnClick( Widget w, int x, int y, int button )
	{
		return true;
	}
	
	
}
// ref AdminMenuGui Tomato_AdminMenu;

// ref AdminMenuGui GetAdminMenu()
// {
    // if( !Tomato_AdminMenu )
    // {
        // Tomato_AdminMenu = new ref AdminMenuGui();
    // }

    // return Tomato_AdminMenu;
// }