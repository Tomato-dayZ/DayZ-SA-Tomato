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
	static ref map<int, string> m_TeleportLocations;
	protected string m_TeleportLocationsPath = "$CurrentDir:\\DayZ-Sa-Tomato\\Config\\List\\TeleportLocation.txt";
	void ~AdminMenuManager()
	{
		
	}	
	
	void AdminMenuManager()
	{
		m_PlayerLocations  = new map<string, vector>; 
		m_TeleportLocations  = new map<int, string>;
		//LoadTeleportLocations();
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
	
	void SendTeleportList(PlayerIdentity admin)
	{
		
		string save;
		string a =";";
		vector v;
		
		
		ScriptRPC TList = new ScriptRPC();
		TList.Write(m_TeleportLocations);
		TList.Send(NULL, M_RPCs.M_Admin_Menu_Teleport_List, false, admin);
		
		
		// for (int i = 0; i < m_TeleportLocations.Count(); ++i)
		// {
			
			
			// TStringArray strs = new TStringArray;
			// save = m_TeleportLocations.GetElement(i);
			// save.Split(a, strs );
			// v = strs.Get(1).ToVector();
			// string Lname = strs.Get(0);
			// Print("SendTeleportList Number : " + i + " Name : " + Lname + "Pos : " + strs.Get(1).ToVector());
			
			
			// ScriptRPC TList = new ScriptRPC();
			// TList.Write(Lname);
			// TList.Write(v);
			// TList.Send(NULL, M_RPCs.M_Admin_Menu_Teleport_List, false, admin);
		
		//}
		
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
				//string.Split(line_content, a, strs );
				//line_content.Split(";", strs)
				//vector v = strs.Get(1).ToVector();
				m_TeleportLocations.Insert(i,line_content); //int Name, posvector
				Print("Adding Number : " + i + " line : " + line_content + " To the Teleport List!");
				i++;
			}
			CloseFile(TpList);
			SendTeleportList(admin);
		}
		Print("TpList = NULL");
	}
	
	
		
	
	
	void AddTeleportLocations()
	{
		
	}
	
}