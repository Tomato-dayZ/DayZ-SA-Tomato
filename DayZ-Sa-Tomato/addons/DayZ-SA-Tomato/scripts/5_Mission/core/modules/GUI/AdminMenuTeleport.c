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
class AdminMenuGuiTeleport extends ScriptedWidgetEventHandler
{
	
	protected Widget						m_Root;
	

	
	protected AdminMenuGui					m_Menu;
	
	protected ref map<int, ref Param2<string, string>> m_TextMap;
	protected ButtonWidget m_btn_Teleport_Teleport;
	protected ButtonWidget m_btn_Teleport_Reload;
	protected ButtonWidget m_btn_Teleport_Add_Location;
	protected ButtonWidget m_btn_Teleport_Spawn_Horde;
	//ref AdminMenuManager adminMenuManager;
	EditBoxWidget m_Text_Teleport_Loacation_Name;		
	EditBoxWidget m_editbox_Teleport_HordeCount;		
	static ref map<string, string> m_TeleportLocations;
	static ref map<int, string> m_TeleportLocations_old;
	TextListboxWidget m_List_Teleport_Location;
	ref array<string> TLoacations;
	ref array<vector> TPos;
	ref HordeModule m_HordeModule;
	//ref AdminMenuManager AMenuM;

	void AdminMenuGuiTeleport( Widget parent, AdminMenuGui menu )
	{
		
		m_Root					= GetGame().GetWorkspace().CreateWidgets( "com\\DayZ-SA-Tomato\\scripts\\5_Mission\\core\\modules\\GUI\\Layouts\\Admin_Teleport.layout", parent );
		//adminMenuManager = new AdminMenuManager();
		m_HordeModule = new ref HordeModule();
		m_Menu						= menu;
		GetDayZGame().Event_OnRPC.Insert( this.ReceiveRPC );
		m_TeleportLocations  = new map<string, string>;
		m_TeleportLocations_old  = new map<int, string>;
		m_List_Teleport_Location = TextListboxWidget.Cast( m_Root.FindAnyWidget( "List_Teleport_Location" ) );
		m_Text_Teleport_Loacation_Name = EditBoxWidget.Cast( m_Root.FindAnyWidget( "Text_Teleport_Loacation_Name" ) );
		m_editbox_Teleport_HordeCount = EditBoxWidget.Cast( m_Root.FindAnyWidget( "editbox_Teleport_HordeCount" ) );
		m_btn_Teleport_Teleport = ButtonWidget.Cast( m_Root.FindAnyWidget( "btn_Teleport_Teleport" ) );
		m_btn_Teleport_Reload = ButtonWidget.Cast( m_Root.FindAnyWidget( "btn_Teleport_Reload" ) );
		m_btn_Teleport_Add_Location = ButtonWidget.Cast( m_Root.FindAnyWidget( "btn_Teleport_Add_Location" ) );
		m_btn_Teleport_Spawn_Horde = ButtonWidget.Cast( m_Root.FindAnyWidget( "btn_Teleport_Spawn_Horde" ) );
		//m_List_Teleport_Location.ClearItems();
		//TpLocations;
		// for ( int i = 0; i < m_Root.Locations.Count(); i++ )
		// {
			// m_List_Teleport_Location.AddItem( GetAdminMenu().Locations[i], NULL, 0 );
		// }
		
		Print("Request Data");
		
		GetGame().RPCSingleParam( NULL, M_RPCs.M_Admin_Menu_Teleport_RequestData, new Param1<string>(""), false, NULL );
	
	}
	
	void MouseLeave(Widget w, Widget enterW, int x, int y)
	{
		if ( w == m_Text_Teleport_Loacation_Name ) 
		{
			GetAdminMenuManager().CanClose = true;
		}
		
		if ( w == m_editbox_Teleport_HordeCount ) 
		{
			GetAdminMenuManager().CanClose = true;
		}
	}
	
	void MouseEnter(Widget w, int x, int y )
	{
		if ( w == m_Text_Teleport_Loacation_Name ) 
		{
			GetAdminMenuManager().CanClose = false;
		}
		
		if ( w == m_editbox_Teleport_HordeCount ) 
		{
			GetAdminMenuManager().CanClose = false;
		}
	}
	
	void DeleteTeleportLocation()
	{
		m_List_Teleport_Location.ClearItems();
	}
	
	int GetHordeCount() 
	{
		return m_editbox_Teleport_HordeCount.GetText().ToInt();
	}
	
	void AddTeleportLocation(string name)
	{
		m_List_Teleport_Location.AddItem( name, NULL, 0 );
	}
	void LogD(string s)
	{
		GetGame().RPCSingleParam( NULL, M_RPCs.M_Admin_Menu_Log_Debug, new Param1<string>( s ), false, NULL );
	}
	bool Click(Widget w, int x, int y, int button)
	{
		
		PlayerBase player = PlayerBase.Cast( GetGame().GetPlayer() );
		string TpLocation = GetCurrentSelection();
		if (player)
		{
			if( ( w == m_btn_Teleport_Teleport ) )
			{
				for (int t = 0; t < GetFileHandler().RootTeleport.Children.Count(); ++t)
						{
							if(GetFileHandler().RootTeleport.Children[t].LocationName == TpLocation)
							{
								ScriptRPC TListDst = new ScriptRPC();
								TListDst.Write( GetFileHandler().RootTeleport.Children[t].LocationPos[0] );
								TListDst.Write( GetFileHandler().RootTeleport.Children[t].LocationPos[2] );
								TListDst.Send(NULL, M_RPCs.M_Admin_Menu_TpMeToPosVec, false, NULL);

							}
						}
			}
			
			if( ( w == m_btn_Teleport_Reload ) )
			{
				GetGame().RPCSingleParam( NULL, M_RPCs.M_Admin_Menu_Teleport_RequestData, new Param1<string>(""), false, NULL );
			}
			
			if( ( w == m_btn_Teleport_Add_Location ) )
			{
				string text =  m_Text_Teleport_Loacation_Name.GetText();
				SendToFile(text);
				GetGame().RPCSingleParam( NULL, M_RPCs.M_Admin_Menu_Teleport_RequestData, new Param1<string>(""), false, NULL );
			}
			
			if( ( w == m_btn_Teleport_Spawn_Horde ) )
			{
				int HCount = GetHordeCount();
				for (t = 0; t < GetFileHandler().RootTeleport.Children.Count(); ++t)
						{
							if(GetFileHandler().RootTeleport.Children[t].LocationName == TpLocation)
							{
								m_HordeModule.Spawn(GetFileHandler().RootTeleport.Children[t].LocationPos, GetHordeCount(), 50, GetCurrentSelection())
							}
						}			
			}
		}
		return true;
		
	}
	void SendToFile(string name)
	{
		ScriptRPC Adding = new ScriptRPC();
		Adding.Write(name);
		Adding.Send(NULL, M_RPCs.M_Admin_Menu_Teleport_Write_Pre, false, NULL);
	}
	void ~AdminMenuGuiTeleport()
	{
		
	}
	
	void Focus()
	{
		
	}
	
	void AddLocationToFile(string LocationName)
	{
		
	}
	
	override bool OnFocus( Widget w, int x, int y )
	{
		/*
		if( m_Menu )
			m_Menu.OnFocus( w, x, y );
		if( w )
		{
			Param2<string, string> p = m_TextMap.Get( w.GetUserID() );
			if( p )
			{
				return true;
			}
		}

		return ( w != null );
		*/
	}
	bool stop = false;
	
	
	
	void ReceiveRPC( PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx ) 
	{
		
		int ListCount = 0;
		ref array<string> TLoacations = new ref array< string >;
		ref array<vector> TPos = new ref array< vector >;
		PlayerBase Admin;
		switch(rpc_type)
		{
			case M_RPCs.M_Admin_Menu_Teleport_ReciveData:
			Print("Data Recived");
				ref array<string> TpName = new ref array< string >;	
				ref array<vector> TpPos = new ref array< vector >;	
				ctx.Read(TpName);
				ctx.Read(TpPos);
				Print("Data Count = " + TpName.Count())
					if ( GetGame().IsServer() ) 
						{
							
						}	
					if ( GetGame().IsClient() && GetGame().IsMultiplayer() ) 
						{
							m_List_Teleport_Location.ClearItems();
						for ( int i = 0; i < TpName.Count(); i++ )
						{
							TLoacations.Insert(TpName[i])
							TPos.Insert(TpPos[i])
							m_List_Teleport_Location.AddItem( TLoacations[i], NULL, 0 );
							Print("Client - Created Child with name = " + TpName[i]);
							GetFileHandler().RootTeleport.AddChilds(TpName[i], TpPos[i])
						}
						//Loadarray();
						}
			break;
		}
		
	}
	
	string GetCurrentSelection()
	{
		if ( m_List_Teleport_Location.GetSelectedRow() != -1 )
		{
			string result;
			m_List_Teleport_Location.GetItemText( m_List_Teleport_Location.GetSelectedRow(), 0, result );
			return result;
		}

		return "";
	}
	
	// void Message( string txt ) 
	// {
        // GetGame().GetMission().OnEvent(ChatMessageEventTypeID, new ChatMessageEventParams(0, "", txt, ""));
	// }
	
	
	
}
