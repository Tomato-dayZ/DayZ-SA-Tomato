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
class AdminMenuGuiCommands extends ScriptedWidgetEventHandler
{
	protected Widget						m_Root;
	

	
	protected AdminMenuGui					m_Menu;
	CheckBoxWidget m_Config_Teleport;
	CheckBoxWidget m_Config_Cam;
	protected ref map<int, ref Param2<string, string>> m_TextMap;
	
	protected ButtonWidget m_Command_Day;
	protected ButtonWidget m_Command_Night;
	protected ButtonWidget m_Command_Refill;
	protected ButtonWidget m_Command_HealButton;
	protected ButtonWidget m_Command_SpCar;
	protected ButtonWidget m_Command_Cam;
	protected ButtonWidget m_Command_CamTp;
	protected ButtonWidget m_Command_DelObj;
	protected ButtonWidget m_Command_Test;
	protected ref map<string, string> m_TestList;
	protected string m_TestListPath = "$CurrentDir:\\DayZ-SA-Tomato\\Config\\";
	
	ref AdminMenuManager AMenuM;
	
	void AdminMenuGuiCommands( Widget parent, AdminMenuGui menu )
	{
		
		m_Root					= GetGame().GetWorkspace().CreateWidgets( "com\\DayZ-SA-Tomato\\scripts\\5_Mission\\core\\modules\\GUI\\Layouts\\Admin_Commands.layout", parent );
			
		m_Menu						= menu;
		
		m_Config_Teleport	= CheckBoxWidget.Cast( m_Root.FindAnyWidget( "Config_Teleport" ) );
		m_Config_Cam	= CheckBoxWidget.Cast( m_Root.FindAnyWidget( "Config_Cam" ) );
		
		m_Command_HealButton = ButtonWidget.Cast( m_Root.FindAnyWidget( "btn_Command_Heal" ) );
		m_Command_SpCar = ButtonWidget.Cast( m_Root.FindAnyWidget( "btn_Command_SpCar" ) );
		m_Command_Day = ButtonWidget.Cast( m_Root.FindAnyWidget( "btn_Command_Day" ) );
		m_Command_Night = ButtonWidget.Cast( m_Root.FindAnyWidget( "btn_Command_Night" ) );
		m_Command_Refill = ButtonWidget.Cast( m_Root.FindAnyWidget( "btn_Command_Refill" ) );
		m_Command_Cam = ButtonWidget.Cast( m_Root.FindAnyWidget( "btn_Command_Cam" ) );
		m_Command_CamTp = ButtonWidget.Cast( m_Root.FindAnyWidget( "btn_Command_CamTp" ) );
		m_Command_DelObj = ButtonWidget.Cast( m_Root.FindAnyWidget( "btn_Command_DelObj" ) );
		 
		m_Command_Test	= ButtonWidget.Cast( m_Root.FindAnyWidget( "btn_Command_Test" ) );
		
		if (AMenuM.Config_Cam)
		{
			m_Config_Cam.SetChecked(true);
		}else
		{
			m_Config_Cam.SetChecked(false);
		}
		
		if (AMenuM.Config_Teleport)
		{
			m_Config_Teleport.SetChecked(true);
		}else
		{
			m_Config_Teleport.SetChecked(false);
		}
		
	}
	
	bool Click(Widget w, int x, int y, int button)
	{
		PlayerBase player = PlayerBase.Cast( GetGame().GetPlayer() );
        if (player)
		{
			if( ( w == m_Command_HealButton ) )
			{
				GetGame().RPCSingleParam( NULL, M_RPCs.M_Admin_Menu_Heal, new Param1<string>(""), false, NULL );
				return true;
			}
			
			
			if( ( w == m_Command_SpCar ) )
			{
				GetGame().RPCSingleParam( NULL, M_RPCs.M_Admin_Menu_Spawn_Car, new Param1<string>(""), false, NULL );
				return true;
			}
			
			if( ( w == m_Command_Day ) )
			{
				GetGame().RPCSingleParam( NULL, M_RPCs.M_Admin_Menu_Day, new Param1<string>(""), false, NULL );
				return true;
			}
			
			if( ( w == m_Command_Night ) )
			{
				GetGame().RPCSingleParam( NULL, M_RPCs.M_Admin_Menu_Night, new Param1<string>(""), false, NULL );
				return true;
			}
			
			if( ( w == m_Command_Refill ) )
			{
				GetGame().RPCSingleParam( NULL, M_RPCs.M_Admin_Menu_Car_Refill, new Param1<string>(""), false, NULL );
				return true;
			}
			
			if( ( w == m_Command_DelObj ) )
			{
				GetGame().RPCSingleParam( NULL, M_RPCs.M_Admin_Delete_Object, new Param1<Object>(GetCursorObject( 50.0, GetGame().GetPlayer(), 0.01 )), false, NULL );
				return true;
			}
			
			if( ( w == m_Command_Test ) )
			{
				string msg;
				msg = "TestLog";
				//GetGame().RPCSingleParam( NULL, M_RPCs.M_Admin_Menu_TestConf, new Param1<string>( msg ), false, NULL );
				return true;
			}
			return true;
		}
		return false;
	}
	
	static Object GetCursorObject( float distance = 100.0, Object ignore = NULL, float radius = 0.5, Object with = NULL )
	{
    vector rayStart = GetGame().GetCurrentCameraPosition();
    vector rayEnd = rayStart + GetGame().GetCurrentCameraDirection() * distance;

    auto objs = GetObjectsAt( rayStart, rayEnd, ignore, radius, with );

    if( objs.Count() > 0 )
    {
        return objs[ 0 ];
    }

    return NULL;
	}
	
	void Set_Teleport()
	{
		if (AMenuM.Config_Teleport)
		{
			AMenuM.Config_Teleport = false;
		}else
		{
			AMenuM.Config_Teleport = true;
		}
	}
	
	void Set_Cam()
	{
		if (AMenuM.Config_Cam)
		{
			AMenuM.Config_Cam = false;
		}else
		{
			AMenuM.Config_Cam = true;
		}
	}
	
	void ~AdminMenuGuiCommands()
	{
	}
	
	void Focus()
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
	
	void Message( string txt ) 
	{
        GetGame().GetMission().OnEvent(ChatMessageEventTypeID, new ChatMessageEventParams(0, "", txt, ""));
	}
}
