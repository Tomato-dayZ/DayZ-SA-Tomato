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

class FPPlayer
{
	ref FPPermission RootPermission;
	
	PlayerBase PlayerObject;
    PlayerIdentity IdentityPlayer;
	ref PlayerDataN Data;
	
	void FPPlayer(ref PlayerDataN data)
	{
		PlayerObject = NULL;
        Data = data;

        if ( Data == NULL )
        {
            Data = new ref PlayerDataN;
        }
		
		RootPermission = new ref FPPermission( Data.SSteam64ID );
	
	}
	
	void SetPermission(string name, PermissionTypeN type)
	{
		Print("FPPlayer");
		RootPermission.SetPermissionType(name , type)
	}
	
	string FileReadyStripName( string name )
    {
        name.Replace( "\\", "" );
        name.Replace( "/", "" );
        name.Replace( "=", "" );
        name.Replace( "+", "" );

        return name;
    }
	
	bool Load()
    {
        string filename = FileReadyStripName( Data.SSteam64ID );
        Print( "Loading permissions for " + filename );
        FileHandle file = OpenFile( GetFileHandler().PlayersFolderPath + filename + ".Player", FileMode.READ );
            
        ref array< string > data = new ref array< string >;

        if ( file != 0 )
        {
            string line;

            while ( FGets( file, line ) > 0 )
            {
                data.Insert( line );
            }

            CloseFile( file );

            for ( int i = 0; i < data.Count(); i++ )
            {
                AddPermission( data[i] );
            }
        } else
        {
            Print( "Failed to open the file for the player to read. Attemping to create." );

            Save();
            return false;
        }
        
        return true;
    }
	
	bool Save()
    {
        string filename = FileReadyStripName( Data.SSteam64ID );

        Print( "Saving permissions for " + filename );
        FileHandle file = OpenFile( GetFileHandler().PlayersFolderPath + filename + ".Player", FileMode.WRITE );
            //TODO ??
        ref array< string > data = ToPermArray();

        if ( file != 0 )
        {
            string line;

            for ( int i = 0; i < data.Count(); i++ )
            {
                FPrintln( file, data[i] );
            }
            
            CloseFile(file);
            
            Print("Wrote to the players");
            return true;
        } else
        {
            Print("Failed to open the file for the player for writing.");
            return false;
        }
    }
	
	void CopyPermissions( ref FPPermission copy )
    {
        ref array< string > data = new ref array< string >;
        copy.ToPermArray( data );

        for ( int i = 0; i < data.Count(); i++ )
        {
            AddPermission( data[i] );
        }
    }
	
	ref array< string > ToPermArray()
    {        
        Data.APermissions.Clear();

        RootPermission.ToPermArray( Data.APermissions );

        return Data.APermissions;
    }
	
	void ToPermData()
    {
        for ( int i = 0; i < Data.APermissions.Count(); i++ )
        {
            AddPermission( Data.APermissions[i] );
        }
    }
	
	bool HasPermission( string fPPermission )
    {
        return RootPermission.HasPermission( fPPermission );
    }
	
	void AddPermission( string fPPermission, PermissionTypeN type = PermissionTypeN.DISALLOW )
    {
        RootPermission.AddPermission( fPPermission, type);
    }
	
	void ClearPermissions()
    {
        delete RootPermission;

        RootPermission = new ref FPPermission( Data.SSteam64ID, NULL );
    }
	
	void UpdatePlayerDataN()
    {
        if ( IdentityPlayer == NULL ) return;

        Data.IPingMin = IdentityPlayer.GetPingMin();
        Data.IPingMax = IdentityPlayer.GetPingMax();
        Data.IPingAvg = IdentityPlayer.GetPingAvg();
        
        Data.SSteam64ID = IdentityPlayer.GetPlainId();
        Data.SGUID = IdentityPlayer.GetId();
        Data.SName = IdentityPlayer.GetName();

        if ( PlayerObject == NULL ) return;

        PlayerDataN.Load( Data, PlayerObject );
    }
	
	void NewData( ref PlayerDataN newData )
    {
        Data = newData;
    }
	
	void ~FPPlayer()
    {
        delete RootPermission;
    }
	
	string GetGUID()
    {
        return Data.SGUID;
    }
	
	string GetSteam64ID()
    {
        return Data.SSteam64ID;
    }

    string GetName()
    {
        return Data.SName;
    }
	
}