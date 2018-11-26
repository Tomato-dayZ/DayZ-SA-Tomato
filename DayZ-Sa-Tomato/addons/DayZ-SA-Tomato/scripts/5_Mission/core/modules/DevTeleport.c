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
class DevTeleport
{
	void DevTeleport() 
	{
		GetDayZGame().Event_OnRPC.Insert( this.ReceiveRPC );
	}

	void ReceiveRPC( PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx ) 
	{
		if ( rpc_type == M_RPCs.M_TELEPORT ) 
		{
			vector positionToTeleport;

			Param1<vector> vectorParam;
			ctx.Read( vectorParam );

			positionToTeleport = vectorParam.param1;

			if ( GetGame().IsServer() ) 
			{
				ref PlayerBase player = GetServerMission().GetPlayerFromIdentity( sender );
				// permission check - server mission file
				// if has permissions send message back to client
				if ( GetServerMission().IsAdmin( sender.GetName(), sender.GetPlainId()) 
				{
					player.SetPosition( positionToTeleport ); //set player position on server side

					GetGame().RPCSingleParam( NULL, M_RPCs.M_TELEPORT, vectorParam, false, NULL );
				}
			}

			if ( GetGame().IsClient() && GetGame().IsMultiplayer() ) 
			{
				//GetPlayer().SetPosition( positionToTeleport ); //client side
				GetPlayer().MessageStatus( "Teleported ");
			}
		}
	}

	void SendRPC() 
	{
		GetGame().RPCSingleParam( NULL, M_RPCs.M_TELEPORT, new Param1<vector>( GetCursorPos() ), false, NULL );
	}
}