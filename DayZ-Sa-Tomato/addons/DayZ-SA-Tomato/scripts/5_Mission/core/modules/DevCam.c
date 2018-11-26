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
class DevCam 
{
	void DevCam() 
	{
		GetDayZGame().Event_OnRPC.Insert( this.ReceiveRPC );
	}

	void ReceiveRPC( PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx ) 
	{
		if ( rpc_type == M_RPCs.M_SET_CAM ) 
		{
			if ( GetGame().IsServer() ) 
			{
				Print( " receive rpc dev cam is server");

				ref PlayerBase player = GetServerMission().GetPlayerFromIdentity( sender );

				Param2< bool, vector > camParams;
				ctx.Read( camParams );

				bool spectating = camParams.param1;
				vector pos = camParams.param2;
				if ( GetServerMission().IsAdmin( sender.GetName(), sender.GetPlainId() ) ) 
				{
					if ( spectating ) 
					{
						player.SetPosition( pos );
						SetFreezePlayer( player, false );
						GetGame().SelectPlayer( sender, player );
					} 
					else 
					{
						SetFreezePlayer( player, true );
						GetGame().SelectSpectator( sender, "DayZSpectator", GetServerMission().GetPlayerFromIdentity( sender ).GetPosition() );
					}
				}
			}
			if ( GetGame().IsClient() && GetGame().IsMultiplayer() ) 
			{ // test if setting camera works on client side. instead of server side ^
				GetPlayer().MessageStatus("Toggle Free cam");
			}

		}
	}

	void SendRPC( bool isSpectating, vector toPos ) 
	{
		Print("Send Cam RPC");
		GetGame().RPCSingleParam( NULL, M_RPCs.M_SET_CAM, new Param2< bool, vector >( isSpectating, toPos ), false, NULL );
	}
}