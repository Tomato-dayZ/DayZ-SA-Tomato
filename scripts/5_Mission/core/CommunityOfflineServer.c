/*
	DayZ SA Tomato Gui Admin tool for DayZ Standalone. Contact DayZ-SA-Tomato@Primary-Network.de
	Copyright (C) 2018  DayZ-SA-Tomato
	
	This file is part of DayZ SA Tomato.
	Originally from DayZCommunityOfflineMode
	Link : https://github.com/Arkensor/DayZCommunityOfflineMode
	
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
class CommunityOfflineServer : MissionServer
{
    protected bool m_bLoaded;
    ref DevTeleport devTeleport;
	ref DevCam devCam;
	ref AdminMenu adminMenu;
	protected float m_LogInTimerLength = 1;
	//admin list
	PlayerBase Admin = NULL;
	protected ref map<string, string> m_AdminList;
	static ref map<string, string> m_StaminaList;
	protected string m_AdminListPath = "$CurrentDir:\\DayZ-SA-Tomato\\Config\\";
	void CommunityOfflineServer()
	{
	    Print( "CommunityOfflineServer::CommunityOfflineServer()" );
	    m_bLoaded = false;
	    devTeleport = new DevTeleport();
	    devCam = new DevCam();
		adminMenu = new AdminMenu();
	}

	void ~CommunityOfflineServer()
	{
	    Print( "CommunityOfflineServer::~CommunityOfflineServer()" );
	}

	
	//Create Mags And Custom Guns
	void addMags(PlayerBase player, string mag_type, int count)
	{
		if (count < 1)
			return;

		EntityAI mag;

		for (int i = 0; i < count; i++) {
			mag = player.GetInventory().CreateInInventory(mag_type);
		}

		player.SetQuickBarEntityShortcut(mag, 1, true);
	}
	EntityAI SVD(int ground, PlayerBase player)
	{
		EntityAI item;
		ItemBase itemBs
		vector NewPosition;
		vector OldPosition;
		if (ground == 1)
		{
			OldPosition = player.GetPosition();
			NewPosition[0] = OldPosition[0] + 1.5;
			NewPosition[1] = OldPosition[1] + 0.1;
			NewPosition[2] = OldPosition[2] + 1.5;
			EntityAI gun = GetGame().CreateObject( "SVD", NewPosition, false, true );
			gun.GetInventory().CreateAttachment("PSO1Optic");
			gun.GetInventory().CreateAttachment("ImprovisedSuppressor");
			gun.GetInventory().CreateAttachment("GhillieAtt_Tan");
		}else
		{
			EntityAI gun1 = player.GetHumanInventory().CreateInHands("SVD");
			gun1.GetInventory().CreateAttachment("PSO1Optic");
			gun1.GetInventory().CreateAttachment("ImprovisedSuppressor");
			gun1.GetInventory().CreateAttachment("GhillieAtt_Tan");
			addMags(player, "Mag_SVD_10Rnd", 3);
		}
		return gun;
}
	
	override void OnEvent(EventType eventTypeId, Param params) 
	{
		super.OnEvent(eventTypeId,params);
		
		
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

			if (m_StaminaList.Contains(PlayerName))
				{
					currentPlayer.GetStaminaHandler().SyncStamina(1000,1000);
					currentPlayer.GetStatStamina().Set(currentPlayer.GetStaminaHandler().GetStaminaCap());
					
				}
				
			if (IsAdmin(PlayerName, PlayerSteam64ID ))
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
			CLogDebug("CommunityOfflineServer - SendPosTOAdmins1/2() - Name :" + PlayerName + "pos : " + pos);
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
				if (IsAdmin(AdminPlayerName1, PlayerSteam64ID1 ))
				{
					CLogDebug("CommunityOfflineServer - SendPosTOAdmins2/2() - Name :" + PlayerName + "pos : " + pos);
					ScriptRPC PPos = new ScriptRPC();
					PPos.Write(PlayerName);
					PPos.Write(pos);
					PPos.Send(NULL, M_RPCs.M_Admin_Menu_Map_Player, false, AdminIdent1);
				}
				m_currentPlayer2++;
			}
				
				
		}
	}
	void SendPlayerListToAdmins()
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
			CLogDebug("CommunityOfflineServer - SendPlayerListToAdmins() - Name :" + PlayerName + "m_currentPlayer1 : " + m_currentPlayer1);
			//SendPosToAdmins(PlayerName, pos);
			m_currentPlayer1++;
			
			int m_currentPlayer2 = 0;
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
				if (IsAdmin(AdminPlayerName1, PlayerSteam64ID1 ))
				{
					ScriptRPC PList = new ScriptRPC();
					PList.Write(PlayerName);
					PList.Send(NULL, M_RPCs.M_Admin_Menu_Player_List, false, AdminIdent1);
				}
				m_currentPlayer2++;
			}
				
				
		}
	}
	
	void AddStamina(string name)
	{
		m_StaminaList.Insert(name, "null");
	}
	
	void RemoveStamina(string name)
	{
		m_StaminaList.Remove(m_StaminaList.GetKeyByValue(name));
	}
	bool StaminaContains(string name)
	{
		if (m_StaminaList.Contains(name))
			{
				return true;	
			}
		return false;
	}
	
	
	
	// bool  IsAdmin( string name, string ID ) 
	// {
		// array<Man> players = new array<Man>;
					// GetGame().GetPlayers( players );
		// for (int i = 0; i < players.Count(); ++i)
			// {
				// if (players.Get(i).GetIdentity().GetName() == name && m_AdminList.Contains(ID))
				// {
					// return true;	
				// }
			// }
			// return false;
	// }
	
	
	
	PlayerBase IsAdminID(string name, string ID ) 
	{
		GetGame().GetWorld().GetPlayerList(m_Players);
		array<Man> players = new array<Man>;
		GetGame().GetPlayers( players );
		//PlayerBase currentPlayer;
		int Count = 0;
		for (int i = 0; i < players.Count(); ++i)
		{
			if(Count >= m_Players.Count() )
				{
					Count = 0;
				}
			PlayerBase currentPlayer = PlayerBase.Cast(m_Players.Get(Count));
			CLogDebug("Current Player : " + currentPlayer.GetIdentity().GetName() + "Count : " + Count.ToString());
			if (currentPlayer.GetIdentity().GetName() == name && m_AdminList.Contains(ID))
			{
				Admin 		  = currentPlayer;
				//AdminIdentity = Admin.GetIdentity();
				//AdminUID 	  = AdminIdentity.GetPlainId();
				CLogDebug("Returning True for : " + players.Get(i).GetIdentity().GetName() );
				return Admin;	
			}else
			{
			CLogDebug("Returning False 1" );
			Admin = NULL;
			}
			Count ++;
		}
		return Admin; 
	}
	
	bool IsAdmin(string name, string ID ) 
	{
		GetGame().GetWorld().GetPlayerList(m_Players);
		array<Man> players = new array<Man>;
		GetGame().GetPlayers( players );
		//PlayerBase currentPlayer;
		int Count = 0;
		for (int i = 0; i < players.Count(); ++i)
		{
			if(Count >= m_Players.Count() )
				{
					Count = 0;
				}
			PlayerBase currentPlayer = PlayerBase.Cast(m_Players.Get(Count));
			if (currentPlayer.GetIdentity().GetName() == name && m_AdminList.Contains(ID))
			{
				Admin 		  = currentPlayer;
				return true;	
			}else
			Count ++;
		}
		return false; 
	}

	ref Man GetPlayerFromIdentity( PlayerIdentity identity ) 
	{
		foreach( ref Man manBase : m_Players ) 
		{
			Print( "Getter: " + manBase  + " : " + manBase.GetIdentity().GetName() + " : " + manBase.GetIdentity().GetId() + ":" + manBase.GetIdentity().GetPlainId());
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
        SetupWeather();
		
		//Admin list Insert from text
		m_AdminList    = new map<string, string>; //UID, name
		m_StaminaList    = new map<string, string>; //UID, name
		FileHandle AdminUIDSFile = OpenFile(m_AdminListPath + "Admins.txt", FileMode.READ);
		if (AdminUIDSFile != 0)
		{
			string line_content = "";
			while ( FGets(AdminUIDSFile,line_content) > 0 )
			{
				m_AdminList.Insert(line_content,"null"); //UID , NAME
				Print("Adding Admin: "+ line_content + " To the Admin List!");
			}
			CloseFile(AdminUIDSFile);
		}

	}

	override void OnMissionStart()
	{
		super.OnMissionStart();
	
    
	}

	override void OnMissionFinish()
	{


		super.OnMissionFinish();
	}

    void OnMissionLoaded()
    {

    }

	override void OnUpdate( float timeslice )
	{
	    super.OnUpdate( timeslice );

        if( !m_bLoaded && !GetDayZGame().IsLoading() )
        {
            m_bLoaded = true;
            OnMissionLoaded();
        }
	}

    static void SetupWeather()
    {
        //Offical DayZ SA weather code
        Weather weather = g_Game.GetWeather();

        weather.GetOvercast().SetLimits( 0.0 , 2.0 );
        weather.GetRain().SetLimits( 0.0 , 2.0 );
        weather.GetFog().SetLimits( 0.0 , 2.0 );

        weather.GetOvercast().SetForecastChangeLimits( 0.0, 0.0 );
        weather.GetRain().SetForecastChangeLimits( 0.0, 0.0 );
        weather.GetFog().SetForecastChangeLimits( 0.0, 0.0 );

        weather.GetOvercast().SetForecastTimeLimits( 1800 , 1800 );
        weather.GetRain().SetForecastTimeLimits( 600 , 600 );
        weather.GetFog().SetForecastTimeLimits( 600 , 600 );

        weather.GetOvercast().Set( 0.0, 0, 0 );
        weather.GetRain().Set( 0.0, 0, 0 );
        weather.GetFog().Set( 0.0, 0, 0 );

        weather.SetWindMaximumSpeed( 50 );
        weather.SetWindFunctionParams( 0, 0, 1 );
    }

	override void OnPreloadEvent(PlayerIdentity identity, out bool useDB, out vector pos, out float yaw, out int queueTime)
	{
		if (GetHive())
		{
			queueTime = m_LogInTimerLength;
		}
		else
		{
			queueTime = m_LogInTimerLength;
		}
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
	
	
    void InitHive()
	{
		Hive oHive = GetHive();
		
		if( !oHive )
		{
			oHive = CreateHive();
		}

		if( oHive )
		{
			oHive.InitOffline();
		}
	}
}
