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

	ref AdminMenuGui m_adMenu;
	ref AdminMenuGuiMap m_map;
	PlayerBase Admin;
	PlayerIdentity AdminIdentity;
	string AdminUID;
				
	void AdminMenu() 
	{
		GetDayZGame().Event_OnRPC.Insert( this.ReceiveRPC );
		//adminMenuMain = new AdminMenuMain();
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
		bool ai = false;

		int quantity = 0;
		string text = "";
		
		
		
		switch(rpc_type)
		{
			
			case (int)M_RPCs.M_Admin_Menu:
				if ( GetGame().IsServer() ) 
				{
					Print("Admin Menu RPC");
					//GetGame().RPCSingleParam( NULL, M_RPCs.M_Admin_Menu, new Param1<vector>( GetCursorPos() ), false, NULL );
					// permission check - server mission file
					
					Admin = GetServerMission().IsAdminID(sender.GetName(), sender.GetPlainId());
					if ( Admin != null ) 
					{
						Print("Admin Menu sender name : " + sender.GetName() + "PlainID : " + sender.GetPlainId());
						AdminIdentity = Admin.GetIdentity();
						AdminUID 	  = AdminIdentity.GetPlainId();
						GetGame().RPCSingleParam( NULL, M_RPCs.M_Admin_Menu_OK, new Param1<string>( "Test" ), false, AdminIdentity );
					}
				}

			if ( GetGame().IsClient() && GetGame().IsMultiplayer() ) 
			{
				  // UIScriptedMenu adminMenuGui = NULL;
				  // adminMenuGui = new AdminMenuGui();
				 // if ( g_Game.GetUIManager().GetMenu() == NULL )
					// { 
						// g_Game.GetUIManager().ShowScriptedMenu( adminMenuGui, NULL );
					// }
			}
			break;
			
			case (int)M_RPCs.M_Admin_Menu_OK:
			Print("Admin Menu OK RPC");
				if ( GetGame().IsServer() ) 
				{	
				}

			if ( GetGame().IsClient() && GetGame().IsMultiplayer() ) 
			{
				  UIScriptedMenu adminMenuGui = NULL;
				  adminMenuGui = new AdminMenuGui();
				 if ( g_Game.GetUIManager().GetMenu() == NULL )
					{ 
						g_Game.GetUIManager().ShowScriptedMenu( adminMenuGui, NULL );
					}
			}
			break;
			
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
						Admin = GetServerMission().IsAdminID( sender.GetName(), sender.GetPlainId());
						if ( Admin != null ) 
						{
							
							EntityAI oObj = GetGame().CreateObject( GroundN_Item, Admin.GetPosition(), false, ai );
							//obEditor.addObject( oObj );
							if ( oObj.IsInherited( ItemBase ) )
							{
								oItem = ( ItemBase ) oObj;
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
						Admin = GetServerMission().IsAdminID( sender.GetName(), sender.GetPlainId());
						if ( Admin != null ) 
						{

							EntityAI oObjp = GetGame().CreateObject( ItemPrev_Item, vector.Zero, false, false );
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
						Admin = GetServerMission().IsAdminID( sender.GetName(), sender.GetPlainId());
						if ( Admin != null ) 
						{
							
							
							
							EntityAI oInvItem = Admin.GetInventory().CreateInInventory( Inventory_Item );
							oInvItem.SetHealth( oInvItem.GetMaxHealth() );
							if ( oInvItem.IsInherited( ItemBase ) )
							{
								oItem = ( ItemBase ) oObj;
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
						Admin = GetServerMission().IsAdminID(sender.GetName(), sender.GetPlainId());
						if ( Admin != null ) 
						{
							EntityAI oCursorObj = GetGame().CreateObject( Cursor_Item, Cursor_Pos, false, ai );
							//obEditor.addObject( oCursorObj );
							
							if ( oCursorObj.IsInherited( ItemBase ) )
							{
								oItem = ( ItemBase ) oCursorObj;
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
								oCursorObj.PlaceOnSurface();
								return;
							}
							
						}
					}
						
					if ( GetGame().IsClient() && GetGame().IsMultiplayer() ) 
						{
						}
			break;
			
			case M_RPCs.M_Admin_Menu_Heal:
					if ( GetGame().IsServer() ) 
						{
							
							Admin = GetServerMission().IsAdminID(sender.GetName(), sender.GetPlainId());
							if ( Admin != null ) 
							{
								//AdminIdentity = Admin.GetIdentity();
						//AdminUID 	  = AdminIdentity.GetPlainId();
								Print(AdminUID);
								Admin.SetHealth( Admin.GetMaxHealth( "", "" ) );
								Admin.SetHealth( "","Blood", Admin.GetMaxHealth( "", "Blood" ) );
								Admin.GetStatEnergy().Add(250);
								Admin.GetStatWater().Add(250);
								Admin.SetBleedingBits(0);
							}
						}
						
					if ( GetGame().IsClient() && GetGame().IsMultiplayer() ) 
						{
						}
			break;
			
			case M_RPCs.M_Admin_Menu_Strip:
					string item;
					Param1<string> stringParam;
					ctx.Read( stringParam );
					PlayerName = stringParam.param1;
					if ( GetGame().IsServer() ) 
						{
							Admin = GetServerMission().IsAdminID(sender.GetName(), sender.GetPlainId());
							if ( Admin != null ) 
							{
								for ( int a = 0; a < players.Count(); ++a )
								{
									selectedPlayer = players.Get(a);
									selectedIdentity = selectedPlayer.GetIdentity();
									if ( selectedIdentity.GetName() == PlayerName )
									{
										selectedPlayer.RemoveAllItems();
									}
								}
							}
						}
						
					if ( GetGame().IsClient() && GetGame().IsMultiplayer() ) 
						{
						}
			break;
			
			case M_RPCs.M_Admin_Menu_TpTo:
					ctx.Read( stringParam );
					PlayerName = stringParam.param1;
					if ( GetGame().IsServer() ) 
						{
							Admin = GetServerMission().IsAdminID(sender.GetName(), sender.GetPlainId());
							if ( Admin != null ) 
							{
								for ( int z = 0; z < players.Count(); ++z )
								{
									selectedPlayer = players.Get(z);
									selectedIdentity = selectedPlayer.GetIdentity();
									if ( selectedIdentity.GetName() == PlayerName )
									{
										selectedPlayer.SetPosition(Admin.GetPosition());

										Msgparam = new Param1<string>( "You were teleported by the admin!" );
										GetGame().RPCSingleParam(Admin, ERPCs.RPC_USER_ACTION_MESSAGE, Msgparam, true, selectedIdentity);
											  
										strMessage = "Player " + PlayerName + " was teleported to your location!";
										Msgparam = new Param1<string>( strMessage );
										GetGame().RPCSingleParam(Admin, ERPCs.RPC_USER_ACTION_MESSAGE, Msgparam, true, AdminIdentity);
									}
								}
							}
						}
						
					if ( GetGame().IsClient() && GetGame().IsMultiplayer() ) 
						{
						}
			break;
			
			case M_RPCs.M_Admin_Menu_TpMe:
					ctx.Read( stringParam );
					PlayerName = stringParam.param1;
					if ( GetGame().IsServer() ) 
						{
							Admin = GetServerMission().IsAdminID(sender.GetName(), sender.GetPlainId());
							if ( Admin != null ) 
							{
								for ( int zm = 0; zm < players.Count(); ++zm )
								{
									if ( players.Get(zm).GetIdentity().GetName() == PlayerName )
									{
										Admin.SetPosition(players.Get(zm).GetPosition());
									}
								}
							}
						}
						
					if ( GetGame().IsClient() && GetGame().IsMultiplayer() ) 
						{
						}
			break;
			
			case M_RPCs.M_Admin_Menu_TpAllMe:
					if ( GetGame().IsServer() ) 
						{
							Admin = GetServerMission().IsAdminID(sender.GetName(), sender.GetPlainId());
							if ( Admin != null ) 
							{
								int tpCount = TeleportAllPlayersTo(Admin);
								 string msgc = "All " + tpCount.ToString() + " Players Teleported to my POS!";
								 Msgparam = new Param1<string>( msgc );
								 GetGame().RPCSingleParam(Admin, ERPCs.RPC_USER_ACTION_MESSAGE, Msgparam, true, AdminIdentity);
							}
						}
						
					if ( GetGame().IsClient() && GetGame().IsMultiplayer() ) 
						{
						}
			break;
			
			case M_RPCs.M_Admin_Menu_Spawn_Car:
					if ( GetGame().IsServer() ) 
						{
							Admin = GetServerMission().IsAdminID(sender.GetName(), sender.GetPlainId());
							if ( Admin != null ) 
							{
								Car MyNiva;
								vector position = Admin.GetPosition();
								float adminHeading = MiscGameplayFunctions.GetHeadingAngle(Admin);
								vector posModifier = Vector(-(3 * Math.Sin(adminHeading)), 0, 3 * Math.Cos(adminHeading));
								
								MyNiva = Car.Cast(GetGame().CreateObject( "OffroadHatchback", position + posModifier, false, true, true ));		            
								MyNiva.GetInventory().CreateAttachment("HatchbackHood");
								MyNiva.GetInventory().CreateAttachment("HatchbackTrunk");
								MyNiva.GetInventory().CreateAttachment("HatchbackDoors_CoDriver");
								MyNiva.GetInventory().CreateAttachment("HatchbackWheel");
								MyNiva.GetInventory().CreateAttachment("HatchbackWheel");
								MyNiva.GetInventory().CreateAttachment("HatchbackWheel");
								MyNiva.GetInventory().CreateAttachment("HatchbackWheel");
								MyNiva.GetInventory().CreateAttachment("SparkPlug");
								MyNiva.GetInventory().CreateAttachment("EngineBelt");
								MyNiva.GetInventory().CreateAttachment("CarBattery");
								
								MyNiva.Fill( CarFluid.FUEL, MyNiva.GetFluidCapacity( CarFluid.FUEL ) );
								MyNiva.Fill( CarFluid.OIL, MyNiva.GetFluidCapacity( CarFluid.OIL ) );
								MyNiva.Fill( CarFluid.BRAKE, MyNiva.GetFluidCapacity( CarFluid.BRAKE ) );
								MyNiva.Fill( CarFluid.COOLANT, MyNiva.GetFluidCapacity( CarFluid.COOLANT ) );
								
							}
						}
						
					if ( GetGame().IsClient() && GetGame().IsMultiplayer() ) 
						{
						}
			break;
			
			case M_RPCs.M_Admin_Menu_Car_Refill:
					if ( GetGame().IsServer() ) 
						{
							Admin = GetServerMission().IsAdminID(sender.GetName(), sender.GetPlainId());
							if ( Admin != null ) 
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
									}
								}
							}	
						}
						
					if ( GetGame().IsClient() && GetGame().IsMultiplayer() ) 
						{
						}
			break;
			
			case M_RPCs.M_Admin_Menu_Day:
					if ( GetGame().IsServer() ) 
						{
							Admin = GetServerMission().IsAdminID(sender.GetName(), sender.GetPlainId());
							if ( Admin != null ) 
							{
								GetGame().GetWorld().SetDate( 1988, 5, 23, 12, 0 );
							}	
						}
						
					if ( GetGame().IsClient() && GetGame().IsMultiplayer() ) 
						{
						}
			break;
			
			case M_RPCs.M_Admin_Menu_Night:
					if ( GetGame().IsServer() ) 
						{
							Admin = GetServerMission().IsAdminID(sender.GetName(), sender.GetPlainId());
							if ( Admin != null ) 
							{
								GetGame().GetWorld().SetDate( 1988, 9, 23, 22, 0 );
							}
						}
						
					if ( GetGame().IsClient() && GetGame().IsMultiplayer() ) 
						{
						}
			break;
			
			case M_RPCs.M_Admin_Menu_TpToPos:
				ctx.Read( stringParam );
				cData = stringParam.param1;
					if ( GetGame().IsServer() ) 
						{
							Admin = GetServerMission().IsAdminID(sender.GetName(), sender.GetPlainId());
							if ( Admin != null ) 
							{
								vector position3 = "0 0 0";
								m_TPLocations.Find( cData, position3 );

								vector ofixPlayerPos;
								ofixPlayerPos[0] = position3[0];
								ofixPlayerPos[2] = position3[2];

								ofixPlayerPos = SnapToGround( ofixPlayerPos );

								Admin.SetPosition(ofixPlayerPos);

								strMessage = "Teleported To Location: " + cData;
								Msgparam = new Param1<string>( strMessage );
								GetGame().RPCSingleParam(Admin, ERPCs.RPC_USER_ACTION_MESSAGE, Msgparam, true, AdminIdentity);
								
							}	
						}
						
					if ( GetGame().IsClient() && GetGame().IsMultiplayer() ) 
						{
						}
			break;
			
			case M_RPCs.M_Admin_Menu_Kill:
				ctx.Read( stringParam );
				PlayerName = stringParam.param1;
					if ( GetGame().IsServer() ) 
						{
							Admin = GetServerMission().IsAdminID(sender.GetName(), sender.GetPlainId());
							if ( Admin != null ) 
							{
								for ( int ig = 0; ig < players.Count(); ++ig )
								{
									PlayerBase Target = players.Get(ig);
									if ( Target.GetIdentity().GetName() == PlayerName )
									{
										Target.SetHealth(0);						
									}
								}
							}
						}
						
					if ( GetGame().IsClient() && GetGame().IsMultiplayer() ) 
						{
						}
			break;
			
			case M_RPCs.M_Admin_Menu_KillAll:
				ctx.Read( stringParam );
				PlayerName = stringParam.param1;
					if ( GetGame().IsServer() ) 
						{
							Admin = GetServerMission().IsAdminID(sender.GetName(), sender.GetPlainId());
							if ( Admin != null ) 
							{
								for ( int ig1 = 0; ig1 < players.Count(); ++ig1 )
								{
									PlayerBase Target1 = players.Get(ig1);
										Target1.SetHealth(0);						
								}
							}
						}
						
					if ( GetGame().IsClient() && GetGame().IsMultiplayer() ) 
						{
						}
			break;
			
			case M_RPCs.M_Admin_Menu_HealAll:
				ctx.Read( stringParam );
				PlayerName = stringParam.param1;
					if ( GetGame().IsServer() ) 
						{
							Admin = GetServerMission().IsAdminID(sender.GetName(), sender.GetPlainId());
							if ( Admin != null ) 
							{
								for ( int ig2 = 0; ig2 < players.Count(); ++ig2 )
								{
								PlayerBase Target2 = players.Get(ig2);	
								Target2.SetHealth( Admin.GetMaxHealth( "", "" ) );
								Target2.SetHealth( "","Blood", Admin.GetMaxHealth( "", "Blood" ) );
								Target2.GetStatEnergy().Add(250);
								Target2.GetStatWater().Add(250);
								Target2.SetBleedingBits(0);
								}
							}
						}
						
					if ( GetGame().IsClient() && GetGame().IsMultiplayer() ) 
						{
						}
			break;
			
			case M_RPCs.M_Admin_Menu_StripAll:
				ctx.Read( stringParam );
				PlayerName = stringParam.param1;
					if ( GetGame().IsServer() ) 
						{
							Admin = GetServerMission().IsAdminID(sender.GetName(), sender.GetPlainId());
							if ( Admin != null ) 
							{
								for ( int ig3 = 0; ig3 < players.Count(); ++ig3 )
								{
								PlayerBase Target3 = players.Get(ig3);	
								Target3.RemoveAllItems();
								}
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
							Admin = GetServerMission().IsAdminID(sender.GetName(), sender.GetPlainId());
							if ( Admin != null ) 
							{
								GetServerMission().RemoveStamina(PlayerName)
							}
						}
						
					if ( GetGame().IsClient() && GetGame().IsMultiplayer() ) 
						{
						}
			break;
			
			case M_RPCs.M_Admin_Menu_Stamina_Dissable:
				ctx.Read( stringParam );
				PlayerName = stringParam.param1;
					if ( GetGame().IsServer() ) 
						{
							Admin = GetServerMission().IsAdminID(sender.GetName(), sender.GetPlainId());
							if ( Admin != null ) 
							{
								GetServerMission().AddStamina(PlayerName)
							}
						}
						
					if ( GetGame().IsClient() && GetGame().IsMultiplayer() ) 
						{
						}
			break;
			
			case M_RPCs.M_Admin_Menu_Player_Stamina_Request:
				ctx.Read( stringParam );
				PlayerName = stringParam.param1;
					if ( GetGame().IsServer() ) 
						{
							Admin = GetServerMission().IsAdminID(sender.GetName(), sender.GetPlainId());
							if ( Admin != null ) 
							{
								if (GetServerMission().StaminaContains(PlayerName))
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
						
					if ( GetGame().IsClient() && GetGame().IsMultiplayer() ) 
						{
						}
			break;
			
			case M_RPCs.M_Admin_Menu_PM:
				string MSG;
				string MSGName;//Vector Postition
				ctx.Read(MSG);
				ctx.Read(MSGName);
					if ( GetGame().IsServer() ) 
						{
							Admin = GetServerMission().IsAdminID(sender.GetName(), sender.GetPlainId());
							if ( Admin != null ) 
							{
								for ( int z1 = 0; z1 < players.Count(); ++z1 )
								{
									selectedPlayer = players.Get(z1);
									selectedIdentity = selectedPlayer.GetIdentity();
									if ( selectedIdentity.GetName() == MSGName )
									{
										Msgparam = new Param1<string>( MSG );
										GetGame().RPCSingleParam(Admin, ERPCs.RPC_USER_ACTION_MESSAGE, Msgparam, true, AdminIdentity);
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
							
							Admin = GetServerMission().IsAdminID(sender.GetName(), sender.GetPlainId());
							if ( Admin != null ) 
							{
								GetServerMission().SendPosTOAdmins();
							}
						}	
					if ( GetGame().IsClient() && GetGame().IsMultiplayer() ) 
						{
							
						}
			break; 
			
			case M_RPCs.M_Admin_Menu_Player_Health_Request:
				
				PlayerBase HealthPlayer;
				ctx.Read(HealthPlayer);
					if ( GetGame().IsServer() ) 
						{
							
							Admin = GetServerMission().IsAdminID(sender.GetName(), sender.GetPlainId());
							if ( Admin != null ) 
							{
								DebugMonitorValues values = HealthPlayer.GetDebugMonitorValues();
								float Value1;
								Value1 = HealthPlayer.GetHealth("", "Health");
								string health = string.Format(" %1", Value1.ToString());
								Print("Name : " + HealthPlayer.GetIdentity().GetName() + "Health :" + health);

								float Value2;
								Value2 = HealthPlayer.GetHealth("", "Blood");
								string blood = string.Format(" %1", Value2.ToString());
								Print("Name : " + HealthPlayer.GetIdentity().GetName() + "blood :" + blood);
							
								vector Value;
								Value = HealthPlayer.GetPosition()
								string positionP = string.Format(" %1 %2 %3", Value[0].ToString(), Value[1].ToString(), Value[2].ToString());
								Print("Name : " + HealthPlayer.GetIdentity().GetName() + "positionP :" + positionP);
								
								ScriptRPC PPos = new ScriptRPC();
								PPos.Write(health);
								PPos.Write(blood);
								PPos.Write(positionP);
								PPos.Send(NULL, M_RPCs.M_Admin_Menu_Player_Health, false, AdminIdentity);
							}
						}	
					if ( GetGame().IsClient() && GetGame().IsMultiplayer() ) 
						{
							
						}
			break; 
			
			
			
		}
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
			PlayerBase Target = players.Get(i);
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