	/*
	DayZ SA Tomato Gui Admin tool for DayZ Standalone. Contact DayZ-SA-Tomato@Primary-Network.de
	Copyright (C) 2018  DayZ-SA-Tomato
	
	This file is part of DayZ SA Tomato.
	Originally from DayZCommunityOfflineMode
	Link : https://github.com/Arkensor/DayZCommunityOfflineMode
	
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

				ref PlayerBase player = PlayerBase.Cast(GetServerMission().GetPlayerFromIdentity( sender ));

				Param3< bool, vector, bool > camParams;
				ctx.Read( camParams );

				bool spectating = camParams.param1;
				vector pos = camParams.param2;
				if ( GetFileHandler().HasPermission("Admin", sender) ) 
				{
					if ( spectating ) 
					{
						if(!camParams.param3)
						{
							SetFreezePlayer( player, false );
							GetGame().SelectPlayer( sender, player );
							return;
						}
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
			}

		}
		
		if ( rpc_type == M_RPCs.M_SET_CAM_Spectate ) 
		{
			Print("rpc spec");
			if ( GetGame().IsServer() ) 
			{
				array<Man> players = new array<Man>;
				GetGame().GetPlayers( players );
				PlayerIdentity selectedIdentity;
				PlayerBase selectedPlayer;
				player = PlayerBase.Cast(GetServerMission().GetPlayerFromIdentity( sender ));

				Param4< bool, string, bool, vector > specParams;
				ctx.Read( specParams );

				bool spectatingnew = specParams.param1;
				
				if ( GetFileHandler().HasPermission("Admin", sender) ) 
				{
					for ( int a = 0; a < players.Count(); ++a )
						{
							selectedPlayer = PlayerBase.Cast(players.Get(a));
							selectedIdentity = NULL;
							if ( selectedPlayer.GetIdentity().GetName() == specParams.param2 )
							{
								selectedIdentity = selectedPlayer.GetIdentity();
								pos = GetServerMission().GetPlayerFromIdentity( selectedIdentity ).GetPosition()
								break;
							}
						}
						
						if(selectedIdentity == NULL) {return;}
					
					if ( spectatingnew ) 
					{
						Print("Stop spec");
						if(!specParams.param3)
						{
							SetFreezePlayer( player, false );
							GetGame().SelectPlayer( sender, player );
							return;
						}
						
						player.SetPosition( specParams.param4 );
						SetFreezePlayer( player, false );
						GetGame().SelectPlayer( sender, player );
					} 
					else 
					{
						Print("Start Spec " + selectedIdentity.GetName());
						SetFreezePlayer( player, true );
						GetGame().SelectSpectator( sender, "DayZSpectator", pos );
					}
				}
			}
			if ( GetGame().IsClient() && GetGame().IsMultiplayer() ) 
			{ // test if setting camera works on client side. instead of server side ^
			}

		}
	}

	void SendRPC( bool isSpectating, vector toPos ) 
	{
		Print("Send Cam RPC");
		GetGame().RPCSingleParam( NULL, M_RPCs.M_SET_CAM, new Param2< bool, vector >( isSpectating, toPos ), false, NULL );
	}
}
