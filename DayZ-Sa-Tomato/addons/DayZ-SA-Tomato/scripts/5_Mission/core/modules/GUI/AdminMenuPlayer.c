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
class AdminMenuGuiPlayer extends ScriptedWidgetEventHandler
{
	protected Widget						m_Root;
	

	ref AdminMenuManager AMenuM;
	protected AdminMenuGui					m_Menu;
	
	protected ref map<int, ref Param2<string, string>> m_TextMap;
	protected ButtonWidget m_btn_Player_Kill;
	protected ButtonWidget m_btn_Player_Strip;
	protected ButtonWidget m_btn_Player_Heal;
	protected ButtonWidget m_btn_Player_TpTo;
	protected ButtonWidget m_btn_Player_TpMe;
	protected ButtonWidget m_btn_Player_Stamina;
	protected ButtonWidget m_btn_Player_KillAll;
	protected ButtonWidget m_btn_Player_HealAll;
	protected ButtonWidget m_btn_Player_StripAll;
	protected ButtonWidget m_btn_Player_TpMeAll;
	protected ButtonWidget m_btn_Player_Spectate;
	protected ButtonWidget m_btn_Player_Send;
	protected TextWidget m_Text_Player_Blood;
	protected TextWidget m_Text_Player_Health;
	protected TextWidget m_Text_Player_Pos;
	protected TextWidget m_Text_Player_Stamina;
	EditBoxWidget m_Box_Player_Message;		
	CheckBoxWidget m_Cb_Player_Stamina;
	TextListboxWidget m_PlayerList;
	
	void AdminMenuGuiPlayer( Widget parent, AdminMenuGui menu )
	{
		
		m_Root					= GetGame().GetWorkspace().CreateWidgets( "com\\DayZ-SA-Tomato\\scripts\\5_Mission\\core\\modules\\GUI\\Layouts\\Admin_Player.layout", parent );
			
		m_Menu						= menu;
		GetDayZGame().Event_OnRPC.Insert( this.ReceiveRPC );
		m_PlayerList = TextListboxWidget.Cast( m_Root.FindAnyWidget( "Player_Player_List" ) );
		m_Box_Player_Message = EditBoxWidget.Cast( m_Root.FindAnyWidget( "Box_Player_Message" ) );
		m_btn_Player_Strip = ButtonWidget.Cast( m_Root.FindAnyWidget( "btn_Player_Strip" ) );
		m_btn_Player_Kill = ButtonWidget.Cast( m_Root.FindAnyWidget( "btn_Player_Kill" ) );
		m_btn_Player_Heal = ButtonWidget.Cast( m_Root.FindAnyWidget( "btn_Player_Heal" ) );
		m_btn_Player_TpMe = ButtonWidget.Cast( m_Root.FindAnyWidget( "btn_Player_tpMe" ) );
		m_btn_Player_TpTo = ButtonWidget.Cast( m_Root.FindAnyWidget( "btn_Player_tpto" ) );
		m_btn_Player_Stamina = ButtonWidget.Cast( m_Root.FindAnyWidget( "btn_Player_Stamina" ) );
		m_btn_Player_KillAll = ButtonWidget.Cast( m_Root.FindAnyWidget( "btn_Player_KillAll" ) );
		m_btn_Player_HealAll = ButtonWidget.Cast( m_Root.FindAnyWidget( "btn_Player_HealAll" ) );
		m_btn_Player_StripAll = ButtonWidget.Cast( m_Root.FindAnyWidget( "btn_Player_StripAll" ) );
		m_btn_Player_TpMeAll = ButtonWidget.Cast( m_Root.FindAnyWidget( "btn_Player_tpMeAll" ) );
		m_btn_Player_Spectate = ButtonWidget.Cast( m_Root.FindAnyWidget( "btn_Player_Spectate" ) );
		m_btn_Player_Send = ButtonWidget.Cast( m_Root.FindAnyWidget( "btn_Player_Send" ) );
		m_Text_Player_Blood = TextWidget.Cast( m_Root.FindAnyWidget( "Text_Player_Blood" ) );
		m_Text_Player_Health = TextWidget.Cast( m_Root.FindAnyWidget( "Text_Player_Energy" ) );
		m_Text_Player_Pos = TextWidget.Cast( m_Root.FindAnyWidget( "Text_Player_Pos" ) );
		m_Cb_Player_Stamina	= CheckBoxWidget.Cast( m_Root.FindAnyWidget( "Cb_Player_Stamina" ) );
		//PlayerList();
		GetGame().RPCSingleParam( NULL, M_RPCs.M_Admin_Menu_Player_List_Request, new Param1<string>(""), false, NULL );
	
	}
	
	
	void LogD(string s)
	{
		GetGame().RPCSingleParam( NULL, M_RPCs.M_Admin_Menu_Log_Debug, new Param1<string>( s ), false, NULL );
	}
	bool Click(Widget w, int x, int y, int button)
	{
		PlayerBase player = PlayerBase.Cast( GetGame().GetPlayer() );
        string PlayerName;
		PlayerName = GetCurrentSelection();
		if (player)
		{
			if( ( w == m_PlayerList ) )
			{
				PlayerSelect();
				return true;
			}
			
			if( ( w == m_btn_Player_Strip ) )
			{
				GetGame().RPCSingleParam( NULL, M_RPCs.M_Admin_Menu_Strip, new Param1<string>(PlayerName), false, NULL );
				return true;
			}
			
			
			if( ( w == m_btn_Player_Kill ) )
			{
				GetGame().RPCSingleParam( NULL, M_RPCs.M_Admin_Menu_Kill, new Param1<string>(PlayerName), false, NULL );
				return true;
			}
			
			if( ( w == m_btn_Player_Heal ) )
			{
				GetGame().RPCSingleParam( NULL, M_RPCs.M_Admin_Menu_Heal, new Param1<string>(""), false, NULL );
				return true;
			}
			
			if( ( w == m_btn_Player_TpMe ) )
			{
				GetGame().RPCSingleParam( NULL, M_RPCs.M_Admin_Menu_TpMe, new Param1<string>(PlayerName), false, NULL );
				return true;
			}
			
			if( ( w == m_btn_Player_TpTo ) )
			{
				GetGame().RPCSingleParam( NULL, M_RPCs.M_Admin_Menu_TpTo, new Param1<string>(PlayerName), false, NULL );
				return true;
			}
			
			
			if( ( w == m_btn_Player_KillAll ) )
			{
				GetGame().RPCSingleParam( NULL, M_RPCs.M_Admin_Menu_KillAll, new Param1<string>(""), false, NULL );
				return true;
			}
			
			if( ( w == m_btn_Player_HealAll ) )
			{
				GetGame().RPCSingleParam( NULL, M_RPCs.M_Admin_Menu_HealAll, new Param1<string>(""), false, NULL );
				return true;
			}
			
			if( ( w == m_btn_Player_StripAll ) )
			{
				GetGame().RPCSingleParam( NULL, M_RPCs.M_Admin_Menu_StripAll, new Param1<string>(""), false, NULL );
				return true;
			}
			
			if( ( w == m_btn_Player_TpMeAll ) )
			{
				GetGame().RPCSingleParam( NULL, M_RPCs.M_Admin_Menu_TpAllMe, new Param1<string>(""), false, NULL );
				return true;
			}
			
			if( ( w == m_btn_Player_Spectate ) )
			{
				if(GetAdminMenuManager().IsSpectate())
				{
					GetAdminMenuManager().CamSpectate(GetAdminMenuManager().IsSpectate(), GetCurrentSelection(), false, vector.Zero, false);
					GetAdminMenuManager().SetSpectate();
					return true;
				}
				GetAdminMenuManager().CamSpectate(GetAdminMenuManager().IsSpectate(), GetCurrentSelection(), false, vector.Zero, true);
				GetAdminMenuManager().SetSpectate();
				return true;
			}
			
			if( ( w == m_btn_Player_Send ) )
			{
				TL().all(m_Box_Player_Message.GetText());
				return true;
			}
			return true;
		}
		return false;
	}
	void Set_Stamina()
	{
		
		if(m_Cb_Player_Stamina.IsChecked())
		{
			GetGame().RPCSingleParam( NULL, M_RPCs.M_Admin_Menu_Stamina_Dissable, new Param1<string>(GetCurrentSelection()), false, NULL );
		}else
		{
			GetGame().RPCSingleParam( NULL, M_RPCs.M_Admin_Menu_Stamina_Enable, new Param1<string>(GetCurrentSelection()), false, NULL );
			
		}
	}
	void ~AdminMenuGuiPlayer()
	{
		GetGame().GetCallQueue( CALL_CATEGORY_SYSTEM ).Remove( this.UpdateStats );
	}
	
	void MouseEnter(Widget w, int x, int y )
	{
		if ( w == m_Box_Player_Message ) 
		{
			//TL().player(PlayerBase.Cast( GetGame().GetPlayer()).GetIdentity(), "Cant close !");
			GetAdminMenuManager().CanClose = false;
		}
	}
	
	void MouseLeave(Widget w, Widget enterW, int x, int y)
	{
		if ( w == m_Box_Player_Message ) 
		{
			GetAdminMenuManager().CanClose = true;
		}
	}
	
	void Focus()
	{
		
	}
	
	
	override bool OnFocus( Widget w, int x, int y )
	{
		if( m_Menu )
			m_Menu.OnFocus( w, x, y );
		if( w )
		{
			Param2<string, string> p = m_TextMap.Get( w.GetUserID() );
			if( p )
			{
				return true;
			}
		}

		return ( w != null );
	}
	
	void ReceiveRPC( PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx ) 
	{
		int i;
		switch(rpc_type)
		{
			
			case M_RPCs.M_Admin_Menu_Player_Health:
				string health;
				string blood
				string position;	//Vector Postition
				ctx.Read(health);
				ctx.Read(blood);
				ctx.Read(position);
					if ( GetGame().IsServer() ) 
						{
							
						}	
					if ( GetGame().IsClient() && GetGame().IsMultiplayer() ) 
						{
						m_Text_Player_Health.SetText(health);
						m_Text_Player_Blood.SetText(blood);
						m_Text_Player_Pos.SetText(position);
						}
						

			break;
			
			case M_RPCs.M_Admin_Menu_Player_Stamina_ok:
				string StaminName;
				ctx.Read(StaminName);
					if ( GetGame().IsServer() ) 
						{
							
						}	
					if ( GetGame().IsClient() && GetGame().IsMultiplayer() ) 
						{
							if(StaminName == "NULL")
							{
								m_Cb_Player_Stamina.SetChecked(false);
							}else if (StaminName == GetCurrentSelection())
							{
								m_Cb_Player_Stamina.SetChecked(true);
							}
						}
						

			break;
			
			case M_RPCs.M_Admin_Menu_Player_List:
				array<string> allplayers = new array<string>;
				ctx.Read(allplayers);
				
					if ( GetGame().IsServer() ) 
						{
							
						}	
					if ( GetGame().IsClient() && GetGame().IsMultiplayer() ) 
						{
							m_PlayerList.ClearItems();
							for (i = 0; i < allplayers.Count(); ++i)
							{
								m_PlayerList.AddItem( allplayers[i], NULL, 0 ); 
							}
						}
			break;
			
			case M_RPCs.M_Admin_Menu_Player_List_Clear:
					if ( GetGame().IsClient() && GetGame().IsMultiplayer() ) 
						{
							m_PlayerList.ClearItems(); 
						}
			break;
		}
	}
	
	void UpdateStats()//Remove
	{
		array<Man> players = new array<Man>;
		GetGame().GetPlayers( players );
		PlayerBase selectedPlayer;
		PlayerIdentity selectedIdentity;
		for ( int a = 0; a < players.Count(); ++a )
			{
				selectedPlayer = PlayerBase.Cast(players.Get(a));
				selectedIdentity = selectedPlayer.GetIdentity();
				if ( selectedIdentity.GetName() == GetCurrentSelection() )
				{
					GetGame().RPCSingleParam( NULL, M_RPCs.M_Admin_Menu_Player_Stamina_Request, new Param1<string>(selectedIdentity.GetName()),  false, NULL );
					GetGame().RPCSingleParam( NULL, M_RPCs.M_Admin_Menu_Player_Health_Request, new Param1<string>(selectedIdentity.GetName()), false, NULL );
				}
			}
		//GetGame().RPCSingleParam( NULL, M_RPCs.M_Admin_Menu_Player_Health_Request, new Param1<PlayerBase>(selectedPlayer), false, NULL );
	}
	
	void PlayerSelect()
	{
		//GetGame().RPCSingleParam( NULL, M_RPCs.M_Admin_Menu_Player_Stamina_Request, new Param1<string>(GetCurrentSelection() ), false, NULL );
		array<Man> players = new array<Man>;
		GetGame().GetPlayers( players );
		PlayerBase selectedPlayer;
		PlayerIdentity selectedIdentity;
		for ( int a = 0; a < players.Count(); ++a )
			{
				selectedPlayer = PlayerBase.Cast(players.Get(a));
				selectedIdentity = selectedPlayer.GetIdentity();
				if ( selectedIdentity.GetName() == GetCurrentSelection() )
				{
					GetGame().RPCSingleParam( NULL, M_RPCs.M_Admin_Menu_Player_Health_Request, new Param1<string>(selectedIdentity.GetName()), false, NULL );
					GetGame().RPCSingleParam( NULL, M_RPCs.M_Admin_Menu_Player_Stamina_Request, new Param1<string>(selectedIdentity.GetName()), false, NULL );
				}
			}
		GetGame().GetCallQueue( CALL_CATEGORY_SYSTEM ).CallLater( this.UpdateStats, 1500, true );

	}
	
	void PlayerList()
	{
		
		 m_PlayerList.ClearItems();
		 array<Man> players = new array<Man>;
		 GetGame().GetPlayers( players );
		 for (int i = 0; i < players.Count(); ++i)
			 {
				 string msg = "AdminMenuPlayer - PlayerList() Adding " + players.Get(i).GetIdentity().GetName() + " To List";
				 GetGame().RPCSingleParam( NULL, M_RPCs.M_Admin_Menu_Log_Info, new Param1<string>( msg ), false, NULL );
				 m_PlayerList.AddItem( players.Get(i).GetIdentity().GetName(), NULL, 0 );  
			 }
	}
	
	string GetCurrentSelection()
	{
		if ( m_PlayerList.GetSelectedRow() != -1 )
		{
			string result;
			m_PlayerList.GetItemText( m_PlayerList.GetSelectedRow(), 0, result );
			return result;
		}

		return "";
	}
	
	void Message( string txt ) 
	{
        // GetGame().GetMission().OnEvent(ChatMessageEventTypeID, new ChatMessageEventParams(0, "", txt, ""));
	}
	
	
	
}
