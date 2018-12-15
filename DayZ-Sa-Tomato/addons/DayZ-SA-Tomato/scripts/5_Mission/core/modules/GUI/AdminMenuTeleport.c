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
	ref AdminMenuManager adminMenuManager;
	protected EditBoxWidget m_Text_Teleport_Loacation_Name;		
	static ref map<string, string> m_TeleportLocations;
	static ref map<int, string> m_TeleportLocations_old;
	TextListboxWidget m_List_Teleport_Location;
	
	
	void AdminMenuGuiTeleport( Widget parent, AdminMenuGui menu )
	{
		
		m_Root					= GetGame().GetWorkspace().CreateWidgets( "com\\DayZ-SA-Tomato\\scripts\\5_Mission\\core\\modules\\GUI\\Layouts\\Admin_Teleport.layout", parent );
		adminMenuManager = new AdminMenuManager(); 
		m_Menu						= menu;
		GetDayZGame().Event_OnRPC.Insert( this.ReceiveRPC );
		m_TeleportLocations  = new map<string, string>;
		m_TeleportLocations_old  = new map<int, string>;
		m_List_Teleport_Location = TextListboxWidget.Cast( m_Root.FindAnyWidget( "List_Teleport_Location" ) );
		m_Text_Teleport_Loacation_Name = EditBoxWidget.Cast( m_Root.FindAnyWidget( "Text_Teleport_Loacation_Name" ) );
		m_btn_Teleport_Teleport = ButtonWidget.Cast( m_Root.FindAnyWidget( "btn_Teleport_Teleport" ) );
		m_btn_Teleport_Reload = ButtonWidget.Cast( m_Root.FindAnyWidget( "btn_Teleport_Reload" ) );
		m_btn_Teleport_Add_Location = ButtonWidget.Cast( m_Root.FindAnyWidget( "btn_Teleport_Add_Location" ) );
		
		m_List_Teleport_Location.ClearItems();
		//TpLocations;
		GetGame().RPCSingleParam( NULL, M_RPCs.M_Admin_Menu_Teleport_List_Request, new Param1<string>(""), false, NULL );
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
				string TpDest;
				
				m_TeleportLocations.Find(TpLocation, TpDest);
				Print("TpLocation : " + TpLocation + " Tp Dest : " + TpDest);
				//GetGame().RPCSingleParam( NULL, M_RPCs.M_Admin_Menu_TpMeToPos, new Param1<string>(TpDest.ToString()), false, NULL );
				ScriptRPC TListDst = new ScriptRPC();
				TListDst.Write(TpDest);
				TListDst.Send(NULL, M_RPCs.M_Admin_Menu_TpMeToPos, false, NULL);
				return true;
			}
			
			if( ( w == m_btn_Teleport_Reload ) )
			{
				m_TeleportLocations.Clear();
				m_List_Teleport_Location.ClearItems();
				GetGame().RPCSingleParam( NULL, M_RPCs.M_Admin_Menu_Teleport_List_Request, new Param1<string>(""), false, NULL );
			}
			
			if( ( w == m_btn_Teleport_Add_Location ) )
			{
				
				
				m_List_Teleport_Location.ClearItems();
				GetGame().RPCSingleParam( NULL, M_RPCs.M_Admin_Menu_Teleport_List_Request, new Param1<string>(""), false, NULL );
			}
		}
		return true;
	}
	
	void ~AdminMenuGuiTeleport()
	{
		m_List_Teleport_Location.ClearItems();
	}
	
	void Focus()
	{
		
	}
	
	void AddLocationToFile(string LocationName)
	{
		
	}
	override bool OnFocus( Widget w, int x, int y )
	{
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
	}
	bool stop = false;
	
	void ReceiveRPC( PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx ) 
	{
		int ListCount = 0;
		
		switch(rpc_type)
		{
			
			case M_RPCs.M_Admin_Menu_Teleport_List:
			string PosName;
			vector Pos1;	//Vector Postition
			// ctx.Read(PosName);
			// ctx.Read(Pos1);
			ctx.Read(m_TeleportLocations_old);			
			//ctx.Read(m_TeleportLocations);
			
				if ( GetGame().IsServer() ) 
					{
						
					}	
				if ( GetGame().IsClient() && GetGame().IsMultiplayer() ) 
					{
						
						for (int i = 0; i < m_TeleportLocations_old.Count(); ++i)
						{
							ListCount ++;
							string save;
							string a =";";
							vector v;
							TStringArray strs = new TStringArray;
							save = m_TeleportLocations_old.GetElement(i);
							save.Split(a, strs );
							v = strs.Get(1).ToVector();
							string Lname = strs.Get(0);
							if (m_TeleportLocations.Contains(Lname))
							{
								return;
							}
							m_TeleportLocations.Insert(Lname, strs.Get(1)); //int Name, posvector
							m_List_Teleport_Location.AddItem( Lname, NULL, 0 );
							Print("SendTeleportList Number : " + i + " Name : " + Lname + "Pos : " + strs.Get(1));
						}
						// Print("Adding : PosName : " + PosName + " Pos1 : " + Pos1);
						// m_TeleportLocations.Insert(PosName, Pos1); //int Name, posvector
						// m_List_Teleport_Location.AddItem( PosName, NULL, 0 ); 
					}
			break;
		}
	}
	
	// void PlayerSelect()
	// {
		// array<Man> players = new array<Man>;
		// GetGame().GetPlayers( players );
		// PlayerBase selectedPlayer;
		// PlayerIdentity selectedIdentity;
		// for ( int a = 0; a < players.Count(); ++a )
			// {
				// selectedPlayer = players.Get(a);
				// selectedIdentity = selectedPlayer.GetIdentity();
				// if ( selectedIdentity.GetName() == GetCurrentSelection() )
				// {
					// GetGame().RPCSingleParam( NULL, M_RPCs.M_Admin_Menu_Player_Health_Request, new Param1<PlayerBase>(selectedPlayer), false, NULL );
					// GetGame().RPCSingleParam( NULL, M_RPCs.M_Admin_Menu_Player_Stamina_Request, new Param1<string>(selectedIdentity.GetName()), false, NULL );
				// }
			// }
	// }
	
	void PlayerList()
	{
		
		// m_PlayerList.ClearItems();
		// array<Man> players = new array<Man>;
		// GetGame().GetPlayers( players );
		// for (int i = 0; i < players.Count(); ++i)
			// {
				// string msg = "AdminMenuPlayer - PlayerList() Adding " + players.Get(i).GetIdentity().GetName() + " To List";
				// GetGame().RPCSingleParam( NULL, M_RPCs.M_Admin_Menu_Log_Info, new Param1<string>( msg ), false, NULL );
				// m_PlayerList.AddItem( players.Get(i).GetIdentity().GetName(), NULL, 0 );  
			// }
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
	
	void Message( string txt ) 
	{
        GetGame().GetMission().OnEvent(ChatMessageEventTypeID, new ChatMessageEventParams(0, "", txt, ""));
	}
	
	
	
}
