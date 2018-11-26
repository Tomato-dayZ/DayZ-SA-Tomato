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
class AdminMenuGui extends UIScriptedMenu
{
	protected TabberUI					m_Tabber;
	protected ref AdminMenuGuiCommands		m_CommandTab;
	protected ref AdminMenuGuiSpawn		m_SpawnTab;
	protected ref AdminMenuGuiPlayer		m_PlayerTab;
	protected ref AdminMenuGuiMap	m_MapTab;
	protected ref map<string, string> m_TestListS;
	protected string m_TestListPath = "$CurrentDir:\\DayZ-SA-Tomato\\";
	
	protected ButtonWidget				m_Back;
	
	void AdminMenuGui()
	{
		
	}
	
	override bool OnItemSelected( Widget w, int x, int y, int row, int column, int oldRow, int oldColumn )
	{
		bool okstap;
		okstap = false;
		if ( w == m_SpawnTab.m_classList ) {
		okstap = m_SpawnTab.OnItemSelect(w, x, y, row, column, oldRow, oldColumn)
	return okstap;
		}
		return okstap;
	}
	
	void Message( string txt ) 
	{
        GetGame().GetMission().OnEvent(ChatMessageEventTypeID, new ChatMessageEventParams(0, "", txt, ""));
	}
	override bool OnChange( Widget w, int x, int y, bool finished )
	{
		if ( w == m_PlayerTab.m_PlayerList )
        {
            m_PlayerTab.PlayerSelect();
            return true;
        }
		
		if ( w == m_SpawnTab.m_Spawn_SearchBox )
        {
            m_SpawnTab.UpdateList( "All" );
            return true;
        }
		
		if ( w == m_CommandTab.m_Config_Teleport )
        {
            m_CommandTab.Set_Teleport();
            return true;
        }
		
		if ( w == m_CommandTab.m_Config_Cam )
        {
            m_CommandTab.Set_Cam();
            return true;
        }
		
		if ( w == m_PlayerTab.m_Cb_Player_Stamina )
        {
            m_PlayerTab.Set_Stamina();
            return true;
        }

        return false;
    }
	void ItemPrevCall(EntityAI item)
	{
		m_SpawnTab.OnItemSelect2(item);
	}


		
	
	
	override Widget Init()
	{
		layoutRoot		= GetGame().GetWorkspace().CreateWidgets( "com\\DayZ-SA-Tomato\\scripts\\5_Mission\\core\\modules\\GUI\\Layouts\\Admin_Main.layout", null );
		
		layoutRoot.FindAnyWidget( "Tabber" ).GetScript( m_Tabber );
		

		
		m_CommandTab			= new AdminMenuGuiCommands( layoutRoot.FindAnyWidget( "Tab_0" ), this );
		m_SpawnTab			= new AdminMenuGuiSpawn( layoutRoot.FindAnyWidget( "Tab_1" ), this );
		m_PlayerTab		= new AdminMenuGuiPlayer( layoutRoot.FindAnyWidget( "Tab_2" ), this );
		m_MapTab	= new AdminMenuGuiMap( layoutRoot.FindAnyWidget( "Tab_3" ), this );

		m_Back				= ButtonWidget.Cast( layoutRoot.FindAnyWidget( "back" ) );

		
		SetFocus( layoutRoot );
		
		
		m_Tabber.m_OnTabSwitch.Insert( OnTabSwitch );
		
		/*
		//-----Add Admins from txt-----
		FileHandle AdminUIDSFile = OpenFile(m_AdminListPath + "Admins.txt",FileMode.READ);
		if (AdminUIDSFile != 0)
		{
			m_AdminList    = new map<string, string>; //UID, name
			string line_content = "";
			while ( FGets(AdminUIDSFile,line_content) > 0 )
			{
				m_AdminList.Insert(line_content,"null"); //UID , NAME
				Print("Adding Admin: "+ line_content + " To the Admin List!");
			}
			CloseFile(AdminUIDSFile);
		}
		
		*/
		return layoutRoot;
	}
	
	void ~AdminMenuGui()
	{
		
	}
	
	override bool OnClick( Widget w, int x, int y, int button )
	{
		//SpawnTab
		bool ok = false;
		if ( w.GetName().Contains("_spawn_") )
		{
			ok = m_SpawnTab.Click(w, x, y, button)
			return ok;
		}
		
		//CommandTab
		if ( w.GetName().Contains("_Command_") )
		{
			ok = m_CommandTab.Click(w, x, y, button)
			return ok;
		}
		
		//PlayerTab
		if ( w.GetName().Contains("_Player_") )
		{
			ok = m_PlayerTab.Click(w, x, y, button)
			return ok;
		}
		
		//Main Widget
		if( button == MouseState.LEFT )
		{
			if( w == m_Back )
			{
				Back();
				return true;
			}
		}
		return false;
	}
	
	void OnTabSwitch( int tab )
	{
		switch( tab )
		{
			case 0:
			{
				m_CommandTab.Focus();
				break;
			}
			case 1:
			{
				m_SpawnTab.Focus();
				break;
			}
			case 2:
			{
				m_PlayerTab.Focus();
				break;
			}
			case 3:
			{
				m_MapTab.Focus();
				break;
			}
		}
	}
	
	
	void Back()
	{	
		GetGame().EndOptionsVideo();
		GetGame().GetUIManager().Back();
		
	}
	

	
	
	override bool OnMouseEnter( Widget w, int x, int y )
	{
		if( w && IsFocusable( w ) )
		{
			ColorRed( w );
			return true;
		}
		return false;
	}
	
	override bool OnMouseLeave( Widget w, Widget enterW, int x, int y )
	{
		if( w && IsFocusable( w ) )
		{
			ColorWhite( w, enterW );
			return true;
		}
		return false;
	}
	
	override bool OnFocus( Widget w, int x, int y )
	{
		if( w && IsFocusable( w ) )
		{
			ColorRed( w );
			return true;
		}
		return false;
	}
	
	override bool OnFocusLost( Widget w, int x, int y )
	{
		if( w && IsFocusable( w ) )
		{
			ColorWhite( w, null );
			return true;
		}
		return false;
	}
	
	bool IsFocusable( Widget w )
	{
		if( w )
		{
			return (  w == m_Back  );
		}
		return false;
	}
	
	
	override void OnShow()
	{
		super.OnShow();
		GetGame().GetUIManager().ShowUICursor( true );
		GetGame().GetInput().ChangeGameFocus( 1 );
	}
	
	override void OnHide()
	{
		super.OnHide();
		GetGame().GetUIManager().ShowUICursor( false );
		GetGame().GetInput().ResetGameFocus( );
	}
	
	//Coloring functions (Until WidgetStyles are useful)
	void ColorRed( Widget w )
	{
		SetFocus( w );
		
		ButtonWidget button = ButtonWidget.Cast( w );
		if( button )
		{
			button.SetTextColor( ARGB( 255, 200, 0, 0 ) );
		}
	}
	
	void ColorWhite( Widget w, Widget enterW )
	{
		#ifdef PLATFORM_WINDOWS
		SetFocus( null );
		#endif
		
		ButtonWidget button = ButtonWidget.Cast( w );
		if( button )
		{
			button.SetTextColor( ARGB( 255, 255, 255, 255 ) );
		}
	}
}
