	/*
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
class AdminMenu //extends UIScriptedMenu
{
	protected ref map<string, vector> m_TPLocations;
	 //ref UIScriptedMenu adminMenuGui;
 //ref AdminMenuGui m_adMenu;
	//ref AdminMenuMessage m_adMenuMessage;
	//ref AdminMenuGuiMap m_map;
	PlayerBase Admin;
	PlayerIdentity AdminIdentity;
	string AdminUID;
	//ref AdminMenuManager AMenuM;
	ref array<Man> m_Players;
	//ref LogHandler m_LogHandler;
	
	
	
	
	void AdminMenu() 
	{
		GetDayZGame().Event_OnRPC.Insert( this.ReceiveRPC );
		//m_LogHandler = new ref LogHandler();
		//adminMenuMain = new AdminMenuMain();
	}
	
	void ~AdminMenu() 
	{
		//delete  AMenuM;
		//delete m_adMenu;
		//delete m_LogHandler;
	}
	
	void Message (string strMessage)
			{
				Param1<string> Msgparam1;
				Msgparam1 = new Param1<string>( strMessage );
				GetGame().RPCSingleParam(Admin, ERPCs.RPC_USER_ACTION_MESSAGE, Msgparam1, true, AdminIdentity);
			}
	
	void ReceiveRPC( PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx ) 
	{
		array<Man> players = new array<Man>;
		GetGame().GetPlayers( players );
		PlayerIdentity selectedIdentity;
		PlayerBase selectedPlayer;
		string strMessage;
		Param1<string> Msgparam;
		string PlayerName;
		string cData;
		ItemBase oItem = NULL;
		PlayerIdentity AdminIdent;
		string status;
		bool ai = false;
		int Count = 0;

		int quantity = 0;
		string text = "";
		
		
		
		switch(rpc_type)
		{

			case (int)M_RPCs.M_Admin_Menu:
				if ( GetGame().IsServer() ) 
				{
					Admin = GetServerMission().IsAdminID(sender.GetName(), sender);
					if ( Admin != NULL) 
					{
						AdminIdentity = Admin.GetIdentity();
						AdminUID 	  = AdminIdentity.GetId();
						GetGame().RPCSingleParam( NULL, M_RPCs.M_Admin_Menu_OK, new Param1<string>( "Test" ), false, AdminIdentity );
					}
				}
			break;
			
			case (int)M_RPCs.M_Admin_Menu_MessageBox:
				Param1<string> MenuMessagep;
				ctx.Read( MenuMessagep );
				string MenuMessage = MenuMessagep.param1;
				if ( GetGame().IsClient() && GetGame().IsMultiplayer() ) 
				{
					//GetAdminMenuManager.MessageMenu(MenuMessage);
					// UIScriptedMenu adminMenuMessage = NULL;
					// adminMenuMessage = new AdminMenuMessage(MenuMessage);
					
					// if ( g_Game.GetUIManager().GetMenu() == NULL ) 
						// { 
							// g_Game.GetUIManager().ShowScriptedMenu( adminMenuGui, NULL );
						// }
						
						// if ( g_Game.GetUIManager().IsMenuOpen(7001) ) 
						// { 
							// g_Game.GetUIManager().CloseMenu(7001);
							// g_Game.GetUIManager().ShowScriptedMenu( adminMenuMessage, NULL );
						// }else{
							// g_Game.GetUIManager().ShowScriptedMenu( adminMenuMessage, NULL );
						// }
				}
			break;
			
			
			
			case (int)M_RPCs.M_Admin_Menu_OK:
				if ( GetGame().IsClient() && GetGame().IsMultiplayer() ) 
				{
					  //UIScriptedMenu adminMenuGui = NULL;
					  //adminMenuGui = new AdminMenuGui();
					  UIScriptedMenu adminMenuGui = NULL;
					  adminMenuGui = new AdminMenuGui();
					 if ( g_Game.GetUIManager().GetMenu() == NULL )
						{ 
							g_Game.GetUIManager().ShowScriptedMenu( adminMenuGui, NULL );
						}
	

						// if ( g_Game.GetUIManager().IsMenuOpen(7000) ) 
					// { 
						// if(!AMenuM.CanClose)
						// {
							// return;
						// }
						
						
						// g_Game.GetUIManager().HideScriptedMenu(adminMenuGui);
						 
						//g_Game.GetUIManager().Back();
						
						// g_Game.GetUIManager().CloseMenu(7000);
						 // g_Game.GetUIManager().CloseAll();
						// delete adminMenuGui;
						//GetGame().GetUIManager().Back();
						
						
					// }else{
						// UIScriptedMenu adminMenuGui = NULL;
						// adminMenuGui = new ref AdminMenuGui();
						// g_Game.GetUIManager().ShowScriptedMenu( adminMenuGui, NULL );
						// AMenuM.CanClose = true;
					// }
				}
			break;
			
			case (int)M_RPCs.M_Admin_Menu_Teleport_Write_Pre:
				if ( GetGame().IsServer()) 
				{
					Print("Pos Pre");
					string PosNamet;		
					ctx.Read(PosNamet);
					Admin = GetServerMission().IsAdminID(sender.GetName(), sender);
					if ( Admin != NULL) 
					{
						vector TLLPos = Admin.GetPosition();
						// ScriptRPC Addingpos = new ScriptRPC();
						// Addingpos.Write(PosNamet);
						// Addingpos.Write(TLLPos);
						// Print("Pos RPC");
						// Addingpos.Send(NULL, M_RPCs.M_Admin_Menu_Teleport_Write, false, NULL);
						GetFileHandler().AddLocation(PosNamet, TLLPos)
					}
				}
			break;
			
			case M_RPCs.M_Admin_Delete_Object:
					Param1<Object> ObjectParam;
					ctx.Read( ObjectParam );
					Object ObJIs = ObjectParam.param1;
				if ( GetGame().IsServer() ) 
				{	
					Admin = GetServerMission().IsAdminID( sender.GetName(), sender);
						if ( Admin != NULL) 
						{
							GetGame().ObjectDelete( ObJIs );
							status = "Object Deleted !";
							TL().status(sender, status);							
						}
						
				}
			
			case M_RPCs.M_Admin_Menu_Spawn_Ground:							
				//read stuff
				string GroundN_Item;	//ItemName
				string GroundN_ai;		//ai Bool
				string QuantityItem; 	//Textbox
				ctx.Read(GroundN_Item);
				ctx.Read(GroundN_ai);
				ctx.Read(QuantityItem);
				
				if (GroundN_ai == "true")
				{
					ai = true;
				}
				if ( GetGame().IsServer() ) 
					{
						Admin = GetServerMission().IsAdminID( sender.GetName(), sender);
						if ( Admin != NULL) 
						{
							
							//EntityAI oObj = GetGame().CreateObject( GroundN_Item, Admin.GetPosition(), false, ai );
							EntityAI oObj = EntityAI.Cast(GetGame().CreateObject( GroundN_Item, Admin.GetPosition(), false, ai ));
							
							//obEditor.addObject( oObj );
							if ( oObj.IsInherited( ItemBase ) )
							{
								//oItem = ( ItemBase ) oObj;
								oItem = ItemBase.Cast(oObj);
								SetupSpawnedItem( oItem, oItem.GetMaxHealth(), 1 );
								
								quantity = 0;
								text = QuantityItem;
								text.ToUpper();
								//TODO ?? Check IsInherited EntetyAI
								if (text == "MAX")
								{
									quantity = oItem.GetQuantityMax();
								} else
								{
									quantity = text.ToInt();
								}
								oItem.SetQuantity(quantity);
								return;
							}
							oObj.PlaceOnSurface();
							TL().status(sender, GroundN_Item + " Spawned");
						}
					}
		
				if ( GetGame().IsClient() && GetGame().IsMultiplayer() ) 
					{
					}
			break;

			case M_RPCs.M_Admin_Menu_Spawn_ItemPrev:							
				//read stuff
				string ItemPrev_Item;	//ItemName
				ctx.Read(ItemPrev_Item);

				if ( GetGame().IsServer() ) 
					{
						Admin = GetServerMission().IsAdminID( sender.GetName(), sender);
						if ( Admin != NULL) 
						{

							EntityAI oObjp = EntityAI.Cast(GetGame().CreateObject( ItemPrev_Item, vector.Zero, false, false ));
							//obEditor.addObject( oObj );
							
								GetGame().RPCSingleParam( NULL, M_RPCs.M_Admin_Menu_Spawn_ItemPrev_ok, new Param1<EntityAI>( oObjp ), false, AdminIdentity );
					
															
								
							
						}
					}
		
				if ( GetGame().IsClient() && GetGame().IsMultiplayer() ) 
					{
					}
			break;
			
			
			
			case M_RPCs.M_Admin_Menu_Spawn_Inventory:							
				//read stuff
				string Inventory_Item;	//ItemName
				string Inventory_ai;		//ai Bool
				string Inventory_QuantityItem; 	//Textbox
				ctx.Read(Inventory_Item);
				ctx.Read(Inventory_ai);
				ctx.Read(Inventory_QuantityItem);
				
				if (Inventory_ai == "true")
				{
					ai = true;
				}
				if ( GetGame().IsServer() ) 
					{
						Admin = GetServerMission().IsAdminID( sender.GetName(), sender);
						if ( Admin != NULL) 
						{
							EntityAI oInvItem = Admin.GetInventory().CreateInInventory( Inventory_Item );
							oInvItem.SetHealth( oInvItem.GetMaxHealth() );
							if ( oInvItem.IsInherited( ItemBase ) )
							{
								oItem = ItemBase.Cast(oObj);
								SetupSpawnedItem( oItem, oItem.GetMaxHealth(), 1 );
								quantity = 0;
								text = Inventory_QuantityItem;
								text.ToUpper();
								if (text == "MAX")
								{
									quantity = oItem.GetQuantityMax();
								} else
								{
									quantity = text.ToInt();
								}
								oItem.SetQuantity(quantity);
								return;
							}	
						}
					}
		
				if ( GetGame().IsClient() && GetGame().IsMultiplayer() ) 
					{
					}
			break;
			
			case M_RPCs.M_Admin_Menu_Spawn_Cursor:
					//read stuff
				string Cursor_Item;	//ItemName
				vector Cursor_Pos	//Vector Postition
				string Cursor_ai;		//ai Bool
				string Cursor_QuantityItem; 	//Textbox
				ctx.Read(Cursor_Item);
				ctx.Read(Cursor_Pos);
				ctx.Read(Cursor_ai);
				ctx.Read(Cursor_QuantityItem);
				if (Cursor_ai == "true")
				{
					ai = true;
				}
				if ( GetGame().IsServer() ) 
					{
						Admin = GetServerMission().IsAdminID(sender.GetName(), sender);
						if ( Admin != NULL) 
						{
							EntityAI oCursorObj = EntityAI.Cast(GetGame().CreateObject( Cursor_Item, Cursor_Pos, false, ai ));
							//obEditor.addObject( oCursorObj );
							
							if ( oCursorObj.IsInherited( ItemBase ) )
							{
								oItem = ItemBase.Cast(oCursorObj);
								SetupSpawnedItem( oItem, oItem.GetMaxHealth(), 1 );

								quantity = 0;
								text = Cursor_QuantityItem;
								text.ToUpper();

								if (text == "MAX")
								{
									quantity = oItem.GetQuantityMax();
								} else
								{
									quantity = text.ToInt();
								}
								oItem.SetQuantity(quantity);
								return;
							}
							oCursorObj.PlaceOnSurface();
							TL().status(sender, Cursor_Item + " Spawned");
						}
					}
						
					if ( GetGame().IsClient() && GetGame().IsMultiplayer() ) 
						{
						}
			break;
			
			case M_RPCs.M_Admin_Menu_Heal:
					if ( GetGame().IsServer() ) 
						{
							
							Admin = GetServerMission().IsAdminID(sender.GetName(), sender);
							if ( Admin != NULL) 
							{
								//AdminIdentity = Admin.GetIdentity();
						//AdminUID 	  = AdminIdentity.GetId();
								Print(AdminUID);
								Admin.GetMaxHealth( "", "" );
                                Admin.SetHealth( "","Blood", Admin.GetMaxHealth( "", "Blood" ) );
								Admin.SetHealth( "GlobalHealth", "Health", Admin.GetMaxHealth( "GlobalHealth", "Health" ) );
                                Admin.GetStatHeatComfort().Set(0);
                                Admin.GetStatTremor().Set(0);
                                Admin.GetStatWet().Set(0);
                                Admin.GetStatEnergy().Set(20000);
                                Admin.GetStatWater().Set(5000);
                                Admin.GetStatStomachEnergy().Set(20000);
                                Admin.GetStatStomachWater().Set(5000);
                                Admin.GetStatStomachVolume().Set(0);
                                Admin.GetStatDiet().Set(2500);
                                Admin.GetStatSpecialty().Set(1);
								Admin.SetBleedingBits(0);
								TL().status(sender, sender.GetName() + " Healed");
							}
						}
			break;
			
			case M_RPCs.M_Admin_Menu_Strip:
					string item;
					Param1<string> stringParam;
					ctx.Read( stringParam );
					PlayerName = stringParam.param1;
					if ( GetGame().IsServer() ) 
						{
							Admin = GetServerMission().IsAdminID(sender.GetName(), sender);
							if ( Admin != NULL) 
							{
								for ( int a = 0; a < players.Count(); ++a )
								{
									selectedPlayer = PlayerBase.Cast(players.Get(a));
									selectedIdentity = selectedPlayer.GetIdentity();
									if ( selectedIdentity.GetName() == PlayerName )
									{
										selectedPlayer.RemoveAllItems();
										TL().status(sender, selectedIdentity.GetName() + " Striped");
									}
								}
							}
						}
			break;
			
			case M_RPCs.M_Admin_Menu_TpTo:
					ctx.Read( stringParam );
					PlayerName = stringParam.param1;
					if ( GetGame().IsServer() ) 
						{
							Admin = GetServerMission().IsAdminID(sender.GetName(), sender);
							if ( Admin != NULL) 
							{
								array<Man> playerstptp = new array<Man>;
								GetGame().GetPlayers( playerstptp );
								vector AdminPos;
								AdminPos = Admin.GetPosition();
								for ( int it = 0; it < playerstptp.Count(); ++it )
								{
									PlayerBase Targettpto = PlayerBase.Cast(playerstptp.Get(it));
									selectedIdentity =playerstptp.Get(it).GetIdentity();
									if ( selectedIdentity.GetName() == PlayerName )
									{
										Targettpto.SetPosition( AdminPos );
										TL().status(sender, PlayerName + " Teleported");
									}
								}
							}
						}
			break;
			
			case M_RPCs.M_Admin_Menu_TpMe:
					ctx.Read( stringParam );
					PlayerName = stringParam.param1;
					if ( GetGame().IsServer() ) 
						{
							Admin = GetServerMission().IsAdminID(sender.GetName(), sender);
							if ( Admin != NULL) 
							{
								for ( int zm = 0; zm < players.Count(); ++zm )
								{
									if ( players.Get(zm).GetIdentity().GetName() == PlayerName )
									{
										Admin.SetPosition(players.Get(zm).GetPosition());
										TL().status(sender, "Telepported to " + PlayerName);
									}
								}
							}
						}
			break;			
			
			case M_RPCs.M_Admin_Menu_TpMeToPos:
					string TpDestination;
					ctx.Read( TpDestination );
					if ( GetGame().IsServer() ) 
						{
							
							TStringArray strs = new TStringArray;
							vector vecTpDestination = TpDestination.ToVector();
							TpDestination.Split(" ", strs );
							float x = strs.Get(0).ToFloat();
							float y = strs.Get(2).ToFloat();
							float z = 0.0;
							string Vec = "" + strs.Get(0).ToFloat() + "0.0" + strs.Get(2).ToFloat();
							//vector ofixPlayerPos = Vector(x, 0.0, y)
							//vector ofixPlayerPos = Vector( x, z, y );
							Admin = GetServerMission().IsAdminID(sender.GetName(), sender);
							if ( Admin != NULL) 
							{	
									//vector position = strs.Get(0) + " 0 " + strs.Get(2);
									vector position = TpDestination.ToVector();
									vector ofixPlayerPos;
									ofixPlayerPos[0] = strs.Get(0).ToFloat();
									ofixPlayerPos[2] = strs.Get(2).ToFloat();

									ofixPlayerPos = SnapToGround( ofixPlayerPos );
									Admin.SetPosition(ofixPlayerPos);
									TL().status(sender, "Telepported to " + ofixPlayerPos.ToString(false) );
							}
						}
			break;
			
			
			case M_RPCs.M_Admin_Menu_TpMeToPosVec:
					// Param2<float> teleParam
					// Param1<float> teleParam
					float X, Y;
					ctx.Read(X);
					ctx.Read(Y);
					Print(" Param2 = " + X + " Param 0 = " + Y);
					float atlZ = GetGame().SurfaceY(X, Y);
					vector reqpos = Vector(X, atlZ, Y);
					if ( GetGame().IsServer() ) 
						{
							Admin = GetServerMission().IsAdminID(sender.GetName(), sender);
							if ( Admin != NULL) 
							{
								Admin.SetPosition(reqpos);
								TL().status(sender, "Telepported to " + reqpos.ToString(false) );
							}
						}
			break;
			
			case M_RPCs.M_Admin_Menu_TpAllMe:
					if ( GetGame().IsServer() ) 
						{
							Admin = GetServerMission().IsAdminID(sender.GetName(), sender);
							if ( Admin != NULL) 
							{
								int tpCount = TeleportAllPlayersTo(Admin);
								 string msgc = "All " + tpCount.ToString() + " Players Teleported here";
								 TL().status(sender, msgc );
							}
						}
			break;
			
			case M_RPCs.M_Admin_Menu_Spawn_Car:
					if ( GetGame().IsServer() ) 
						{
							Admin = GetServerMission().IsAdminID(sender.GetName(), sender);
							if ( Admin != NULL) 
							{
								Car MyNiva;
								vector position22 = Admin.GetPosition();
								float adminHeading = MiscGameplayFunctions.GetHeadingAngle(Admin);
								vector posModifier = Vector(-(3 * Math.Sin(adminHeading)), 0, 3 * Math.Cos(adminHeading));
								
								MyNiva = Car.Cast(GetGame().CreateObject( "OffroadHatchback", position22 + posModifier, false, true, true ));		            
								MyNiva.GetInventory().CreateAttachment("HatchbackHood");
								MyNiva.GetInventory().CreateAttachment("HatchbackTrunk");
								MyNiva.GetInventory().CreateAttachment("HatchbackWheel");
								MyNiva.GetInventory().CreateAttachment("HatchbackWheel");
								MyNiva.GetInventory().CreateAttachment("HatchbackWheel");
								MyNiva.GetInventory().CreateAttachment("HatchbackWheel");
								MyNiva.GetInventory().CreateAttachment("SparkPlug");
								MyNiva.GetInventory().CreateAttachment("CarRadiator");
								MyNiva.GetInventory().CreateAttachment("CarBattery");
								
								MyNiva.Fill( CarFluid.FUEL, MyNiva.GetFluidCapacity( CarFluid.FUEL ) );
								MyNiva.Fill( CarFluid.OIL, MyNiva.GetFluidCapacity( CarFluid.OIL ) );
								MyNiva.Fill( CarFluid.BRAKE, MyNiva.GetFluidCapacity( CarFluid.BRAKE ) );
								MyNiva.Fill( CarFluid.COOLANT, MyNiva.GetFluidCapacity( CarFluid.COOLANT ) );
								TL().status(sender, "Car spawned and filled" );
							}
						}
						
					if ( GetGame().IsClient() && GetGame().IsMultiplayer() ) 
						{
						}
			break;
			
			case M_RPCs.M_Admin_Menu_Car_Refill:
					if ( GetGame().IsServer() ) 
						{
							Admin = GetServerMission().IsAdminID(sender.GetName(), sender);
							if ( Admin != NULL) 
							{
								ref array<Object> nearest_objects = new array<Object>;
								ref array<CargoBase> proxy_cargos = new array<CargoBase>;
								Car toBeFilled;
								vector position1 = Admin.GetPosition();
								GetGame().GetObjectsAtPosition ( position1, 10, nearest_objects, proxy_cargos );
			
								for (int i = 0; i < nearest_objects.Count(); i++) 
								{
									if (nearest_objects[i].IsKindOf("CarScript")) 
									{
										toBeFilled = Car.Cast(nearest_objects[i]);
										float fuelReq = toBeFilled.GetFluidCapacity( CarFluid.FUEL ) - (toBeFilled.GetFluidCapacity( CarFluid.FUEL ) * toBeFilled.GetFluidFraction( CarFluid.FUEL ));
										float oilReq = toBeFilled.GetFluidCapacity( CarFluid.OIL ) - (toBeFilled.GetFluidCapacity( CarFluid.OIL ) * toBeFilled.GetFluidFraction( CarFluid.OIL ));
										float coolantReq = toBeFilled.GetFluidCapacity( CarFluid.COOLANT ) - (toBeFilled.GetFluidCapacity( CarFluid.COOLANT ) * toBeFilled.GetFluidFraction( CarFluid.COOLANT ));
										float brakeReq = toBeFilled.GetFluidCapacity( CarFluid.BRAKE ) - (toBeFilled.GetFluidCapacity( CarFluid.BRAKE ) * toBeFilled.GetFluidFraction( CarFluid.BRAKE ));
										toBeFilled.Fill( CarFluid.FUEL, fuelReq );
										toBeFilled.Fill( CarFluid.OIL, oilReq );
										toBeFilled.Fill( CarFluid.COOLANT, coolantReq );
										toBeFilled.Fill( CarFluid.BRAKE, brakeReq );
										TL().status(sender, "Car filled" );
									}
								}
							}	
						}
			break;
			
			case M_RPCs.M_Admin_Menu_Day:
					if ( GetGame().IsServer() ) 
						{
							Admin = GetServerMission().IsAdminID(sender.GetName(), sender);
							if ( Admin != NULL) 
							{
								//TODO CHANGEABLE
								GetGame().GetWorld().SetDate( 1988, 5, 23, 12, 0 );
								TL().status(sender, "Time Set to Day" );
							}	
						}
			break;
			
			case M_RPCs.M_Admin_Menu_Night:
					if ( GetGame().IsServer() ) 
						{
							Admin = GetServerMission().IsAdminID(sender.GetName(), sender);
							if ( Admin != NULL) 
							{
								GetGame().GetWorld().SetDate( 1988, 9, 23, 22, 0 );
								TL().status(sender, "Time Set to Night" );
							}
						}
			break;
			
			case M_RPCs.M_Admin_Menu_Kill:
				ctx.Read( stringParam );
				PlayerName = stringParam.param1;
					if ( GetGame().IsServer() ) 
						{
							Admin = GetServerMission().IsAdminID(sender.GetName(), sender);
							if ( Admin != NULL) 
							{
								for ( int ig = 0; ig < players.Count(); ++ig )
								{
									PlayerBase Target = PlayerBase.Cast(players.Get(ig));
									if ( Target.GetIdentity().GetName() == PlayerName )
									{
										Target.SetHealth(0);
										TL().status(sender, PlayerName + "Killed" );										
									}
								}
							}
						}
			break;
			
			case M_RPCs.M_Admin_Menu_KillAll:
				ctx.Read( stringParam );
				PlayerName = stringParam.param1;
					if ( GetGame().IsServer() ) 
						{
							Admin = GetServerMission().IsAdminID(sender.GetName(), sender);
							if ( Admin != NULL) 
							{
								for ( int ig1 = 0; ig1 < players.Count(); ++ig1 )
								{
									PlayerBase Target1 = PlayerBase.Cast(players.Get(ig1));
										Target1.SetHealth(0);						
								}
								TL().status(sender, "All Player Killed" );
							}
						}
			break;
			
			case M_RPCs.M_Admin_Menu_HealAll:
				ctx.Read( stringParam );
				PlayerName = stringParam.param1;
					if ( GetGame().IsServer() ) 
						{
							Admin = GetServerMission().IsAdminID(sender.GetName(), sender);
							if ( Admin != NULL) 
							{
								for ( int ig2 = 0; ig2 < players.Count(); ++ig2 )
								{
								PlayerBase Target2 = PlayerBase.Cast(players.Get(ig2));	
								Target2.GetMaxHealth( "", "" );
                                Target2.SetHealth( "","Blood", Admin.GetMaxHealth( "", "Blood" ) );
								Target2.SetHealth( "GlobalHealth", "Health", Admin.GetMaxHealth( "GlobalHealth", "Health" ) );
                                Target2.GetStatHeatComfort().Set(0);
                                Target2.GetStatTremor().Set(0);
                                Target2.GetStatWet().Set(0);
                                Target2.GetStatEnergy().Set(20000);
                                Target2.GetStatWater().Set(5000);
                                Target2.GetStatStomachEnergy().Set(20000);
                                Target2.GetStatStomachWater().Set(5000);
                                Target2.GetStatStomachVolume().Set(0);
                                Target2.GetStatDiet().Set(2500);
                                Target2.GetStatSpecialty().Set(1);
								Target2.SetBleedingBits(0);
								}
								TL().status(sender, "All Player Healed" );
							}
						}
			break;
			
			case M_RPCs.M_Admin_Menu_StripAll:
				ctx.Read( stringParam );
				PlayerName = stringParam.param1;
					if ( GetGame().IsServer() ) 
						{
							Admin = GetServerMission().IsAdminID(sender.GetName(), sender);
							if ( Admin != NULL) 
							{
								for ( int ig3 = 0; ig3 < players.Count(); ++ig3 )
								{
								PlayerBase Target3 = PlayerBase.Cast(players.Get(ig3));	
								Target3.RemoveAllItems();
								}
								TL().status(sender, "All Player Striped" );
							}
						}
						
					if ( GetGame().IsClient() && GetGame().IsMultiplayer() ) 
						{
						}
			break;
			
			case M_RPCs.M_Admin_Menu_Stamina_Enable:
				ctx.Read( stringParam );
				PlayerName = stringParam.param1;
					if ( GetGame().IsServer() ) 
						{
							Admin = GetServerMission().IsAdminID(sender.GetName(), sender);
							if ( Admin != NULL) 
							{
								GetFileHandler().SetPermission("DisableStamina", PermissionType.DISALLOW, GetPlayerIdentityFromName(PlayerName).GetId());
								TL().status(sender, "Stamina reset Removed for " + PlayerName);
							}
						}
			break;
			
			case M_RPCs.M_Admin_Menu_Stamina_Dissable:
				ctx.Read( stringParam );
				PlayerName = stringParam.param1;
					if ( GetGame().IsServer() ) 
						{
							Admin = GetServerMission().IsAdminID(sender.GetName(), sender);
							if ( Admin != NULL) 
							{
								GetFileHandler().SetPermission("DisableStamina", PermissionType.ALLOW, GetPlayerIdentityFromName(PlayerName).GetId());
								TL().status(sender, "Stamina reset Added for " + PlayerName);
							}
						}
			break;
			
			case M_RPCs.M_Admin_Menu_Player_Stamina_Request:
				ctx.Read( stringParam );
				PlayerName = stringParam.param1;
					if ( GetGame().IsServer() ) 
						{
							Admin = GetServerMission().IsAdminID(sender.GetName(), sender);
							if ( Admin != NULL) 
							{
								if(GetFileHandler().HasPermission("DisableStamina", GetPlayerIdentityFromName(PlayerName))
									{
										ScriptRPC IsStamina = new ScriptRPC();
										IsStamina.Write(PlayerName);
										IsStamina.Send(NULL, M_RPCs.M_Admin_Menu_Player_Stamina_ok, false, AdminIdentity);
									}else
									{
										ScriptRPC IsStamina2 = new ScriptRPC();
										IsStamina2.Write("NULL");
										IsStamina2.Send(NULL, M_RPCs.M_Admin_Menu_Player_Stamina_ok, false, AdminIdentity);
									}
							}
						}
			break;
			
			case M_RPCs.M_Admin_Menu_Teleport_RequestData:
						if ( GetGame().IsServer() ) 
							{
								Admin = GetServerMission().IsAdminID(sender.GetName(), sender);
								if ( Admin != NULL) 
								{
									GetFileHandler().LoadTeleport();
									ref array<string> TpName = new ref array< string >;	
									ref array<vector> TpPos = new ref array< vector >;
									for ( i = 0; i < GetFileHandler().RootTeleport.Children.Count(); i++ )
									{
										TpName.Insert(GetFileHandler().RootTeleport.Children[i].LocationName)
										TpPos.Insert(GetFileHandler().RootTeleport.Children[i].LocationPos)
									}
									ScriptRPC Adding = new ScriptRPC();
									Adding.Write(TpName);
									Adding.Write(TpPos);
									Adding.Send(NULL, M_RPCs.M_Admin_Menu_Teleport_ReciveData, false, Admin.GetIdentity());
								}
							}
				break;
				
			case M_RPCs.M_Admin_Menu_PM:
				string MSG;
				string MSGName;//Vector Postition
				ctx.Read(MSG);
				ctx.Read(MSGName);
					if ( GetGame().IsServer() ) 
						{
							Admin = GetServerMission().IsAdminID(sender.GetName(), sender);
							if ( Admin != NULL) 
							{
								for ( int z1 = 0; z1 < players.Count(); ++z1 )
								{
									selectedPlayer = PlayerBase.Cast(players.Get(z1));
									selectedIdentity = selectedPlayer.GetIdentity();
									if ( selectedIdentity.GetName() == MSGName )
									{
										Msgparam = new Param1<string>( MSG );
										GetGame().RPCSingleParam(NULL , ERPCs.RPC_USER_ACTION_MESSAGE, Msgparam, true, selectedIdentity);
										TL().status(sender, "Message Sent to  " + selectedIdentity.GetName());
									}
								}
							}
						}	
					if ( GetGame().IsClient() && GetGame().IsMultiplayer() ) 
						{
						}
			break;
			
			case M_RPCs.M_Admin_Menu_Map_Player_Request:
				string PosName;
				vector Pos1;	//Vector Postition
				ctx.Read(PosName);
				ctx.Read(Pos1);
					if ( GetGame().IsServer() ) 
						{
							
							Admin = GetServerMission().IsAdminID(sender.GetName(), sender);
							if ( Admin != NULL) 
							{
								GetServerMission().SendPosTOAdmins();
							}
						}	
					if ( GetGame().IsClient() && GetGame().IsMultiplayer() ) 
						{
							
						}
			break; 
			
			case M_RPCs.M_Admin_Menu_Player_List_Request:
					if ( GetGame().IsServer() ) 
						{
							
							Admin = GetServerMission().IsAdminID(sender.GetName(), sender);
							if ( Admin != NULL) 
							{
								array<Man> playerss = new array<Man>;
							array<string> allplayers = new array<string>;
							GetGame().GetPlayers( playerss );
							for ( i = 0; i < playerss.Count(); ++i)
							{								
								PlayerBase currentPlayer = PlayerBase.Cast(playerss.Get(i));
								string playername 		  = currentPlayer.GetIdentity().GetName();
								allplayers.Insert(playername)
							}
							ScriptRPC Plist = new ScriptRPC();
							Plist.Write(allplayers);
							Plist.Send(NULL, M_RPCs.M_Admin_Menu_Player_List, true, sender);
							
							}
						}	
					if ( GetGame().IsClient() && GetGame().IsMultiplayer() ) 
						{
							
						}
			break; 
			
			case M_RPCs.M_Admin_Menu_Player_Health_Request:
				Param1<string> stringParamss;
				ctx.Read( stringParamss );
				string RecPlayer = stringParamss.param1;
				Print("Health Request");
				PlayerBase HealthPlayer;
					if ( GetGame().IsServer() ) 
						{
							
							array<Man> playerssh = new array<Man>;
							
							GetGame().GetPlayers( playerssh );
							for ( i = 0; i < playerssh.Count(); ++i)
							{								
								HealthPlayer = PlayerBase.Cast(playerssh.Get(i));
								string playername1 		  = HealthPlayer.GetIdentity().GetName();
								Print("Curretn = " +  playername1 + "Looking for " + RecPlayer);
								if(playername1 == RecPlayer)
								{
									ref FPPlayer HPlayer = NULL;
									ref PlayerDataN HData = new ref PlayerDataN;
									HPlayer = GetFileHandler().GetPlayerByIdentity(HealthPlayer.GetIdentity());
									HData = HPlayer.Data;
									Admin = GetServerMission().IsAdminID(sender.GetName(), sender);
									if ( Admin != NULL) 
									{
										DebugMonitorValues values = HealthPlayer.GetDebugMonitorValues();
										string health, blood, HPos;
										health = HData.FHealth.ToString();
										blood = HData.FBlood.ToString();
										HPos = HData.VPosition.ToString();
										Print("Healt Player Found " + health);
										ScriptRPC PPos = new ScriptRPC();
										PPos.Write(health);
										PPos.Write(blood);
										PPos.Write(HPos);
										PPos.Send(NULL, M_RPCs.M_Admin_Menu_Player_Health, false, AdminIdentity);
										}
							}
							
							
							}
						}	
					if ( GetGame().IsClient() && GetGame().IsMultiplayer() ) 
						{
							
						}
			break; 
			
			
			
		}
	}
	
	ref PlayerBase GetPlayerBaseFromName(string name)
	{
		array<Man> players = new array<Man>;
		GetGame().GetPlayers( players );
		PlayerBase Target;
		for ( int ig = 0; ig < players.Count(); ++ig )
			{
				Target = PlayerBase.Cast(players.Get(ig));
				if ( Target.GetIdentity().GetName() == name )
				{
					return Target;						
				}
			}
		return Target;
	}
	
	ref PlayerIdentity GetPlayerIdentityFromName(string name)
	{
		array<Man> players = new array<Man>;
		GetGame().GetPlayers( players );
		PlayerBase Target;
		PlayerIdentity TargetIdent;
		for ( int ig = 0; ig < players.Count(); ++ig )
			{
				Target = PlayerBase.Cast(players.Get(ig));
				TargetIdent = Target.GetIdentity();
				if ( TargetIdent.GetName() == name )
				{
					return TargetIdent;						
				}
			}
		return TargetIdent;
	}
	
	void status(PlayerIdentity ident, string msg)
	{
		GetGame().RPCSingleParam( NULL, M_RPCs.M_Admin_Menu_MessageStatus, new Param1<string>( msg ), false, ident );
	}
	
	void SendRPC() 
	{
		GetGame().RPCSingleParam( NULL, M_RPCs.M_Admin_Menu, new Param1<vector>( GetCursorPos() ), false, AdminIdentity );
	}
	
	void SendRPCItem(string item) 
	{
		GetGame().RPCSingleParam( NULL, M_RPCs.M_Admin_Menu_Spawn_Ground, new Param1<string>(item), false, AdminIdentity );
	}
	
	
	void SendRPCHeal() 
	{
		GetGame().RPCSingleParam( NULL, M_RPCs.M_Admin_Menu_Heal, new Param1<string>(""), false, AdminIdentity );
	}
	
	void SendRPCStrip(string PlayerName) 
	{
		GetGame().RPCSingleParam( NULL, M_RPCs.M_Admin_Menu_Strip, new Param1<string>(PlayerName), false, AdminIdentity );
	}
	
	void SendRPCTpTo(string PlayerName) 
	{
		GetGame().RPCSingleParam( NULL, M_RPCs.M_Admin_Menu_TpTo, new Param1<string>(PlayerName), false, AdminIdentity );
	}
	
	void SendRPCTpMe(string PlayerName) 
	{
		GetGame().RPCSingleParam( NULL, M_RPCs.M_Admin_Menu_TpMe, new Param1<string>(PlayerName), false, AdminIdentity );
	}
	
	void SendRPCTpAllMe() 
	{
		GetGame().RPCSingleParam( NULL, M_RPCs.M_Admin_Menu_TpAllMe, new Param1<string>(""), false, AdminIdentity );
	}
	
	void SendRPCSpCar() 
	{
		GetGame().RPCSingleParam( NULL, M_RPCs.M_Admin_Menu_Spawn_Car, new Param1<string>(""), false, AdminIdentity );
	}
	
	void SendRPCDay() 
	{
		GetGame().RPCSingleParam( NULL, M_RPCs.M_Admin_Menu_Day, new Param1<string>(""), false, AdminIdentity );
	}
	
	void SendRPCNight() 
	{
		GetGame().RPCSingleParam( NULL, M_RPCs.M_Admin_Menu_Night, new Param1<string>(""), false, AdminIdentity );
	}
	
	void SendRPCRefill() 
	{
		GetGame().RPCSingleParam( NULL, M_RPCs.M_Admin_Menu_Car_Refill, new Param1<string>(""), false, AdminIdentity );
	}
	
	
	
	void SendRPCTpToPos(string pos) 
	{
		GetGame().RPCSingleParam( NULL, M_RPCs.M_Admin_Menu_TpToPos, new Param1<string>(pos), false, AdminIdentity );
	}
	
	void SendRPCKill(string PlayerName) 
	{
		GetGame().RPCSingleParam( NULL, M_RPCs.M_Admin_Menu_Kill, new Param1<string>(PlayerName), false, AdminIdentity );
	}
	
	void SendRPCSpWear() 
	{
		GetGame().RPCSingleParam( NULL, M_RPCs.M_Admin_Menu_SpWear, new Param1<string>(""), false, AdminIdentity );
	}
	
	

	
	vector SnapToGround(vector pos)
	{
		float pos_x = pos[0];
		float pos_z = pos[2];
		float pos_y = GetGame().SurfaceY( pos_x, pos_z );
		vector tmp_pos = Vector( pos_x, pos_y, pos_z );
		tmp_pos[1] = tmp_pos[1] + pos[1];

		return tmp_pos;
	}
	
	int TeleportAllPlayersTo(PlayerBase Admin)
	{
		array<Man> players = new array<Man>;
		GetGame().GetPlayers( players );

		vector AdminPos;
		AdminPos = Admin.GetPosition();

		for ( int i = 0; i < players.Count(); ++i )
		{
			PlayerBase Target = PlayerBase.Cast(players.Get(i));
			Target.SetPosition( AdminPos );
		}
		return i;
	}
	

	void oSpawnItemFunc(int ground, string ClassName)//2nd PlayerBase player
	{
		EntityAI item;
		ItemBase itemBs

		vector NewPosition;
		vector OldPosition;

		if (ground == 1)
		{
			OldPosition = Admin.GetPosition();

			NewPosition[0] = OldPosition[0] + 1.5;
			NewPosition[1] = OldPosition[1] + 0.1;
			NewPosition[2] = OldPosition[2] + 1.5;
			GetGame().CreateObject( ClassName, NewPosition, false, true );
		}else{

			item = Admin.GetInventory().CreateInInventory( ClassName );
			itemBs = ItemBase.Cast(item);	
			itemBs.SetQuantity(1);
		}
	}
	
	
	
}
ref AdminMenu Tomato_AdminMenuM;
ref AdminMenu GetAdminM()
{
    if( !Tomato_AdminMenuM )
    {
        Tomato_AdminMenuM = new ref AdminMenu();
    }

    return Tomato_AdminMenuM;
}
