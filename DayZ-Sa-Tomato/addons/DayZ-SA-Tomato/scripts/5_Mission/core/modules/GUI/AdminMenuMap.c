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
class AdminMenuGuiMap extends ScriptedWidgetEventHandler
{
	protected Widget						m_Root;

protected MapWidget m_Map_Map;
	
	protected AdminMenuGui					m_Menu;
	
	protected ref map<int, ref Param2<string, string>> m_TextMap;
	
	void AdminMenuGuiMap( Widget parent, AdminMenuGui menu )
	{
		GetDayZGame().Event_OnRPC.Insert( this.ReceiveRPC );
		m_Root					= GetGame().GetWorkspace().CreateWidgets( "com\\DayZ-SA-Tomato\\scripts\\5_Mission\\core\\modules\\GUI\\Layouts\\Admin_Map.layout", parent );
		
		m_Menu						= menu;
		m_Map_Map	= MapWidget.Cast( m_Root.FindAnyWidget( "Map" ) );
		GetGame().RPCSingleParam( NULL, M_RPCs.M_Admin_Menu_Map_Player_Request, new Param1<string>(""), false, NULL );

		
		{
			//GetMarkers();
			/*
			m_Map_Map.AddUserMark("2681 4.7 1751", "Lalal", ARGB(255,255,0,0), "\\dz\\gear\\navigation\\data\\map_tree_ca.paa");
			m_Map_Map.AddUserMark("2683 4.7 1851", "Lala2", ARGB(255,0,255,0), "\\dz\\gear\\navigation\\data\\map_bunker_ca.paa");
			m_Map_Map.AddUserMark("2670 4.7 1651", "Lala3", ARGB(255,0,0,255), "\\dz\\gear\\navigation\\data\\map_busstop_ca.paa"); */
		}
	}
	
	void ~AdminMenuGuiMap()
	{
	}
	
	void Focus()
	{
		
	}
	
	void Message( string txt ) 
	{
        GetGame().GetMission().OnEvent(ChatMessageEventTypeID, new ChatMessageEventParams(0, "", txt, ""));
	}
	
	void ReceiveRPC( PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx ) 
	{
		switch(rpc_type)
		{
			
			case M_RPCs.M_Admin_Menu_Map_Player:
				string PosName;
				vector Pos1;	//Vector Postition
				ctx.Read(PosName);
				ctx.Read(Pos1);
					if ( GetGame().IsServer() ) 
						{
							
						}	
					if ( GetGame().IsClient() && GetGame().IsMultiplayer() ) 
						{
							AddPlayerMarker(PosName, Pos1);
						}
			break;
		}
	}
			
	
	void AddPlayerMarker(string name, vector pos)
	{
		m_Map_Map.AddUserMark(pos, name, ARGB(255,255,0,0), "\\dz\\gear\\navigation\\data\\map_tree_ca.paa");
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
	
	
}
