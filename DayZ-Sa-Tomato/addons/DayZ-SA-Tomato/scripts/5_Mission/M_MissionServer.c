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
modded class MissionServer
{
	protected ref PermissionBase m_PermissionBase;
	protected ref ConfigModule m_ConfigModule;
	protected ref TeleportModule m_TeleportModule;
	protected ref FileHandler m_FileHandler;
	protected ref HordeModule m_HordeModule;
	protected bool m_bLoaded;
	//ref LogHandler m_LogHandler;
    ref DevTeleport devTeleport;
	ref AdminMenu adminMenu;
	ref DevCam devCam;
	ref TeleportData Tdata;
	ref ChatModules m_ChatModule;
	//admin list
	ref PlayerModule PModule;
	PlayerBase Admin = NULL;
	void MissionServer()
	{
		//m_LogHandler = new ref LogHandler();
		m_FileHandler = new ref FileHandler();
		m_HordeModule = new ref HordeModule();
		m_PermissionBase = new ref PermissionBase;
		m_ConfigModule = new ref ConfigModule;
		m_ChatModule = new ref ChatModules;
		m_TeleportModule = new ref TeleportModule;
	    Print( "Dayz-Sa-Tomato initialized .." );
	    devTeleport = new DevTeleport();
	    PModule = new PlayerModule();
		adminMenu = new AdminMenu();
		devCam = new DevCam();
		//Tdata = new TeleportData();
	}

	void ~MissionServer()
	{
		
		delete PModule;
		delete adminMenu;
	    delete m_PermissionBase;
		Print( "CommunityOfflineServer::~CommunityOfflineServer()" );
	}
	
	
	
	override void OnEvent(EventType eventTypeId, Param params) 
	{
		super.OnEvent(eventTypeId,params);
		//PlayerIdentity identity;
		switch(eventTypeId)
		{
			case ChatMessageEventTypeID:
			 Print("Chat Event");
			 ChatMessageEventParams chat_params = ChatMessageEventParams.Cast(params);
			 //chat_params.param1 == 0 && 
			 if (chat_params.param2 != "") //trigger only when channel is Global == 0 and Player Name does not equal to null
				{
					Param4<int,string,string,string> request_info = new Param4<int,string,string,string>(chat_params.param1, chat_params.param2, chat_params.param3, chat_params.param4);
					GetChatModule().ChatHandler(request_info); //Send the param to Admintools
				}
			break;
		}
	}
	
	
	override void TickScheduler(float timeslice)
	{
		GetGame().GetWorld().GetPlayerList(m_Players);
		if( m_Players.Count() == 0 ) return;
		for(int i = 0; i < SCHEDULER_PLAYERS_PER_TICK; i++)
		{
			if(m_currentPlayer >= m_Players.Count() )
			{
				m_currentPlayer = 0;
			}

			PlayerBase currentPlayer = PlayerBase.Cast(m_Players.Get(m_currentPlayer));
			string PlayerName;
			PlayerIdentity PlayerIdent;
			string PlayerSteam64ID;
			vector PlayerPos;
			
			PlayerIdent = currentPlayer.GetIdentity();
			PlayerName = PlayerIdent.GetName();
			PlayerSteam64ID = PlayerIdent.GetPlainId();
			PlayerPos = currentPlayer.GetPosition();
			currentPlayer.OnTick();

			if(GetFileHandler().HasPermission("DisableStamina", PlayerIdent)
				{
					currentPlayer.GetStaminaHandler().SyncStamina(1000,1000);
					currentPlayer.GetStatStamina().Set(currentPlayer.GetStaminaHandler().GetStaminaCap());
				}

			m_currentPlayer++;
			
			
		}
	}
	
	void SendPosTOAdmins()
	{
		int m_currentPlayer1;
		array<Man> players = new array<Man>;
		GetGame().GetPlayers( players );
				
		for (int i = 0; i < players.Count(); ++i)
		{
			if(m_currentPlayer1 >= m_Players.Count() )
			{
				m_currentPlayer1 = 0;
			}
			PlayerBase currentPlayer = PlayerBase.Cast(m_Players.Get(m_currentPlayer1));
			string PlayerName;
			PlayerIdentity PlayerIdent;
			string PlayerSteam64ID;
			PlayerIdent = currentPlayer.GetIdentity();
			PlayerName = PlayerIdent.GetName();
			PlayerSteam64ID = PlayerIdent.GetPlainId();
			vector pos;
				
			pos = currentPlayer.GetPosition();
			//SendPosToAdmins(PlayerName, pos);
			m_currentPlayer1++;
			
			int m_currentPlayer2;
			array<Man> players1 = new array<Man>;
			GetGame().GetPlayers( players1 );
					
			for (int i1 = 0; i1 < players1.Count(); ++i1)
			{
				if(m_currentPlayer2 >= m_Players.Count() )
			{
				m_currentPlayer2 = 0;
			}
				PlayerBase currentPlayer1 = PlayerBase.Cast(m_Players.Get(m_currentPlayer2));
				string AdminPlayerName1;
				PlayerIdentity AdminIdent1;
				string PlayerSteam64ID1;
				AdminIdent1 = currentPlayer1.GetIdentity();
				AdminPlayerName1 = AdminIdent1.GetName();
				PlayerSteam64ID1 = AdminIdent1.GetPlainId();
				if (GetFileHandler().HasPermission("Admin", AdminIdent1))
				{
					ScriptRPC PPos = new ScriptRPC();
					PPos.Write(PlayerName);
					PPos.Write(pos);
					PPos.Send(NULL, M_RPCs.M_Admin_Menu_Map_Player, false, AdminIdent1);
				}
				m_currentPlayer2++;
			}
				
				
		}
	}
	
	
	PlayerBase IsAdminID(string name, PlayerIdentity ID ) 
	{
		GetGame().GetWorld().GetPlayerList(m_Players);
		array<Man> players = new array<Man>;
		GetGame().GetPlayers( players );
		PlayerIdentity CurIdent;
		string id;
		int Count = 0;
		for (int i = 0; i < players.Count(); ++i)
		{
			PlayerBase currentPlayer = PlayerBase.Cast(m_Players.Get(i));
			CurIdent = currentPlayer.GetIdentity();
			if(GetFileHandler().HasPermission("Admin", ID) && CurIdent.GetName() == name )
			{
				Admin 		  = currentPlayer;
				break;				
			}else
			{
			Admin = NULL;
			}
			Count ++;
		}
		return Admin; 
	}

	ref Man GetPlayerFromIdentity( PlayerIdentity identity ) 
	{
		foreach( ref Man manBase : m_Players ) 
		{
			if ( manBase.GetIdentity().GetPlayerId() == identity.GetPlayerId() ) 
			{
				return manBase;
			}
		}
		return NULL;
	}

	override void OnInit()
	{
		super.OnInit();
		m_ConfigModule.Init();
		m_TeleportModule.Init();
		
	}

	override void OnMissionStart()
	{
		super.OnMissionStart();

        m_PermissionBase.OnStart();
	}

	override void OnMissionFinish()
	{
		m_PermissionBase.OnFinish();

        super.OnMissionFinish();
	}

	override void OnPreloadEvent(PlayerIdentity identity, out bool useDB, out vector pos, out float yaw, out int queueTime)
	{
        super.OnPreloadEvent( identity, useDB, pos, yaw, queueTime );
		GetFileHandler().GetPlayerByIdentity( identity );
    }
	
	override void InvokeOnConnect( PlayerBase player, PlayerIdentity identity)
	{
        super.InvokeOnConnect( player, identity );
		GetFileHandler().GetPlayerByIdentity( identity );

        GetGame().SelectPlayer( identity, player );
    } 
	
	override void InvokeOnDisconnect( PlayerBase player )
	{
        GetFileHandler().PlayerLeft( player.GetIdentity() );
		
		super.InvokeOnDisconnect( player );
    } 
	
    void OnMissionLoaded()
    {

    }

	override void OnUpdate( float timeslice )
	{
	    super.OnUpdate( timeslice );
		
		m_PermissionBase.OnUpdate( timeslice );
	}

	void  CLogInfo(string log) 
	{
		int year, month, day, hour, minute, second;
		GetYearMonthDay(year, month, day);
		GetHourMinuteSecond(hour, minute, second);
	
		string date = day.ToStringLen(2) + "." + month.ToStringLen(2) + "." + year.ToStringLen(4) + " " + hour.ToStringLen(2) + ":" + minute.ToStringLen(2);
		Print(log);
		if(FileExist("$profile:\\TomatoLog"))
		{
			FileHandle file = OpenFile("$profile:\\TomatoLog\\Info.log", FileMode.APPEND);
			if (file != 0)
			{
				FPrintln(file, "[" + date + "] - " + log);
				CloseFile(file);
			}
		}else{
			MakeDirectory("$profile:\\TomatoLog");
			FileHandle file2 = OpenFile("$profile:\\TomatoLog\\Info.log", FileMode.APPEND);
			if (file != 0)
			{
				FPrintln(file, "[" + date + "] - " + log);
				CloseFile(file);
			}
		}
	}
	
	void  CLogRPC(string log) 
	{
		int year, month, day, hour, minute, second;
		GetYearMonthDay(year, month, day);
		GetHourMinuteSecond(hour, minute, second);
	
		string date = day.ToStringLen(2) + "." + month.ToStringLen(2) + "." + year.ToStringLen(4) + " " + hour.ToStringLen(2) + ":" + minute.ToStringLen(2);
		Print(log);
		if(FileExist("$profile:\\TomatoLog"))
		{
			FileHandle file = OpenFile("$profile:\\TomatoLog\\RPC.log", FileMode.APPEND);
			if (file != 0)
			{
				FPrintln(file, "[" + date + "] - " + log);
				CloseFile(file);
			}
		}else{
			MakeDirectory("$profile:\\TomatoLog");
			FileHandle file2 = OpenFile("$profile:\\TomatoLog\\RPC.log", FileMode.APPEND);
			if (file != 0)
			{
				FPrintln(file, "[" + date + "] - " + log);
				CloseFile(file);
			}
		}
	}
	
	void  CLogStartup(string log) 
	{
		int year, month, day, hour, minute, second;
		GetYearMonthDay(year, month, day);
		GetHourMinuteSecond(hour, minute, second);
	
		string date = day.ToStringLen(2) + "." + month.ToStringLen(2) + "." + year.ToStringLen(4) + " " + hour.ToStringLen(2) + ":" + minute.ToStringLen(2);
		Print(log);
		if(FileExist("$profile:\\TomatoLog"))
		{
			FileHandle file = OpenFile("$profile:\\TomatoLog\\Startup.log", FileMode.APPEND);
			if (file != 0)
			{
				FPrintln(file, "[" + date + "] - " + log);
				CloseFile(file);
			}
		}else{
			MakeDirectory("$profile:\\TomatoLog");
			FileHandle file2 = OpenFile("$profile:\\TomatoLog\\Startup.log", FileMode.APPEND);
			if (file != 0)
			{
				FPrintln(file, "[" + date + "] - " + log);
				CloseFile(file);
			}
		}
	}
	
	void  CLogDebug(string log) 
	{
		int year, month, day, hour, minute, second;
		GetYearMonthDay(year, month, day);
		GetHourMinuteSecond(hour, minute, second);
	
		string date = day.ToStringLen(2) + "." + month.ToStringLen(2) + "." + year.ToStringLen(4) + " " + hour.ToStringLen(2) + ":" + minute.ToStringLen(2);
		Print(log);
		if(FileExist("$profile:\\TomatoLog"))
		{
			FileHandle file = OpenFile("$profile:\\TomatoLog\\Debug.log", FileMode.APPEND);
			if (file != 0)
			{
				FPrintln(file, "[" + date + "] - " + log);
				CloseFile(file);
			}
		}else{
			MakeDirectory("$profile:\\TomatoLog");
			FileHandle file2 = OpenFile("$profile:\\TomatoLog\\Debug.log", FileMode.APPEND);
			if (file != 0)
			{
				FPrintln(file, "[" + date + "] - " + log);
				CloseFile(file);
			}
		}
	}
	
	
    // void InitHive()
	// {
		// Hive oHive = GetHive();
		
		// if( !oHive )
		// {
			// oHive = CreateHive();
		// }

		// if( oHive )
		// {
			// oHive.InitOffline();
		// }
	// }
}
