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
modded class MissionGameplay
{
	protected ref PermissionBase m_PermissionBase;
	ref DevTeleport devTeleport;
	ref LogHandler m_LogHandler;
	// ref AdminMenuGui m_AdminMenuGui;
	ref DevCam devCam;
	ref AdminMenu adminMenu;
	ref TeleportData Tdata;
	ref AdminMenuManager adminMenuManager;
	bool isSpectating = false;
	bool MenuOpen = false;
	
	void MissionGameplay()
	{
	    Print( " Mission Gameplay Constructor ");
		m_LogHandler = new ref LogHandler();
		// m_AdminMenuGui = new ref AdminMenuGui();
		m_PermissionBase = new ref PermissionBase;
	    devTeleport = new DevTeleport();
	    devCam = new DevCam();
		adminMenu = new AdminMenu();
		adminMenuManager = new AdminMenuManager(); 
		Tdata = new TeleportData();
	}
	
	void ~MissionGameplay()
	{
		delete Tdata;
		delete m_LogHandler;
		delete adminMenuManager;
		delete adminMenu;
		delete m_PermissionBase;
	}

	override void OnInit() 
	{
		super.OnInit();

		Print( " Mission Gameplay ");
	}

	override void OnMissionStart()
	{
		
        super.OnMissionStart();
		m_PermissionBase.OnStart();
        GetGame().RPCSingleParam( NULL, M_RPCs.M_Admin_Player_UpdatePlayers, new Param1<string>( "" ), false, NULL );
	}
	
	override void OnMissionFinish()
    {
		m_PermissionBase.OnFinish();
		GetGame().GetUIManager().CloseMenu( MENU_INGAME );
        super.OnMissionFinish();
    }
	
	
	
	// override void OnUpdate( float timeslice )
    // {
        // super.OnUpdate( timeslice );
		// m_PermissionBase.OnUpdate( timeslice );
    // }
	


	override void OnKeyPress (int key )
	{
		super.OnKeyPress( key );
		PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
		if ( key == KeyCode.KC_N ) 
		{
			adminMenuManager.Teleport();
			if ( GetGame().IsClient() ) 
			{
			}
		}

		if ( key == KeyCode.KC_DELETE ) 
		{		
			if(adminMenuManager.Spectate)
			{
				adminMenuManager.CamSpectate(adminMenuManager.Spectate, "", false, vector.Zero, false);
				adminMenuManager.Spectate = !adminMenuManager.Spectate;
				return;
			}
			
			if(isSpectating)
			{
				adminMenuManager.CamTeleport( isSpectating, vector.Zero, false );
				isSpectating = !isSpectating;
			}
			
		}
		
		if ( key == KeyCode.KC_INSERT ) 
		{	
			if(adminMenuManager.Spectate)
			{
				adminMenuManager.CamSpectate(adminMenuManager.Spectate, "", true, GetCursorPos(), false );
				adminMenuManager.Spectate = !adminMenuManager.Spectate;
				return;
			}
			adminMenuManager.CamTeleport( isSpectating, GetCursorPos() );
			isSpectating = !isSpectating;
		}
		if ( key == KeyCode.KC_M )
	    {
			if(GetGame().IsClient() || !GetGame().IsMultiplayer())
			{
				if ( player )
				{			
					//GetGame().GetMission().OnEvent(ChatMessageEventTypeID, new ChatMessageEventParams(0, "", "DayZ-Sa-Tomato", ""));
					Widget widget = g_Game.GetUIManager().GetWidgetUnderCursor();
					// Print("TL funx");
					// TL().playerSetup();
					adminMenuManager.MenuOpen();
			    }			
		    }
		}
	}
}

//Mission CreateCustomMission(string path)
// {
    // if ( GetGame().IsServer() && GetGame().IsMultiplayer() ) {
        // return new CustomMission(); // this always runs because createcustommission isnt a client side function
    // }
    // return new MissionGameplay();
// }
//class, function, params