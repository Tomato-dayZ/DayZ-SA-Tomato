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

// STORE ALL PLAYERS DATA HERE FOR OUTSIDE NETWORK BUBBLE!

class PlayerDataN
{
    string SName;
    string SGUID;
    string SSteam64ID;

    int IPingMax;
    int IPingMin;
    int IPingAvg;

    ref array< string > ARoles;
    ref array< string > APermissions;

    vector VPosition;
    vector VDirection;
    vector VOrientation;

    float FHealth;
    float FBlood;
    float FShock;

    int IBloodStatType;

    float FEnergy;
    float FWater;

    float FHeatComfort;

    float FWet;
    float FTremor;
    float FStamina;

    int Kills;
    int TotalKills;
    
    int ILifeSpanState;
    bool BBloodyHands;

    void PlayerDataN()
    {
        ARoles = new ref array< string >;
        APermissions = new ref array< string >;
    }

    static void Load( out PlayerDataN data, ref PlayerBase player )
    {
        data.VPosition = player.GetPosition();
        data.VDirection = player.GetDirection();
        data.VOrientation = player.GetOrientation();
        
        data.FHealth = player.GetHealth( "GlobalHealth","Health" );
        data.FBlood = player.GetHealth( "GlobalHealth", "Blood" );
        data.FShock = player.GetHealth( "GlobalHealth", "Shock" );
        data.IBloodStatType = player.GetStatBloodType().Get();
        data.FEnergy = player.GetStatEnergy().Get();
        data.FWater = player.GetStatWater().Get();
        data.FHeatComfort = player.GetStatHeatComfort().Get();
        data.FWet = player.GetStatWet().Get();
        data.FTremor = player.GetStatTremor().Get();
        data.FStamina = player.GetStatStamina().Get();
        data.ILifeSpanState = player.GetLifeSpanState();
        data.BBloodyHands = player.HasBloodyHands();
    }
}