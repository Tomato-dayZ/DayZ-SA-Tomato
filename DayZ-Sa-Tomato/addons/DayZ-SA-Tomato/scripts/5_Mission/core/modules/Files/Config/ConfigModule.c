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
class ConfigModule
{
	void ConfigModule()
	{
		
	}
	
	void Init()
	{
		GetFileHandler().CheckAndCreateFiles();
		GetFileHandler().RegisterNewconfig("Setup", "true");
		
		//Horde Message
		GetFileHandler().RegisterNewconfig("Horde_Message", "true",);
		GetFileHandler().RegisterNewconfig("Horde_Message_Location", "custom", "Horde appeared near {Location}");
		
		//Welcome Message
		GetFileHandler().RegisterNewconfig("Welcome_Message", "false",);
		GetFileHandler().RegisterNewconfig("Welcome_Message_Join", "custom", "{Player} just joined the Server");
		
		// Kill Feed
		GetFileHandler().RegisterNewconfig("KillFeed_LogToFile", "false");
		
		GetFileHandler().RegisterNewconfig("KillFeed_Message_Suicide", "false",);
		GetFileHandler().RegisterNewconfig("KillFeed_Suicide", "custom", "{Killed} took his own life");
	
		GetFileHandler().RegisterNewconfig("KillFeed_Message_PlayerHand", "false",);
		GetFileHandler().RegisterNewconfig("KillFeed_ByPlayerHand", "custom", "{Killed} murdered by {Killer} with his Hands");
		
		GetFileHandler().RegisterNewconfig("KillFeed_Message_PlayerWeapon", "false",);
		GetFileHandler().RegisterNewconfig("KillFeed_ByPlayerWeapon", "custom", "{Killed} murdered by {Killer} with Weapon {Weapon} from {Distance}m");
		
		GetFileHandler().RegisterNewconfig("KillFeed_Message_Zombie", "false",);
		GetFileHandler().RegisterNewconfig("KillFeed_Zombie", "custom", "{Killed} died by a zombie");
		
		GetFileHandler().RegisterNewconfig("KillFeed_Message_Animal", "false",);
		GetFileHandler().RegisterNewconfig("KillFeed_Animal", "custom", "{Killed} died by a Wild Animal");
		
		GetFileHandler().RegisterNewconfig("KillFeed_Message_Unkown", "false",);
		GetFileHandler().RegisterNewconfig("KillFeed_Unknown", "custom", "{Killed} died");
		
		GetFileHandler().ConfigInitialize();
		
    
	}
	
}