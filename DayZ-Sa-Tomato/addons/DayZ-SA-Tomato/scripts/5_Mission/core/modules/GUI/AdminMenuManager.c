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
	static ref map<string, vector> m_PlayerLocations;
	
	void ~AdminMenuManager()
	{
		
	}	
	
	void AdminMenuManager()
	{
		m_PlayerLocations  = new map<string, vector>; //name of town, pos
	}
	void Teleport() 
	{
		if (Config_Teleport)
		{
			GetGame().RPCSingleParam( NULL, M_RPCs.M_TELEPORT, new Param1<vector>( GetCursorPos() ), false, NULL );
		}
	}
	
	void CamTeleport( bool isSpectating, vector toPos ) 
	{
		if (Config_Cam)
		{
			Print("Send Cam RPC");
			GetGame().RPCSingleParam( NULL, M_RPCs.M_SET_CAM, new Param2< bool, vector >( isSpectating, toPos ), false, NULL );
		}
	}
	
	void MenuOpen() 
	{
		GetGame().RPCSingleParam( NULL, M_RPCs.M_Admin_Menu, new Param1<vector>( GetCursorPos() ), false, NULL );
	}
	
}