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
	protected ref AdminMenuGuiTeleport	m_TeleportTab;
	protected ref AdminMenuGuiAbout	m_AboutTab;
	protected ref AdminMenuGuiAbout2	m_AboutTab2;
	ref AdminMenuManager AMenuM;
	protected ref map<string, string> m_TestListS;
	protected string m_TestListPath = "$CurrentDir:\\DayZ-SA-Tomato\\";
	ref array<string> Locations;
	protected ButtonWidget				m_Back;
	protected TextWidget m_txt_Main_Ver;
	static MultilineTextWidget m_txt_Main_Status;
	
	void AdminMenuGui()
	{
		ref array <string> Locations = new ref array<string>;
		SetID(7000);
		GetDayZGame().Event_OnRPC.Insert( this.ReceiveRPC );
	}
	override void Update(float tome) 
	{
		m_MapTab.Update();
	}
	
	
	override bool OnItemSelected( Widget w, int x, int y, int row, int column, int oldRow, int oldColumn )
	{
		
		bool okstap;
		okstap = false;
		if ( w == m_SpawnTab.m_classList ) {
		okstap = m_SpawnTab.OnItemSelect(w, x, y, row, column, oldRow, oldColumn);
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
		
		 if ( w == m_MapTab.m_Config_Map_Teleport )
         {
             m_MapTab.Set_Map_Teleport();
             return true;
         }
		
		if ( w == m_MapTab.m_Config_Map_Horde )
        {
            m_MapTab.Set_Map_Horde();
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

	void ReceiveRPC( PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx ) 
	{
		switch(rpc_type)
		{
			
			case (int)M_RPCs.M_Admin_Menu_MessageStatus:
			Param1<string> MenuMessagep;
				ctx.Read( MenuMessagep );
				string MenuMessage = MenuMessagep.param1;
				if ( GetGame().IsClient() && GetGame().IsMultiplayer() ) 
				{
					SetStatus(MenuMessage);
				}
			break;
		}
	}
		
	
	
	override Widget Init()
	{
		layoutRoot		= GetGame().GetWorkspace().CreateWidgets( "com\\DayZ-SA-Tomato\\scripts\\5_Mission\\core\\modules\\GUI\\Layouts\\Admin_Main.layout", null );
		
		layoutRoot.FindAnyWidget( "Tabber" ).GetScript( m_Tabber );
		

		
		 m_CommandTab			= new AdminMenuGuiCommands( layoutRoot.FindAnyWidget( "Tab_0" ), this );
		 m_SpawnTab			= new AdminMenuGuiSpawn( layoutRoot.FindAnyWidget( "Tab_1" ), this );
		 m_PlayerTab		= new AdminMenuGuiPlayer( layoutRoot.FindAnyWidget( "Tab_2" ), this );
		 m_MapTab	= new AdminMenuGuiMap( layoutRoot.FindAnyWidget( "Tab_3" ), this );
		 m_TeleportTab		= new AdminMenuGuiTeleport( layoutRoot.FindAnyWidget( "Tab_4" ), this );
		 m_AboutTab	= new AdminMenuGuiAbout( layoutRoot.FindAnyWidget( "Tab_5" ), this );
		 m_AboutTab2	= new AdminMenuGuiAbout2( layoutRoot.FindAnyWidget( "Tab_6" ), this );
		
		//m_todo	= new AdminMenuGuiTeleport( layoutRoot.FindAnyWidget( "Tab_5" ), this );
		//m_todo2	= new AdminMenuGuiTeleport( layoutRoot.FindAnyWidget( "Tab_5" ), this );

		m_Back				= ButtonWidget.Cast( layoutRoot.FindAnyWidget( "back" ) );
		m_txt_Main_Ver = TextWidget.Cast( layoutRoot.FindAnyWidget( "txt_Main_Ver" ) );
		m_txt_Main_Status = TextWidget.Cast( layoutRoot.FindAnyWidget( "txt_Main_Status" ) );
		
		m_txt_Main_Ver.SetText(GetAdminMenuManager().Version);
		SetFocus( layoutRoot );
		
		
		m_Tabber.m_OnTabSwitch.Insert( OnTabSwitch );
		return layoutRoot;
	}
	
	void ~AdminMenuGui()
	{
		delete m_SpawnTab;
		delete m_AboutTab;
		delete m_AboutTab2;
		delete m_MapTab;
		delete m_CommandTab;
		delete m_TeleportTab;
		delete m_PlayerTab;
	}
	
	void SetStatus(string txt)
	{
		// if(m_txt_Main_Status == NULL)
		// {
			 m_txt_Main_Status = TextWidget.Cast( layoutRoot.FindAnyWidget( "txt_Main_Status" ) );
		// }
		
		m_txt_Main_Status.SetText(txt);
		GetGame().GetCallQueue( CALL_CATEGORY_SYSTEM ).CallLater( this.SetStatusNull, 1500, false );
	}
	
	void SetStatusNull()
	{
		//m_txt_Main_Status = TextWidget.Cast( layoutRoot.FindAnyWidget( "txt_Main_Status" ) );
		m_txt_Main_Status.SetText("");
	}

	override bool OnMouseLeave(Widget w, Widget enterW, int x, int y)
	{
		super.OnMouseLeave(w, enterW, x, y);
		bool ret;
		if ( w == m_MapTab.m_Map_Map ) 
		{
			ret = m_MapTab.OnMouseLeave(w, x, y);
		}
		
		//MapTab HordeCount
		if ( w == m_MapTab.m_editbox_Map_HordeCount ) 
		{
			m_MapTab.MouseLeave(w, enterW, x, y);
			ret = true;
		}
		
		//PlayerTab
		if ( w.GetName().Contains("_Player_") )
		 {
			 m_PlayerTab.MouseLeave(w, enterW, x, y);
			 ret = true;
		 }
		
		//SpawnTab
		if ( w.GetName().Contains("_Spawn_") )
		{
			m_SpawnTab.MouseLeave(w, enterW, x, y);
			ret = true;
		}
		
		//TeleportTab
		 if ( w.GetName().Contains("_Teleport_") )
		 {
			 m_TeleportTab.MouseLeave(w, enterW, x, y);
			 ret = true;
		 }
		
		
		return ret;
	}
	
	override bool OnMouseEnter( Widget w, int x, int y ) 
	{
		
		bool ret;
		if ( w == m_MapTab.m_Map_Map ) 
		{
			ret = m_MapTab.OnMouseEnter(w, x, y);
		}
		
		if ( w == m_MapTab.m_helper_Map_MouseLeave ) 
		{
			ret = m_MapTab.OnMouseEnter(w, x, y);
		}
		
		//MapTab HordeCount
		if ( w == m_MapTab.m_editbox_Map_HordeCount ) 
		{
			m_MapTab.MouseEnter(w, x, y);
			ret = true;
		}
		
		//PlayerTab
		 if ( w.GetName().Contains("_Player_") )
		 {
			 m_PlayerTab.MouseEnter(w, x, y);
			 ret = true;
		 }
		
		//SpawnTab
		if ( w.GetName().Contains("_Spawn_") )
		{
			m_SpawnTab.MouseEnter(w, x, y);
			ret = true;
		}
		
		//TeleportTab
		 if ( w.GetName().Contains("_Teleport_") )
		 {
			 m_TeleportTab.MouseEnter(w, x, y);
			 ret = true;
		 }

		return ret;
	}
	
	
	
	override bool OnClick( Widget w, int x, int y, int button )
	{
		////SpawnTab
		bool ok = false;
		if ( w.GetName().Contains("_spawn_") )
		{
			ok = m_SpawnTab.Click(w, x, y, button);
			return ok;
		}
		
		//TeleportTab
		 if ( w.GetName().Contains("_Teleport_") )
		 {
			 ok = m_TeleportTab.Click(w, x, y, button);
			 return ok;
		 }
		
		//CommandTab
		if ( w.GetName().Contains("_Command_") )
		{
			ok = m_CommandTab.Click(w, x, y, button);
			return ok;
		}
		
		//PlayerTab
		 if ( w.GetName().Contains("_Player_") )
		 {
			 ok = m_PlayerTab.Click(w, x, y, button);
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
				 m_TeleportTab.Focus();
				break;
			}
			case 4:
			{
				m_MapTab.Focus();
				break;
			}
			case 5:
			{
				m_AboutTab.Focus();
				break;
			}
			case 6:
			{
				m_AboutTab2.Focus();
				break;
			}
		}
	}
	
	
	void Back()
	{	
		GetGame().EndOptionsVideo();
		GetGame().GetUIManager().Back();
		
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
	
	
}
ref AdminMenuGui Tomato_AdminMenu;

ref AdminMenuGui GetAdminMenu()
{
    if( !Tomato_AdminMenu )
    {
        Tomato_AdminMenu = new ref AdminMenuGui();
    }

    return Tomato_AdminMenu;
}