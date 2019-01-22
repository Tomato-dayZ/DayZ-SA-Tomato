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
class TeleportData
{
	ref array <ref TeleportData> Locations
	string LocationName;
	vector LocationPos;
	ref FileTeleport Parent;
	
	void TeleportData(ref FileTeleport parent = NULL)
	{
		Print("TeleportData");
		
		GetDayZGame().Event_OnRPC.Insert( this.ReceiveRPC );
		Parent = parent
	}
	
	
	void ReceiveRPC( PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx ) 
	{
		PlayerBase Admin;
		switch(rpc_type)
		{
			// case M_RPCs.M_Admin_Menu_Teleport_RequestData:
			// GetFileHandler().LoadTeleport();
					// if ( GetGame().IsServer() ) 
						// {
							// ref array< string > LocationNT = new ref array< string >;
							// ref array< vector > LocationP = new ref array< vector >;
							// PlayerIdentity AdminIdentity;
							// Admin = GetServerMission().IsAdminID(sender.GetName(), sender.GetPlainId());
							// if ( Admin != NULL) 
							// {
								// AdminIdentity = Admin.GetIdentity();
								// for ( int t = 0; t < GetFileHandler().RootTeleport.Children.Count(); t++ )
								// {
									////string name = GetFileHandler().RootTeleport.Children[t].LocationName;
									// vector pos = GetFileHandler().RootTeleport.Children[t].LocationPos;
									// string name = GetFileHandler().RootTeleport.Children[t].LocationName;

									// LocationNT.Insert(name);

									// LocationP.Insert(pos);

								// }
								// Print("Server - Teleport Data Rpc Sent");
								// ScriptRPC TListDst = new ScriptRPC();
									// TListDst.Write(LocationNT);
									// TListDst.Write(LocationP);
									// TListDst.Send(NULL, M_RPCs.M_Admin_Menu_Teleport_ReciveData, false, AdminIdentity);
							// }
						// }
			
					// if ( GetGame().IsClient() && GetGame().IsMultiplayer() ) 
						// {
							
						// }
			// break;
		}
	}
	
	
}
ref TeleportData Tomato_TeleportData;

ref TeleportData GetTeleportData()
{
    if( !Tomato_TeleportData )
    {
        Tomato_TeleportData = new ref TeleportData();
    }

    return Tomato_TeleportData;
}