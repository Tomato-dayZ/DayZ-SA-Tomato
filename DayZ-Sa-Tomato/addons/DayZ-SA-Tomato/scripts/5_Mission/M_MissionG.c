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
	ref DevTeleport devTeleport;
	ref DevCam devCam;
	ref AdminMenu adminMenu;
	ref AdminMenuManager adminMenuManager;
	//ref AdminMenuMain AdminMenumain;

	bool isSpectating = false;
	bool MenuOpen = false;
	void MissionGameplay()
	{
	    Print( " Mission Gameplay Constructor ");

	    devTeleport = new DevTeleport();
	    devCam = new DevCam();
		adminMenu = new AdminMenu();
		adminMenuManager = new AdminMenuManager(); 
	}

	override void OnInit() 
	{
		super.OnInit();

		Print( " Mission Gameplay ");
	}

	override void OnMissionStart()
	{
		super.OnMissionStart();
		
	}
	
	
	override void OnKeyRelease( int key )
	{
		super.OnKeyRelease( key );
		PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
		if ( key == KeyCode.KC_N ) 
		{
			adminMenuManager.Teleport();
			if ( GetGame().IsClient() ) 
			{
			}
		}

		if ( key == KeyCode.KC_INSERT ) 
		{			
			adminMenuManager.CamTeleport( isSpectating, GetCursorPos() );
			isSpectating = !isSpectating;
		}
		if ( key == KeyCode.KC_M )
	    {
			if(GetGame().IsClient() || !GetGame().IsMultiplayer())
			{
				if ( player )
				{			
					GetPlayer().MessageStatus( "Admin Menue Is Client" );
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