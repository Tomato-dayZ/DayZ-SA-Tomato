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

	MapWidget m_Map_Map;
	ItemPreviewWidget m_helper_Map_MouseLeave;
	//ref AdminMenuManager AMenuM;
	ref HordeModule m_HordeModule;
	protected AdminMenuGui					m_Menu;
	protected bool TpOK = true;
	EditBoxWidget m_editbox_Map_HordeCount;
	protected bool HordeOK = true;
	protected ref map<int, ref Param2<string, string>> m_TextMap;
	protected TextWidget m_Text_Map_Location;
	protected bool PointerMap = false;
	CheckBoxWidget m_Config_Map_Teleport;
	CheckBoxWidget m_Config_Map_Horde;
	
	void AdminMenuGuiMap( Widget parent, AdminMenuGui menu )
	{
		
		GetDayZGame().Event_OnRPC.Insert( this.ReceiveRPC );
		m_HordeModule = new ref HordeModule();
		m_Root					= GetGame().GetWorkspace().CreateWidgets( "com\\DayZ-SA-Tomato\\scripts\\5_Mission\\core\\modules\\GUI\\Layouts\\Admin_Map.layout", parent );
		
		m_Menu						= menu;
		m_Map_Map	= MapWidget.Cast( m_Root.FindAnyWidget( "Map_Map_Main" ) );
		m_helper_Map_MouseLeave	= ItemPreviewWidget.Cast( m_Root.FindAnyWidget( "helper_Map_MouseLeave" ) );
		m_editbox_Map_HordeCount = EditBoxWidget.Cast( m_Root.FindAnyWidget( "editbox_Map_HordeCount" ) );
		m_Text_Map_Location = TextWidget.Cast( m_Root.FindAnyWidget( "Text_Map_Location" ) );
		m_Config_Map_Teleport	= CheckBoxWidget.Cast( m_Root.FindAnyWidget( "Config_Map_Teleport" ) );
		m_Config_Map_Horde	= CheckBoxWidget.Cast( m_Root.FindAnyWidget( "Config_Map_Horde" ) );
		GetGame().RPCSingleParam( NULL, M_RPCs.M_Admin_Menu_Map_Player_Request, new Param1<string>(""), false, NULL );
		
		if (GetAdminMenuManager().Config_Map_Teleport)
		{
			m_Config_Map_Teleport.SetChecked(true);
		}else
		{
			m_Config_Map_Teleport.SetChecked(false);
		}
		
		if (GetAdminMenuManager().Config_Map_Horde)
		{
			m_Config_Map_Horde.SetChecked(true);
		}else
		{
			m_Config_Map_Horde.SetChecked(false);
		}
		
	}
	
	void ~AdminMenuGuiMap()
	{
	}
	
	void Update() 
	{
		if (PointerMap) {
			int X, Y;
			vector Map;
			GetMousePos(X, Y);
			Map = m_Map_Map.ScreenToMap(Vector(X, Y, 0));
			m_Text_Map_Location.SetText("X: " + Map[0] + "  Y: " + Map[2]);

			if (GetAdminMenuManager().Config_Map_Teleport && PointerMap && GetMouseState(MouseState.LEFT) < 0) {
				if (TpOK) {
					TpOK = false;
					// Send tp rpc
					ScriptRPC TListDst = new ScriptRPC();
					TListDst.Write( Map[0] );
					TListDst.Write( Map[2] );
					TListDst.Send(NULL, M_RPCs.M_Admin_Menu_TpMeToPosVec, false, NULL);
				}
			} else {
				if (!TpOK) TpOK = true;
			}
			
			if (GetAdminMenuManager().Config_Map_Horde && PointerMap && GetMouseState(MouseState.LEFT) < 0) { 
				if (HordeOK) {
					HordeOK = false;
					m_HordeModule.Spawn(Map, GetHordeCount())
				}
			} else {
				if (!HordeOK) HordeOK = true;
			}
		}
	}
	
	void MouseEnter(Widget w, int x, int y )
	{
		GetAdminMenuManager().CanClose = false;
	}
	
	void MouseLeave(Widget w, Widget enterW, int x, int y)
	{
			GetAdminMenuManager().CanClose = true;
	}
	
	int GetHordeCount() 
	{
		return m_editbox_Map_HordeCount.GetText().ToInt();
	}
	
	void Set_Map_Teleport()
	{
		if (GetAdminMenuManager().Config_Map_Teleport)
		{
			GetAdminMenuManager().Config_Map_Teleport = false;
		}else
		{
			GetAdminMenuManager().Config_Map_Teleport = true;
		}
	}
	
	void Set_Map_Horde()
	{
		if (GetAdminMenuManager().Config_Map_Horde)
		{
			GetAdminMenuManager().Config_Map_Horde = false;
		}else
		{
			GetAdminMenuManager().Config_Map_Horde = true;
		}
	}
	
	bool OnMouseLeave( Widget w, int x, int y ) 
	{
		if ( w == m_Map_Map ) {
			PointerMap = false;
			return true;
		}
		return false;
	}

	bool OnMouseEnter( Widget w, int x, int y ) {
		if ( w == m_Map_Map ) {
			
			PointerMap = true;
			return true;
		}
		if ( w == m_helper_Map_MouseLeave ) {
			PointerMap = false;
			return true;
		}
		return false;
	}
	
	void Focus()
	{
		
	}
	
	void Message( string txt ) 
	{
        // GetGame().GetMission().OnEvent(ChatMessageEventTypeID, new ChatMessageEventParams(0, "", txt, ""));
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
