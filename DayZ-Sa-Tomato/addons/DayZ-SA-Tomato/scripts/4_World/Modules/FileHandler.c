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
class FileHandler
{
	//Main Folder
	string MainFolder = "$profile:\\Tomato_Profiles";
	string MainFolderPath = "$profile:\\Tomato_Profiles\\";
	//Config Folder and Files
	string ConfigFolder = MainFolderPath + "Config";
	string ConfigFolderPath = MainFolderPath + "Config\\";
	string ConfigFile = ConfigFolderPath + "Config.txt";
	//Players Folder
	string PlayersFolderPath = ConfigFolderPath + "Players\\";
	//Log Folder and Files
	string LogFolder = MainFolderPath + "Log";
	string LogFolderPath = MainFolderPath + "Log\\";
	string LErrorFile = LogFolderPath + "Error.txt";
	string LDebugFile = LogFolderPath + "Debug.txt";
	string LInfoFile = LogFolderPath + "Info.txt";
	string LAdminFile = LogFolderPath + "Admin.txt";
	string LKillsFile = LogFolderPath + "Kills.txt";
	//Customization Folder and Files
	string CustomizationFolder = MainFolderPath + "Customization";
	string CustomizationFolderPath = MainFolderPath + "Customization\\";
	string TeleportFile = CustomizationFolderPath + "Teleport_Locations.txt";
	bool IsExit = false;
	ref FileConfig RootConfig;
	ref FileTeleport RootTeleport;
	//ref FilePlayers RootPlayers;

	// NEW BEGINN 
	ref array< ref FPPlayer > FPPlayers;
    ref FPPermission RootPermission;
	// NEW END
	
	

	
	void FileHandler()
	{
		RootConfig = new ref FileConfig( "ROOT" );
		RootTeleport = new ref FileTeleport( "ROOT" );
		//RootPlayers = new ref FilePlayers( "ROOT" );
	
	// NEW BEGINN 
	FPPlayers = new ref array< ref FPPlayer >;
    RootPermission = new ref FPPermission( "ROOT" );
	// NEW END

	}
	
	// NEW BEGINN 
	
	void SetPermission(string perm, PermissionTypeN type, string id) //Identity.GetID()
	{
		Print("FileHandler");
		for ( int i = 0; i < FPPlayers.Count(); i++ )
        {
            if ( FPPlayers[i].GetGUID() == id )
            {
				Print("FileHanddler Player Founf");
                FPPlayers[i].SetPermission(perm , type);
				//return FPPlayers[i].HasPermission( fPPermission );
            }
        }
	}
	
	array< ref FPPlayer > GetPlayers( ref array< string > guids = NULL )
    {
        if ( guids == NULL )
        {
            return FPPlayers;
        }

        array< ref FPPlayer > tempArray = new array< ref FPPlayer >;

        for ( int i = 0; i < guids.Count(); i++ )
        {
            for ( int k = 0; k < FPPlayers.Count(); k++ )
            {
                if ( guids[i] == FPPlayers[k].GetGUID() )
                {
                    tempArray.Insert( FPPlayers[k] );
                }
            }
        }

        return tempArray;
    }

    void SetPlayers( ref array< ref FPPlayer > players )
    {
        FPPlayers.Clear();

        // This doesn't work??? wtf
        //FPPlayers.Copy( players );

        for ( int i = 0; i < players.Count(); i++ )
        {
            FPPlayers.Insert( players[i] );
        }
    }

    void AddPlayers( ref array< ref FPPlayer > players )
    {
        for ( int i = 0; i < players.Count(); i++ )
        {
            FPPlayers.Insert( players[i] );
        }
    }

    void RegisterPermission( string fPPermission, PermissionTypeN type = PermissionTypeN.DISALLOW )
    {
        RootPermission.AddPermission( fPPermission, type );
    }

    ref array< string > ToPermArray()
    {
        ref array< string > data = new ref array< string >;
        RootPermission.ToPermArray( data );
        return data;
    }

    ref FPPermission GetRootPermission()
    {
        return RootPermission;
    }

    bool HasPermission( string fPPermission, PlayerIdentity player = NULL )
    {
        if ( !GetGame().IsMultiplayer() ) return true;

        if ( player == NULL ) 
        {
            if ( ClientAuthPlayer == NULL )
            {
                return true;
            }

            return ClientAuthPlayer.HasPermission( fPPermission );
        } 

        for ( int i = 0; i < FPPlayers.Count(); i++ )
        {
            if ( FPPlayers[i].GetGUID() == player.GetId() )
            {
                return FPPlayers[i].HasPermission( fPPermission );
            }
        }

        return false;
    }

    ref FPPlayer PlayerJoined( PlayerIdentity player )
    {
        ref PlayerDataN data = new ref PlayerDataN;

        if ( player )
        {
            data.SName = player.GetName();
            data.SGUID = player.GetId();
            data.SSteam64ID = player.GetPlainId();
        } else 
        {
            data.SName = "Offline Mode";
            data.SGUID = "N/A";
        }

        ref FPPlayer auPlayer = new ref FPPlayer( data );

        auPlayer.IdentityPlayer = player;

        auPlayer.CopyPermissions( RootPermission );

        auPlayer.Load();

        FPPlayers.Insert( auPlayer );

        return auPlayer;
    }

    void PlayerLeft( PlayerIdentity player )
    {
		ref PlayerDataN PData = new ref PlayerDataN;
        if ( player == NULL ) return;

        for ( int i = 0; i < FPPlayers.Count(); i++ )
        {
            ref FPPlayer auPlayer = FPPlayers[i];
            
            if ( auPlayer.GetSteam64ID() == player.GetPlainId() )
            {
                auPlayer.Save();

                if ( GetGame().IsServer() && GetGame().IsMultiplayer() )
                {
                    PData = SerializePlayer( auPlayer );
					ScriptRPC Adding = new ScriptRPC();
					Adding.Write(PData);
					Adding.Send(NULL, M_RPCs.M_Admin_Player_RemovePlayer, true, NULL);
					//GetRPCManager().SendRPC( "PermissionsFramework", "RemovePlayer", new Param1< ref PlayerDataN >( SerializePlayer( auPlayer ) ), true );
                }

                FPPlayers.Remove( i );
                break;
            }
        }
    }

    // void DebugPrint()
    // {
        // Print( "Printing all authenticated players!" );
        // for ( int i = 0; i < FPPlayers.Count(); i++ )
        // {
            // FPPlayers[i].DebugPrint();
        // }
    // }

    ref FPPlayer GetPlayerByGUID( string guid )
    {
        ref FPPlayer auPlayer = NULL;

        for ( int i = 0; i < FPPlayers.Count(); i++ )
        {
            if ( FPPlayers[i].GetGUID() == guid )
            {
                auPlayer = FPPlayers[i];
                break;
            }
        }

        if ( auPlayer == NULL )
        {
            ref PlayerDataN data = new ref PlayerDataN;
            
            data.SGUID = guid;

            auPlayer = new ref FPPlayer( data );

            FPPlayers.Insert( auPlayer );
        }

        return auPlayer;
    }

    ref FPPlayer GetPlayerByIdentity( PlayerIdentity ident )
    {
        if ( ident == NULL ) return NULL;

        ref FPPlayer auPlayer = NULL;

        for ( int i = 0; i < FPPlayers.Count(); i++ )
        {
            if ( FPPlayers[i].GetGUID() == ident.GetId() )
            {
                auPlayer = FPPlayers[i];
                break;
            }
        }

        if ( auPlayer == NULL )
        {
            auPlayer = PlayerJoined( ident );
        }

        return auPlayer
    }

    ref FPPlayer GetPlayer( ref PlayerDataN data )
    {
        if ( data == NULL ) return NULL;
        
        ref FPPlayer auPlayer = NULL;

        for ( int i = 0; i < FPPlayers.Count(); i++ )
        {
            if ( FPPlayers[i].GetGUID() == data.SGUID )
            {
                auPlayer = FPPlayers[i];
                break;
            }
        }

        if ( auPlayer == NULL )
        {
            auPlayer = new ref FPPlayer( data );

            FPPlayers.Insert( auPlayer );
        }

        auPlayer.NewData( data );

        auPlayer.ToPermData();

        return auPlayer;
    }

	// NEW END
	void AddLocation(string PosName, vector AdminPos)
	{
		RootTeleport.AddNewLocation(PosName, AdminPos)
	}
	void LoadTeleport()
	{
		RootTeleport.Load();
	}
	
	void RegisterNewconfig( string CfgName , string type, string data = "")
    {
		Print("RegisterNewconfig Data = " + data)
        RootConfig.RegisterNewconfig( CfgName, type , data);
    }
	
	void PrintAllConfigs()
	{
		RootConfig.PrintAll();
	}
	
	void ConfigInitialize()
	{
		RootConfig.ConfigInitialize();
	}
	
	
	bool IsConfig( string CfgName)
    {
        bool iscfg = false;
		iscfg = RootConfig.IsConfig(CfgName);
		return iscfg;
    }
	
	string GetConfig( string CfgName)
    {
        string getConf = "";
		getConf = RootConfig.GetConfigData(CfgName);
		return getConf;
    }
	
	void CheckAndCreateFiles()
	{
		Print("DayZ-Sa-Tomato Checking File system");
		CheckFolder(MainFolder);
		CheckFolder(ConfigFolder);
		CheckFolder(CustomizationFolder);
		CheckFolder(LogFolder);
		
		CheckFile(LKillsFile);
		CheckFile(TeleportFile);
		CheckFile(LErrorFile);
		CheckFile(LDebugFile);
		CheckFile(LInfoFile);
		CheckFile(LAdminFile);
	}
	
	
	
	void CheckFile(string File)
	{
		if(FileExist(File))
		{
			Print("FileHandler : File " + File + " found!");
		}else
		{
			FileHandle file = OpenFile(File, FileMode.APPEND);
			if (file != 0)
				{
					FPrintln(file, "");
					CloseFile(file);
				}
			if(FileExist(File))
				{
					if(File == TeleportFile)
					{
						CreateTeleportFile();
					}else
					{
					Print("FileHandler : File " + File + " Created");
					}
				}
		}
	}
	
	void SetConfigType(string name, string stype)
	{
		ConfigType type
		if(stype == "true"){type = ConfigType.true;}
		else if (stype == "false"){type = ConfigType.false;}
		else if (stype == "custom"){type = ConfigType.custom;}
		
		for ( int i = 0; i < RootConfig.Children.Count(); i++ )
            {
				if ( name == RootConfig.Children[i].ConfigName )
				{
					RootConfig.Children[i].SetConfigType(type);
				}
			}
		
		RootConfig.WriteToFile();
	}
	
	void SetConfigData(string name, string data)
	{
		for ( int i = 0; i < RootConfig.Children.Count(); i++ )
            {
				if ( name == RootConfig.Children[i].ConfigName )
				{
					RootConfig.Children[i].SetConfigData(data);
				}
			}
			RootConfig.WriteToFile();
	}
	
	void CheckFolder(string Folder)
	{
		if(FileExist(Folder))
		{
			Print("FileHandler : Folder " + Folder + " found!");
		}else
		{
			MakeDirectory(Folder);
			if(FileExist(Folder))
				{
					Print("FileHandler : Folder " + Folder + " Created");
				}
		}
	}
	
	void CreateTeleportFile()
	{
		FileHandle file = OpenFile(TeleportFile, FileMode.APPEND);
		if (file != 0)
			{
				FPrintln(file, "Prison Island = 2651.42 0.0 1395.8");
				FPrintln(file, "Mogilevka = 7572.65 0.0 5182.3");
				FPrintln(file, "Stary Sobor = 6192.39 0.0 7666.5");
				FPrintln(file, "Msta = 11206.6 0.0 5398.70");
				FPrintln(file, "Solnichniy = 13436.5 0.0 6158.7");
				FPrintln(file, "Chernogorsk = 6350.99 0.0 2666.12");
				FPrintln(file, "Elektrogorsk = 10432.1 0.0 2218.56");
				FPrintln(file, "Berezino = 12661.4 0.0 9465.03");
				FPrintln(file, "Tisy = 1890.45 0.0 13704.6");
				FPrintln(file, "Gorka = 9678.94 0.0 8828.93");
				FPrintln(file, "Balota = 4546.92 0.0 2416.4");
				FPrintln(file, "Vybor = 3916.85 0.0 8795.59");
				FPrintln(file, "Severograd = 8318.51 0.0 12743.4");
				FPrintln(file, "North West Airfield = 4835.59 0.0 9667.72");
				FPrintln(file, "Green Mountain = 3752.08 0.0 6002.94");
				FPrintln(file, "Zelenogorsk = 2542.18 0.0 4994.26");
				FPrintln(file, "Tisy Military Base = 1599.15 0.0 14166.66");
				FPrintln(file, "Pavlovo Military Base = 2047.82 0.0 3293.36");
				CloseFile(file);
			}
	}
}
ref FileHandler Tomato_FileHandler;

ref FileHandler GetFileHandler()
{
    if( !Tomato_FileHandler )
    {
        Tomato_FileHandler = new ref FileHandler();
    }

    return Tomato_FileHandler;
}