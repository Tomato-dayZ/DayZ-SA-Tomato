		/*
	DayZ SA Tomato Gui Admin tool for DayZ Standalone. Contact DayZ-SA-Tomato@Primary-Network.de
	Copyright (C) 2018  DayZ-SA-Tomato
	
	This file is part of DayZ SA Tomato, 
	however this File is Execludet from  GNU GENERAL PUBLIC LICENSE
	Version 3, 29 June 2007 since it is 
	
	Originally from DayZ-CommunityOnlineTools
	Link : https://github.com/Jacob-Mango/DayZ-CommunityOnlineTools
	Created by Jacob-Mango
	and Published under license (CC BY SA 4.0) http://creativecommons.org/licenses/by-sa/4.0/ 
    which means this file is under CC BY SA 4.0) http://creativecommons.org/licenses/by-sa/4.0/ Licence.
	*/
class PlayerModule
{
    
	void PlayerModule()
    {
		Print("PlayerModule Init");
        // FileHandler().RegisterPlayerConfig( "Menu.Admin" );
        
         GetFileHandler().RegisterPermission( "Admin" );
         GetFileHandler().RegisterPermission( "DisableStamina" );
         GetFileHandler().RegisterPermission( "Godmode" );
		 
		//GetDayZGame().Event_OnRPC.Insert( this.ReceiveRPC );
    }

    void ~PlayerModule()
    {
    }

	
	void ReceiveRPC( PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx ) 
	{
	PlayerBase Admin;
	PlayerIdentity AdminIdentity;
	float Dfloat;
	bool Dbool;
	vector Dvector;
	ref array <string> Dstring = new ref array <string>;
	ref array <string> Dstring1 = new ref array <string>;
		switch(rpc_type)
		{
			case M_RPCs.M_Admin_Player_SetHealth:
					ctx.Read(Dfloat);
					ctx.Read(Dstring);
					if ( !FileHandler().HasPermission( "Admin", sender ) )
					return;
					if ( GetGame().IsServer() ) 
						{
								array< ref FPPlayer > players = DeserializePlayersGUID( Dstring );

								for (int i = 0; i < players.Count(); i++ )
								{
									PlayerBase player = players[i].PlayerObject;

									if ( player == NULL ) continue;

									player.SetHealth( "GlobalHealth", "Health", Dfloat );

									//COTLog( sender, "Set health to " + Dfloat + " for " + players[i].GetGUID() );
								}
						}
			break;
			
			case M_RPCs.M_Admin_Player_SetBlood:
					ctx.Read(Dfloat);
					ctx.Read(Dstring);
					if ( !FileHandler().HasPermission( "Admin", sender ) )
					return;
					if ( GetGame().IsServer() ) 
						{
							players = DeserializePlayersGUID( Dstring );

							for (i = 0; i < players.Count(); i++ )
							{
								player = players[i].PlayerObject;

								if ( player == NULL ) continue;

								player.SetHealth( "GlobalHealth", "Blood", Dfloat );

								//COTLog( sender, "Set blood to " + Dfloat + " for " + players[i].GetGUID() );
							}
						}
			break;
			
			case M_RPCs.M_Admin_Player_SetEnergy:
					ctx.Read(Dfloat);
					ctx.Read(Dstring);
					if ( !FileHandler().HasPermission( "Admin", sender ) )
					return;
					if ( GetGame().IsServer() ) 
						{
								players = DeserializePlayersGUID( Dstring );

								for (i = 0; i < players.Count(); i++ )
								{
									player = players[i].PlayerObject;

									if ( player == NULL ) continue;

									player.GetStatEnergy().Set( Dfloat );

									//COTLog( sender, "Set energy to " + Dfloat + " for " + players[i].GetGUID() );
								}	
						}
			break;
			
			case M_RPCs.M_Admin_Player_SetWater:
					ctx.Read(Dfloat);
					ctx.Read(Dstring);
					if ( !FileHandler().HasPermission( "Admin", sender ) )
					return;
					if ( GetGame().IsServer() ) 
						{
							players = DeserializePlayersGUID( Dstring );

							for (i = 0; i < players.Count(); i++ )
							{
								player = players[i].PlayerObject;

								if ( player == NULL ) continue;

								player.GetStatWater().Set( Dfloat );

								//COTLog( sender, "Set water to " + Dfloat + " for " + players[i].GetGUID() );
							}
						}
			break;
			
			case M_RPCs.M_Admin_Player_SetShock:
					ctx.Read(Dfloat);
					ctx.Read(Dstring);
					if ( !FileHandler().HasPermission( "Admin", sender ) )
					return;
					if ( GetGame().IsServer() ) 
						{
							 players = DeserializePlayersGUID( Dstring );

							for (i = 0; i < players.Count(); i++ )
							{
								player = players[i].PlayerObject;

								if ( player == NULL ) continue;

								player.SetHealth( "GlobalHealth", "Shock", Dfloat );

								//COTLog( sender, "Set shock to " + Dfloat + " for " + players[i].GetGUID() );
							}
						}
			break;
			
			case M_RPCs.M_Admin_Player_SetWet:
					ctx.Read(Dfloat);
					ctx.Read(Dstring);
					if ( !FileHandler().HasPermission( "Admin", sender ) )
					return;
					if ( GetGame().IsServer() ) 
						{
							players = DeserializePlayersGUID( Dstring );

							for (i = 0; i < players.Count(); i++ )
							{
								player = players[i].PlayerObject;

								if ( player == NULL ) continue;

								player.GetStatWet().Set( Dfloat );

								//COTLog( sender, "Set wetness to " + Dfloat + " for " + players[i].GetGUID() );
							}
						}
			break;
			
			case M_RPCs.M_Admin_Player_SetShock:
					ctx.Read(Dfloat);
					ctx.Read(Dstring);
					if ( !FileHandler().HasPermission( "Admin", sender ) )
					return;
					if ( GetGame().IsServer() ) 
						{
							players = DeserializePlayersGUID( Dstring );

							for (i = 0; i < players.Count(); i++ )
							{
								player = players[i].PlayerObject;

								if ( player == NULL ) continue;

								player.GetStatHeatComfort().Set( Dfloat );

								//COTLog( sender, "Set heat comfort to " + Dfloat + " for " + players[i].GetGUID() );
							}
						}
			break;
			
			case M_RPCs.M_Admin_Player_SetStamina:
					ctx.Read(Dfloat);
					ctx.Read(Dstring);
					if ( !FileHandler().HasPermission( "Admin", sender ) )
					return;
					if ( GetGame().IsServer() ) 
						{
							players = DeserializePlayersGUID( Dstring );

							for (i = 0; i < players.Count(); i++ )
							{
								player = players[i].PlayerObject;

								if ( player == NULL ) continue;

								player.GetStatStamina().Set( Dfloat );

								//COTLog( sender, "Set stamina to " + Dfloat + " for " + players[i].GetGUID() );
							}
						}
			break;
			
			case M_RPCs.M_Admin_Player_SetHeatComfort:
					ctx.Read(Dfloat);
					ctx.Read(Dstring);
					if ( !FileHandler().HasPermission( "Admin", sender ) )
					return;
					if ( GetGame().IsServer() ) 
						{
							players = DeserializePlayersGUID( Dstring );

							for (i = 0; i < players.Count(); i++ )
							{
								player = players[i].PlayerObject;

								if ( player == NULL ) continue;

								player.GetStatTremor().Set( Dfloat );

								//COTLog( sender, "Set tremor to " + Dfloat + " for " + players[i].GetGUID() );
							}
						}
			break;
			
			case M_RPCs.M_Admin_Player_SetLifeSpanState:
					ctx.Read(Dfloat);
					ctx.Read(Dstring);
					if ( !FileHandler().HasPermission( "Admin", sender ) )
					return;
					if ( GetGame().IsServer() ) 
						{
							players = DeserializePlayersGUID( Dstring );

							for (i = 0; i < players.Count(); i++ )
							{
								player = players[i].PlayerObject;

								if ( player == NULL ) continue;

								if ( Dfloat >= LifeSpanState.BEARD_NONE && Dfloat < LifeSpanState.COUNT )
								{
									player.SetLifeSpanStateVisible( Dfloat );
								}

								//COTLog( sender, "Set beard state to " + Dfloat + " for " + players[i].GetGUID() );
							}
						}
			break;
			
			case M_RPCs.M_Admin_Player_SetBloodyHands:
					ctx.Read(Dbool);
					ctx.Read(Dstring);
					if ( !FileHandler().HasPermission( "Admin", sender ) )
					return;
					if ( GetGame().IsServer() ) 
						{
							players = DeserializePlayersGUID( Dstring );

							for (i = 0; i < players.Count(); i++ )
							{
								player = players[i].PlayerObject;

								if ( player == NULL ) continue;

								player.SetBloodyHands( Dfloat );

								//COTLog( sender, "Set bloody hands to " + Dfloat + " for " + players[i].GetGUID() );
							}
						}
			break;
			
			case M_RPCs.M_Admin_Player_KickTransport:
					ctx.Read(Dstring);
					if ( !FileHandler().HasPermission( "Admin", sender ) )
					return;
					if ( GetGame().IsServer() ) 
						{
							players = DeserializePlayersGUID( Dstring );

							for (i = 0; i < players.Count(); i++ )
							{
								player = players[i].PlayerObject;

								if ( player == NULL ) continue;

								HumanCommandVehicle vehCommand = player.GetCommand_Vehicle();

								if ( vehCommand == NULL ) continue;

								Transport trans = vehCommand.GetTransport();
								
								if ( trans )
								{
									Car caro;
									if ( Class.CastTo(caro, trans) )
									{
										float speed = caro.GetSpeedometer();
										if ( speed <= 8 )
										{
											vehCommand.GetOutVehicle();
										}
										else
										{
											vehCommand.JumpOutVehicle();
										}

										//COTLog( sender, "Kicked " + players[i].GetGUID() + " out of transport" );
									}
								}
							}
						}
			break;
			
			case M_RPCs.M_Admin_Player_RepairTransport:
					ctx.Read(Dstring);
					if ( !FileHandler().HasPermission( "Admin", sender ) )
					return;
					if ( GetGame().IsServer() ) 
						{
							array< Transport > completedTransports = new array< Transport >;

							players = DeserializePlayersGUID( Dstring );

							for (i = 0; i < players.Count(); i++ )
							{
								player = players[i].PlayerObject;

								if ( player == NULL || player.GetTransport() == NULL ) continue;

								Transport transport = player.GetTransport();

								if ( completedTransports.Find( transport ) > -1 )
								{
									ItemBase radiator;

									Class.CastTo( radiator, transport.FindAttachmentBySlotName("CarRadiator") );

									if ( radiator )
									{
										radiator.SetHealth( "", "", 1 );
									}

									transport.SetHealth( "Engine", "", 1 );
									transport.SetHealth( "FuelTank", "", 1 );

									CarScript car = CarScript.Cast( transport );

									if ( car )
									{
										car.Fill( CarFluid.FUEL, car.GetFluidCapacity( CarFluid.FUEL ) );
										car.Fill( CarFluid.OIL, car.GetFluidCapacity( CarFluid.OIL ) );
										car.Fill( CarFluid.BRAKE, car.GetFluidCapacity( CarFluid.BRAKE ) );
										car.Fill( CarFluid.COOLANT, car.GetFluidCapacity( CarFluid.COOLANT ) );
									}

									completedTransports.Insert( transport );

									//COTLog( sender, "Repaired transport for " + players[i].GetGUID() );
								}
							}
						}
			break;
			
			case M_RPCs.M_Admin_Player_TeleportToMe:
					ctx.Read(Dvector);
					ctx.Read(Dstring);
					if ( !FileHandler().HasPermission( "Admin", sender ) )
					return;
					if ( GetGame().IsServer() ) 
						{
							players = DeserializePlayersGUID( Dstring );

							for (i = 0; i < players.Count(); i++ )
							{
								player = players[i].PlayerObject;

								if ( player == NULL ) continue;

								if ( player.GetTransport() != NULL ) continue;

								player.SetPosition( Dvector );

								//COTLog( sender, "Teleported " + players[i].GetGUID() + " to self" );
							}
						}
			break;
			
			case M_RPCs.M_Admin_Player_TeleportMeTo:
					ctx.Read(Dstring);
					if ( !FileHandler().HasPermission( "Admin", sender ) )
					return;
					if ( GetGame().IsServer() ) 
						{
							PlayerBase senderPlayer = PlayerBase.Cast( target );

							if ( senderPlayer == NULL || senderPlayer.GetTransport() != NULL ) return;

							
							players = DeserializePlayersGUID( Dstring );

							if ( players.Count() != 1 ) return;

							player = players[0].PlayerObject;

							if ( player == NULL ) return;

							senderPlayer.SetPosition( player.GetPosition() );

							//COTLog( sender, "Teleported self to " + players[0].GetGUID() );
							
						}
			break;
			
			// case M_RPCs.M_Admin_SpectatePlayer:
					// TODO
					// ctx.Read(Dbool);
					// ctx.Read(Dstring);
					// if ( !FileHandler().HasPermission( "Admin", sender ) )
					// return;
					// if ( GetGame().IsServer() ) 
					// {
						// if ( !Dbool )
						// {
							// GetGame().SelectPlayer( sender, target );
							// GetRPCManager().SendRPC( "COT_Camera", "LeaveCamera", new Param, true, sender );

							// COTLog( sender, "Left spectating/free camera" );
							// return;
						// }

						// array< ref FPPlayer > players = DeserializePlayersGUID( Dstring );

						// if ( players.Count() != 1 ) return;

						// player = players[0].PlayerObject;

						// if ( player == NULL ) return;

						// GetGame().SelectSpectator( sender, "SpectatorCamera", player.GetPosition() );

						// GetGame().SelectPlayer( sender, NULL );

						//GetRPCManager().SendRPC( "COT_Admin", "SpectatePlayer", new Param, true, sender, player );

						// COTLog( sender, "Spectating " + players[0].GetGUID() );
					// }else
					// {
						// if ( GetGame().IsMultiplayer() )
						// {
							// CurrentActiveCamera = COTCamera.Cast( Camera.GetCurrentCamera() );
						// }
						
						// if ( CurrentActiveCamera )
						// {
							// CurrentActiveCamera.SelectedTarget( target );
							// CurrentActiveCamera.SetActive( true );
							// GetPlayer().GetInputController().SetDisabled( true );
						// }
					// }
			// break;
			
			case M_RPCs.M_Admin_Player_GodMode:
					// ctx.Read(Dbool);
					// ctx.Read(Dstring);
					// if ( !FileHandler().HasPermission( "Admin", sender ) )
					// return;
					// if ( GetGame().IsServer() ) 
						// {
							// players = DeserializePlayersGUID( Dstring );

							// for (i = 0; i < players.Count(); i++ )
							// {
								// player = players[i].PlayerObject;

								// if ( player == NULL ) continue;
								//TODO
								// player.SetGodMode( Dvector );
				 
								//COTLog( sender, "Set god mode to " + Dvector + " for " + players[i].GetGUID() );
							// }
						// }
			break;
			
			case M_RPCs.M_Admin_SetConfigs:
					ctx.Read(Dstring1);
					ctx.Read(Dstring);
					if ( !FileHandler().HasPermission( "Admin", sender ) )
					return;
					if ( GetGame().IsServer() ) 
						{
							ref array< string > perms = new ref array< string >;
							perms.Copy( Dstring1 );

							ref array< string > guids = new ref array< string >;
							guids.Copy( Dstring );

							players = DeserializePlayersGUID( Dstring );

							for (i = 0; i < guids.Count(); i++ )
							{
								for ( int k = 0; k < FileHandler().FPPlayers.Count(); k++ )
								{
									ref FPPlayer player1 = FileHandler().FPPlayers[k];
									
									if ( guids[i] == player1.GetGUID() )
									{
										player1.ClearPermissions();

										for ( int j = 0; j < perms.Count(); j++ )
										{
											player1.AddPermission( perms[j] );
										}
										//TODO
										//GetRPCManager().SendRPC( "PermissionsFramework", "UpdatePlayer", new Param1< ref PlayerDataN >( SerializePlayer( player1 ) ), true, player1.IdentityPlayer );
										ScriptRPC Adding = new ScriptRPC();
										Adding.Write(player1);
										Adding.Send(NULL, M_RPCs.M_Admin_Player_UpdatePlayer, true, player1.IdentityPlayer);
										player1.Save();

										//COTLog( sender, "Set and saved permissions for " + players[i].GetGUID() );
									}
								}
							}
						}
			break;
			
			// case M_RPCs.M_Admin_KickPlayer:
					// ctx.Read(Dstring);
					// if ( !FileHandler().HasPermission( "Admin", sender ) )
					// return;
					// if ( GetGame().IsServer() ) 
						// {
							// array< ref FPPlayer > auPlayers = DeserializePlayersGUID( Dstring );

							// for (i = 0; i < auPlayers.Count(); i++ )
							// {
								// auPlayers[i].Kick();
								////COTLog( sender, "Kicked " + auPlayers[i].GetGUID() );
							// }
						// }
			// break;
			
			// case M_RPCs.M_Admin_BanPlayer:
					// ctx.Read(Dstring);
					// if ( !FileHandler().HasPermission( "Admin", sender ) )
					// return;
					// if ( GetGame().IsServer() ) 
						// {
							// auPlayers = DeserializePlayersGUID( Dstring );

							// for (i = 0; i < auPlayers.Count(); i++ )
							// {
								// auPlayers[i].Ban();
								//COTLog( sender, "Banned " + auPlayers[i].GetGUID() );
							// }
						// }
			// break;
			
			// case M_RPCs.M_Admin_SetConfigs:
					// ctx.Read(Dvector);
					// ctx.Read(Dstring);
					// if ( !FileHandler().HasPermission( "Admin", sender ) )
					// return;
					// if ( GetGame().IsServer() ) 
						// {
							
						// }
			// break;
		}
	}
	
}