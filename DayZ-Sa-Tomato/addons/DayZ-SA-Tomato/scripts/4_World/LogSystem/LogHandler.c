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

class LogHandler
{
	string LogFolderPath = GetFileHandler().LogFolderPath;
							
	
	string LineIn()
	{
		int year, month, day, hour, minute, second;
		GetYearMonthDay(year, month, day);
		GetHourMinuteSecond(hour, minute, second);
		string date = day.ToStringLen(2) + "." + month.ToStringLen(2) + "." + year.ToStringLen(4) + " " + hour.ToStringLen(2) + ":" + minute.ToStringLen(2);
		string LineIn = "[" + date + "] - ";
		return LineIn;
	}
		
		
	void LogHandler()
	{
		GetDayZGame().Event_OnRPC.Insert( this.ReceiveRPC );
	}
	
	ref PlayerBase GetPlayerBaseByName(string name)
	{
		
		array<Man> players = new array<Man>;
		
		PlayerBase selectedPlayer;
		PlayerIdentity selectedIdentity;
		
		GetGame().GetPlayers( players );
		for ( int a = 0; a < players.Count(); ++a )
			{
				selectedPlayer = PlayerBase.Cast(players.Get(a));
				selectedIdentity = selectedPlayer.GetIdentity();
				if ( selectedIdentity.GetName() == name )
					{
						return selectedPlayer;
					}
			}
			return selectedPlayer;
	}
	
	ref PlayerIdentity GetIdent(string name)
	{
		
		array<Man> players = new array<Man>;
		
		PlayerBase selectedPlayer;
		PlayerIdentity selectedIdentity;
		
		GetGame().GetPlayers( players );
		for ( int a = 0; a < players.Count(); ++a )
			{
				selectedPlayer = PlayerBase.Cast(players.Get(a));
				selectedIdentity = selectedPlayer.GetIdentity();
				if ( selectedIdentity.GetName() == name )
					{
						return selectedIdentity;
					}
			}
			return selectedIdentity;
	}
	
	void status(PlayerIdentity ident, string msg)
	{
		GetGame().RPCSingleParam( NULL, M_RPCs.M_Admin_Menu_MessageStatus, new Param1<string>( msg ), false, ident );
	}
	
	void playern(PlayerIdentity ident, string msg)
	{
		Param1<string> Msgparam = new Param1<string>( msg );
		GetGame().RPCSingleParam(NULL , ERPCs.RPC_USER_ACTION_MESSAGE, Msgparam, true, ident);
	}
	
	void player(PlayerIdentity ident, string msg)
	{
		if ( GetGame().IsServer() ) 
		{
			GetGame().RPCSingleParam(NULL, M_RPCs.M_Admin_Message, new Param1<string>(msg), true, ident);
		}else{
			GetGame().GetMission().OnEvent(ChatMessageEventTypeID, new ChatMessageEventParams(0, "", msg, ""));
			
		}
	}
	
	void playerSetup()
	{
		if ( GetGame().IsServer() ) 
		{
			
		}else{
			GetGame().RPCSingleParam(NULL, M_RPCs.M_Admin_Message_Setup, new Param1<string>(""), true, NULL);
		}
	}
	
	void all(string msg)
	{
		if ( GetGame().IsServer() ) 
		{
			
				ref array< Man > allPlayers = new ref array< Man >;
				GetGame().GetWorld().GetPlayerList(allPlayers);
				foreach( Man man : allPlayers ) 
				{
					PlayerBase playerBase = PlayerBase.Cast(man);
					playerBase.RPCSingleParam(ERPCs.RPC_USER_ACTION_MESSAGE, new Param1<string>(msg), false, playerBase.GetIdentity());
				}
		}else{
			ScriptRPC Rpc = new ScriptRPC();
			Rpc.Write(msg);
			Rpc.Send(NULL, M_RPCs.M_Admin_Log_all, true, NULL);
			}
		}
		
		void allWhite(string msg)
		{
			if ( GetGame().IsServer() ) 
			{
				
					GetGame().ChatPlayer(0, msg);
			}else{
				ScriptRPC Rpc = new ScriptRPC();
				Rpc.Write(msg);
				Rpc.Send(NULL, M_RPCs.M_Admin_Log_all_White, true, NULL);
				}
		}
	
	
	void cons(string log)
	{
		if ( GetGame().IsServer() ) 
		{
			Debug.Log(log)
		}else{
			ScriptRPC Rpc = new ScriptRPC();
			Rpc.Write(log);
			Rpc.Send(NULL, M_RPCs.M_Admin_Log_con, true, NULL);
		}
	}
	
	
	void dbug(string log)
	{
		if ( GetGame().IsServer() ) 
		{
			if(FileExist(LogFolderPath))
			{
				FileHandle file = OpenFile(LogFolderPath + "Debug.txt", FileMode.APPEND);
				if (file != 0)
				{
					FPrintln(file, LineIn() + log);
					CloseFile(file);
				}
			}else
			{
				MakeDirectory(LogFolderPath);
				if (file != 0)
				{
					FPrintln(file, LineIn() + log);
					CloseFile(file);
				}
				Print("Could not create Folder/File " + LogFolderPath + "Debug.txt");
			}
		}else
			{
				ScriptRPC Rpc = new ScriptRPC();
				Rpc.Write(log);
				Rpc.Send(NULL, M_RPCs.M_Admin_Menu_Log_Debug, true, NULL);
			}
	}
	
	void kill(string log)
	{
		if ( GetGame().IsServer() ) 
		{
			if(FileExist(LogFolderPath))
			{
				FileHandle file = OpenFile(LogFolderPath + "Kills.txt", FileMode.APPEND);
				if (file != 0)
				{
					FPrintln(file, LineIn() + log);
					CloseFile(file);
				}
			}else
			{
				MakeDirectory(LogFolderPath);
				if (file != 0)
				{
					FPrintln(file, LineIn() + log);
					CloseFile(file);
				}
				Print("Could not create Folder/File " + LogFolderPath + "Kills.txt");
			}
		}else
			{
				ScriptRPC Rpc = new ScriptRPC();
				Rpc.Write(log);
				Rpc.Send(NULL, M_RPCs.M_Admin_Menu_Log_Debug, true, NULL);
			}
	}
	
	
	
	
	void admin(string log)
	{
		if ( GetGame().IsServer() ) 
		{
			if(FileExist(LogFolderPath))
			{
				FileHandle file = OpenFile(LogFolderPath + "Admin.txt", FileMode.APPEND);
				if (file != 0)
				{
					FPrintln(file, LineIn() + log);
					CloseFile(file);
				}
			}else{
				MakeDirectory(LogFolderPath + "Admin.txt");
				if (file != 0)
				{
					FPrintln(file, LineIn() + log);
					CloseFile(file);
				}
			}
		}else
		{
			ScriptRPC Rpc = new ScriptRPC();
			Rpc.Write(log);
			Rpc.Send(NULL, M_RPCs.M_Admin_Menu_Log_Admin, true, NULL);
		}
	}
	
	void error(string log)
	{
		if ( GetGame().IsServer() ) 
		{
			if(FileExist(LogFolderPath))
			{
				FileHandle file = OpenFile(LogFolderPath + "Error.txt", FileMode.APPEND);
				if (file != 0)
				{
					FPrintln(file, LineIn() + log);
					CloseFile(file);
				}
			}else{
				MakeDirectory(LogFolderPath + "Error.txt");
				if (file != 0)
				{
					FPrintln(file, LineIn() + log);
					CloseFile(file);
				}
				Print("Could not create Folder/File " + LogFolderPath + "Error.txt");
			}
		}else
		{
			ScriptRPC Rpc = new ScriptRPC();
			Rpc.Write(log);
			Rpc.Send(NULL, M_RPCs.M_Admin_Log_error, true, NULL);
		}
	}
	
	void info(string log)
	{
		if ( GetGame().IsServer() ) 
		{
			if(FileExist(LogFolderPath))
			{
				FileHandle file = OpenFile(LogFolderPath + "Info.txt", FileMode.APPEND);
				if (file != 0)
				{
					FPrintln(file, LineIn() + log);
					CloseFile(file);
				}
			}else{
				MakeDirectory(LogFolderPath + "Info.txt");
				if (file != 0)
				{
					FPrintln(file, LineIn() + log);
					CloseFile(file);
				}
				Print("Could not create Folder/File " + LogFolderPath + "Info.txt");
			}
		}else
		{
			ScriptRPC Rpc = new ScriptRPC();
			Rpc.Write(log);
			Rpc.Send(NULL, M_RPCs.M_Admin_Log_info, true, NULL);
		}
	}

	void ReceiveRPC( PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx ) 
	{
		string msg;
		string player;
		switch(rpc_type)
		{
			case M_RPCs.M_Admin_Message:	
				Param1< string > specParams;
				ctx.Read( specParams );
				if ( GetGame().IsClient() ) 
				{
					player(sender, specParams.param1);				
				}
		
			break;
			
			case M_RPCs.M_Admin_Message_Setup:	
				//ctx.Read( specParams );
				if ( GetGame().IsServer() ) 
				{
					if(GetFileHandler().IsConfig("Setup"))
					{
						if(GetFileHandler().HasPermission("Admin", sender))
						{
							player(sender, "Admin Set Menu Should open !")
						}else{
							player(sender,"Admin not set type /opme and try again")
						}
					}
					
				}
				
			break;
			
			case M_RPCs.M_Admin_Log_info:	
				ctx.Read( msg );
				if ( GetGame().IsServer() ) 
				{
					if(GetFileHandler().HasPermission("Admin", sender))
					{
						info(msg);
					}
				}
			break;
			
			case M_RPCs.M_Admin_Log_error:	
				ctx.Read( msg );
				if ( GetGame().IsServer() ) 
				{
					if(GetFileHandler().HasPermission("Admin", sender))
					{
						error(msg);
					}
				}
			break;
			
			case M_RPCs.M_Admin_Menu_Log_Admin:	
				ctx.Read( msg );
				if ( GetGame().IsServer() ) 
				{
					if(GetFileHandler().HasPermission("Admin", sender))
					{
						admin(msg);
					}
				}
			break;
			
			case M_RPCs.M_Admin_Menu_Log_Debug:	
				ctx.Read( msg );
				if ( GetGame().IsServer() ) 
				{
					if(GetFileHandler().HasPermission("Admin", sender))
					{
						dbug(msg);
					}
				}
			break;
			
			case M_RPCs.M_Admin_Log_con:	
				ctx.Read( msg );
				if ( GetGame().IsServer() ) 
				{
					if(GetFileHandler().HasPermission("Admin", sender))
					{
						cons(msg);
					}
				}
			break;
			
			case M_RPCs.M_Admin_Log_all:	
				ctx.Read( msg );
				if ( GetGame().IsServer() ) 
				{
					if(GetFileHandler().HasPermission("Admin", sender))
					{
						all(msg);
					}
				}
			break;
			
			case M_RPCs.M_Admin_Log_all_White:	
				ctx.Read( msg );
				if ( GetGame().IsServer() ) 
				{
					if(GetFileHandler().HasPermission("Admin", sender))
					{
						allWhite(msg);
					}
				}
			break;
		}
	}
}

ref LogHandler Tomato_LogHandler;

ref LogHandler TL()
{
    if( !Tomato_LogHandler )
    {
        Tomato_LogHandler = new ref LogHandler();
    }

    return Tomato_LogHandler;
}