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
class PermissionBase
{
    protected ref array< Man > bServerPlayers;

    protected bool bLoaded;
	protected ref array< PlayerIdentity > bServerIdentities;
    void PermissionBase()
    {
		GetFileHandler().IsExit = false
        if ( GetGame().IsServer() && GetGame().IsMultiplayer() )
        {
            bServerPlayers = new ref array< Man >;
        }
		bServerIdentities = new ref array< PlayerIdentity >;
        bLoaded = false;
		GetDayZGame().Event_OnRPC.Insert( this.ReceiveRPC );
    }

    void ~PermissionBase()
    {
        Print("PermissionBase::~PermissionBase");
        if ( GetGame().IsServer() && GetGame().IsMultiplayer() )
        {
            GetGame().GetCallQueue( CALL_CATEGORY_SYSTEM ).Remove( this.ReloadPlayerList );
			GetFileHandler().IsExit = true;
            delete bServerPlayers;
        }
    }
    
	private bool CheckIfExists( ref FPPlayer auPlayer )
    {
        for ( int i = 0; i < bServerIdentities.Count(); i++ )
        {
            if ( auPlayer.GetGUID() == bServerIdentities[i].GetId() )
            {
                return true;
            }
        }

        return false;
    }
	
    void OnStart()
    {
        if ( GetGame().IsServer() && GetGame().IsMultiplayer() )
        {
            GetGame().GetCallQueue( CALL_CATEGORY_SYSTEM ).CallLater( this.ReloadPlayerList, 1000, true );
        }
    }

    void OnFinish()
    {
		GetGame().GetCallQueue( CALL_CATEGORY_SYSTEM ).Remove( this.ReloadPlayerList );
    }

    void OnLoaded()
    {
    }

    void Update( float timeslice )
    {
        if( !bLoaded && !GetDayZGame().IsLoading() )
        {
            bLoaded = true;
            OnLoaded();
        } else {
            OnUpdate( timeslice );
        }
    }

    void OnUpdate( float timeslice )
    {
		ReloadPlayerList();
    }
	
	void ReloadPlayerList()
    {
		if(GetFileHandler().IsExit){return;}
        GetGame().GetPlayers( bServerPlayers );
		if(GetFileHandler().IsExit){return;}
        for ( int i = 0; i < bServerPlayers.Count(); i++ )
        {
			if(GetFileHandler().GetFileHandler().IsExit){return;}
            Man man = bServerPlayers[i];
            PlayerBase player = PlayerBase.Cast( man );
			if(GetFileHandler().IsExit){return;}
            ref FPPlayer auPlayer = GetFileHandler().GetPlayerByIdentity( man.GetIdentity() );

            if ( player )
            {
				if(GetFileHandler().IsExit){return;}
                player.authentiPlayer = auPlayer;
            }
			if(GetFileHandler().IsExit){return;}
            auPlayer.PlayerObject = player;
            auPlayer.IdentityPlayer = man.GetIdentity();
			if(GetFileHandler().IsExit){return;}
            auPlayer.UpdatePlayerDataN();
        }
		if(GetFileHandler().IsExit){return;}
        bServerPlayers.Clear();
		
    }

	
	void ReceiveRPC( PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx ) 
	{

		PlayerBase Admin;
		PlayerIdentity AdminIdentity;
		ref PlayerDataN PData = new ref PlayerDataN;
		switch(rpc_type)
		{
			case M_RPCs.M_Admin_Player_UpdatePlayers:
					if ( GetGame().IsServer() ) 
						{
							Admin = GetServerMission().IsAdminID(sender.GetName(), sender);
							if ( Admin != NULL) 
							{
								AdminIdentity = Admin.GetIdentity();
								
								for ( int i = 0; i < GetFileHandler().GetPlayers().Count(); i++ )
								{
									PData = SerializePlayer( GetFileHandler().GetPlayers().Get( i ) );
									ScriptRPC Adding = new ScriptRPC();
									Adding.Write(PData);
									Adding.Send(NULL, M_RPCs.M_Admin_Player_UpdatePlayer, true, sender);
									//GetRPCManager().SendRPC( "PermissionBase", "UpdatePlayer", new Param1< ref PlayerDataN >( SerializePlayer( GetFileHandler().GetPlayers().Get( i ) ) ), true, sender );
								}
							}
						}
			break;
			
			case M_RPCs.M_Admin_Player_RemovePlayer:
					if ( GetGame().IsClient() && GetGame().IsMultiplayer() ) 
					{
						ctx.Read(PData);
						GetFileHandler().FPPlayers.RemoveItem( DeserializePlayer( PData ) );
					}
			break;
			
			case M_RPCs.M_Admin_Player_UpdatePlayer:
					if ( GetGame().IsClient() && GetGame().IsMultiplayer() ) 
						{
							ctx.Read(PData);
							DeserializePlayer( PData );
						}
			break;
			
			
		}
		
	}
}
