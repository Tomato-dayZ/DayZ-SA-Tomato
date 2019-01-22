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
class AdminMenuManager
{
	
	static bool Config_Teleport = false;
	static bool Config_Cam = false;
	static bool Spectate = false;
	static string SpectatePlayer;
	static bool Config_Map_Teleport = false;
	static bool Config_Map_Horde = false;
	static bool CanClose = true;
	//ref AdminMenuMessage m_adMenuMessage;
	static string Version = "Version : 1.30";
	static ref map<string, vector> m_PlayerLocations;
	static ref map<int, string> m_TeleportLocations;
	protected string m_TeleportLocationsPath = "$CurrentDir:\\DayZ-Sa-Tomato\\Config\\List\\TeleportLocation.txt";
	void ~AdminMenuManager()
	{
		// GetGame().GetCallQueue( CALL_CATEGORY_SYSTEM ).Remove( this.MessageClose );
	}	
	
	void AdminMenuManager()
	{
		m_PlayerLocations  = new map<string, vector>; 
		m_TeleportLocations  = new map<int, string>;
		//LoadTeleportLocations();
		// GetGame().GetCallQueue( CALL_CATEGORY_SYSTEM ).CallLater( this.MessageClose, 1000, true );
	}
	
	void Teleport() 
	{
		if (Config_Teleport)
		{
			GetGame().RPCSingleParam( NULL, M_RPCs.M_TELEPORT, new Param1<vector>( GetCursorPos() ), false, NULL );
		}
	}
	
	void Map_Teleport() 
	{
		if (Config_Teleport)
		{
			GetGame().RPCSingleParam( NULL, M_RPCs.M_TELEPORT, new Param1<vector>( GetCursorPos() ), false, NULL );
		}
	}
	
	bool IsSpectate()
	{
		return Spectate;
	}
	
	void SetSpectate()
	{
		Spectate = !Spectate;
	}
	
	void CamSpectate( bool isSpectating, string PlayerName, bool tp, vector posi, bool enable = true)	
	{
		if(enable)
		{
			//TL().player("enable");
			SpectatePlayer = PlayerName;
			GetGame().RPCSingleParam( NULL, M_RPCs.M_SET_CAM_Spectate, new Param4< bool, string, bool, vector >( Spectate, SpectatePlayer, tp, posi ), false, NULL );
		}else
		{
			//TL().player("not Enable");
			GetGame().RPCSingleParam( NULL, M_RPCs.M_SET_CAM_Spectate, new Param4< bool, string, bool, vector >( Spectate, SpectatePlayer, tp, posi ), false, NULL );
			SpectatePlayer = "";
		}
		
	}
	
	void CamTeleport( bool isSpectating, vector toPos, bool tp = true ) 
	{
		if (Config_Cam)
		{
			GetGame().RPCSingleParam( NULL, M_RPCs.M_SET_CAM, new Param3< bool, vector, bool >( isSpectating, toPos, tp ), false, NULL );
		}
	}
	
	void MenuOpen() 
	{
		GetGame().RPCSingleParam( NULL, M_RPCs.M_Admin_Menu, new Param1<string>( "" ), false, NULL );
	}
	
	void MessageClose()
	{
		GetGame().GetMission().OnEvent(ChatMessageEventTypeID, new ChatMessageEventParams(0, "", "Should Close", ""));
		g_Game.GetUIManager().CloseMenu(7001);
	}
	
	void MessageMenu(string MenuMessage)
	{
		UIScriptedMenu adminMenuMessage = NULL;
		adminMenuMessage = new AdminMenuMessage(MenuMessage);
		
		if ( g_Game.GetUIManager().IsMenuOpen(7001) ) 
		{ 
			adminMenuMessage.Close();
			g_Game.GetUIManager().ShowScriptedMenu( adminMenuMessage, NULL );
		}else{
			g_Game.GetUIManager().ShowScriptedMenu( adminMenuMessage, NULL );
		}
	}
	
	void MessageOpen(PlayerIdentity ident, string msg)
	{
		GetGame().RPCSingleParam( NULL, M_RPCs.M_Admin_Menu_MessageBox, new Param1<string>( msg ), false, ident );
	}
	
	void SendTeleportList(PlayerIdentity admin)
	{
		
		string save;
		string a =";";
		vector v;
		
		
		ScriptRPC TList = new ScriptRPC();
		TList.Write(m_TeleportLocations);
		TList.Send(NULL, M_RPCs.M_Admin_Menu_Teleport_List, false, admin);
		
		
		
	}
	void LoadTeleportLocations(PlayerIdentity admin)
	{
		m_TeleportLocations.Clear();
		FileHandle TpList = OpenFile(m_TeleportLocationsPath, FileMode.READ);
		if (TpList != 0)
		{
			string a =";";
			int i = 0;
			string line_content = "";
			while ( FGets(TpList,line_content) > 0 )
			{
				TStringArray strs = new TStringArray;
				m_TeleportLocations.Insert(i,line_content); //int Name, posvector
				i++;
			}
			CloseFile(TpList);
			SendTeleportList(admin);
		}
	}
	
	
		
	
	
	void AddTeleportLocations()
	{
		
	}
	
}

ref AdminMenuManager Tomato_AdminMenuManager;

ref AdminMenuManager GetAdminMenuManager()
{
    if( !Tomato_AdminMenuManager )
    {
        Tomato_AdminMenuManager = new ref AdminMenuManager();
    }

    return Tomato_AdminMenuManager;
}