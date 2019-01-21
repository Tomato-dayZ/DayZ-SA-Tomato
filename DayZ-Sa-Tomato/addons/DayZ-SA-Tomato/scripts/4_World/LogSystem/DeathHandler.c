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
class DeathHandler
{
	string KillFile = "$profile:\\Dayz-Sa-Tomato\\Log\\Kills.txt";

    PlayerBase      KPlayerBase;                       
    PlayerIdentity  KPlayerIdentity;                       
    string          KName;                    
    vector          KPos;                
    int             Dist;                   
    EntityAI        KW;                  
    ItemBase        KWItemBase;                 
    string          KWName;                    
    

    PlayerBase      VPlayerBase;                      
    PlayerIdentity  VPlayerIdentity;                       
    string          VName;                    
    vector          VPos;                
	
	string OutMessage;
	
	void DeathHandler()
	{
		
	}
	
	void log(string log)
	{
		if ( GetGame().IsServer() ) 
		{
			if(FileExist(KillFile))
			{
				FileHandle file = OpenFile(KillFile, FileMode.APPEND);
				if (file != 0)
				{
					FPrintln(file, LineIn() + log);
					CloseFile(file);
				}
			}else
			{
				MakeDirectory(KillFile);
				if (file != 0)
				{
					FPrintln(file, LineIn() + log);
					CloseFile(file);
				}
				Print("Could not create Folder/File " + KillFile);
			}
		}
	}
	
	string LineIn()
	{
		int year, month, day, hour, minute, second;
		GetYearMonthDay(year, month, day);
		GetHourMinuteSecond(hour, minute, second);
		string date = day.ToStringLen(2) + "." + month.ToStringLen(2) + "." + year.ToStringLen(4) + " " + hour.ToStringLen(2) + ":" + minute.ToStringLen(2);
		string LineIn = "[" + date + "] - ";
		return LineIn;
	}
	void ConnectHandler(PlayerIdentity player)
	{
		string msg;
		if (GetFileHandler().IsConfig("Welcome_Message"))
			{
				msg = GetMessage(GetFileHandler().GetConfig("Welcome_Message_Join"), VName);
				int count = msg.Replace("{Player}", player.GetName());
				GetGame().ChatPlayer(0, msg);
			}
	}
	void KilledHandler(Object killer, PlayerBase pbKilled)
	{
		KPlayerBase        = NULL;                     
        // Victim 
        VPlayerBase        	= PlayerBase.Cast(pbKilled);                     
        VPlayerIdentity    	= VPlayerBase.GetIdentity();   
        VName     			= VPlayerIdentity.GetName();       
  
        OutMessage     = "";                       
		
		IsMan(killer);
		SelectKillType();
		IsAnimal(killer);
		Send();
        
	}
	
	void Send()
	{
        if (OutMessage != "")
        {
            GetGame().ChatPlayer(0, OutMessage);
        }
	}
	
	void IsAnimal(Object killer)
	{
		if (killer.IsKindOf("AnimalBase"))
		{			
			if (GetFileHandler().IsConfig("KillFeed_Message_Animal"))
			{
				OutMessage = GetMessage(GetFileHandler().GetConfig("KillFeed_Animal"), VName);
			}
		}
		else if (killer.IsKindOf("ZombieBase"))
		{
			if (GetFileHandler().IsConfig("KillFeed_Message_Zombie")) //TODO
			{
				OutMessage = GetMessage(GetFileHandler().GetConfig("KillFeed_Zombie"), VName); 
			}
		}
		else
		{	
			if (GetFileHandler().IsConfig("KillFeed_Message_Unknown"))
			{
				OutMessage = GetMessage(GetFileHandler().GetConfig("KillFeed_Unknown"), VName);
			}
		}
        
	}
	
	void SelectKillType()
	{
		if (KPlayerBase)
        {
				if (VPlayerBase == KPlayerBase)
				{
					if (GetFileHandler().IsConfig("KillFeed_Message_Suicide"))
					{
						OutMessage = GetMessage(GetFileHandler().GetConfig("KillFeed_Suicide"), VName);
					}
					
				}
			else
			{
				
				KPlayerIdentity        = NULL;
				KPlayerIdentity        = KPlayerBase.GetIdentity();
				KName     = KPlayerIdentity.GetName();
				KPos = KPlayerBase.GetPosition();
				VPos = VPlayerBase.GetPosition();
				Dist    = vector.Distance(VPos, KPos);
				KW   = KPlayerBase.GetHumanInventory().GetEntityInHands();
				
				if (KW.IsItemBase())
				{
					KWItemBase = ItemBase.Cast(KW);
					KWName = KWItemBase.GetDisplayName();
					
					if (KPlayerBase.GetDisplayName() == KWName)
					{
						if(GetFileHandler().IsConfig("KillFeed_LogToFile"))
						{
							string Lmessage = GetMessage(GetFileHandler().GetConfig("KillFeed_ByPlayerHand"), VName, KName)
							log(Lmessage);
						}
						
						if (GetFileHandler().IsConfig("KillFeed_Message_PlayerHand"))
						{
							OutMessage = GetMessage(GetFileHandler().GetConfig("KillFeed_ByPlayerHand"), VName, KName);
						}
						
					}
					else
					{
						if(GetFileHandler().IsConfig("KillFeed_LogToFile"))
						{
							Lmessage = GetMessage(GetFileHandler().GetConfig("KillFeed_ByPlayerWeapon"), VName, KName, KWName, Dist.ToString())
							log(Lmessage);
						}
						
						if (GetFileHandler().IsConfig("KillFeed_Message_PlayerWeapon") 
						{
							OutMessage = GetMessage(GetFileHandler().GetConfig("KillFeed_ByPlayerWeapon"), VName, KName, KWName, Dist.ToString());
						}
						
						
					}
				}
				else
				{
				}
			}
        }
	}
	
	
	void IsMan(Object killer)
	{
		if (killer.IsMan())
        {
            if (killer.IsKindOf("SurvivorBase"))
            {
                KPlayerBase = PlayerBase.Cast(killer);
            }
        }
        else
        {
			
            if (killer.IsItemBase())
            {
				KWItemBase = ItemBase.Cast(killer);
                KPlayerBase = PlayerBase.Cast(KWItemBase.GetHierarchyRootPlayer());
            }
        }
	}
	
	void KilledHandlerOld(Object killer, PlayerBase pbKilled)
	{
		string Killername;
		string Killedname;
        SurvivorBase sbKilled = SurvivorBase.Cast(pbKilled);
        if (killer.IsMan()) {

            Man manKiller = Man.Cast(killer);

            if (sbKilled.GetPFullName() == manKiller.GetIdentity().GetName()) {

				string KilledBySuicide = GetFileHandler().GetConfig("KillFeed_Suicide");
				Killedname = sbKilled.GetPFullName();
				GetGame().ChatPlayer( 0, GetMessage(KilledBySuicide, Killedname));
                // TL.all(GetMessage(KilledBySuicide, Killedname));	
                // TL.all(sbKilled.GetPFullName() + " took his own life");

            } else 
			{
                SurvivorBase sbKiller = SurvivorBase.Cast(killer);
				string KilledByPlayer = GetFileHandler().GetConfig("KillFeed_ByPlayer");
				Killername = sbKiller.GetPFullName();
				Killedname = sbKilled.GetPFullName();
				GetGame().ChatPlayer( 0, GetMessage(KilledByPlayer, Killedname , Killername));
                // TL.all(GetMessage(KilledByPlayer, Killedname, Killername));
            }
        } else 
		{
            string KilledByBleed = GetFileHandler().GetConfig("KillFeed_Bleeding_Zombie");
			Killedname = sbKilled.GetPFullName();
			GetGame().ChatPlayer( 0, GetMessage(KilledByBleed, Killedname)); 
			// TL.all(GetMessage(KilledByBleed, Killedname));
        }
	}
	
	string GetMessage(string input, string killed, string killer = "" , string weap = "", string dist = "")
	{
		int count = input.Replace("{Killed}", killed);
		if(killer != "")
		{
			count = input.Replace("{Killer}", killer);
		}
		
		if(weap != "")
		{
			count = input.Replace("{Weapon}", weap);
		}
		
		if(dist != "")
		{
			count = input.Replace("{Distance}", dist);
		}
		
		
		return input;
	}
	
}

// ref DeathHandler Tomato_DeathHandler;

// ref DeathHandler GetDeathHandler()
// {
    // if( !Tomato_DeathHandler )
    // {
        // Tomato_DeathHandler = new ref DeathHandler();
    // }

    // return Tomato_DeathHandler;
// }