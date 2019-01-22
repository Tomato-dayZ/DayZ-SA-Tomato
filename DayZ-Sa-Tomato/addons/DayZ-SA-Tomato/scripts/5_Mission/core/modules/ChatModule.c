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
typedef Param4<int, string, string, string> ChatParams;
class ChatModules
{
	
	protected ref map<string, int> m_Commands;
	
	void ChatModules()
	{
		m_Commands = new map<string,int>; //Command, length
		
		m_Commands.Insert("/test",1);
		m_Commands.Insert("/test1",1);
		m_Commands.Insert("/opme",1);
		//m_Commands.Insert("/split",7);
	}
	
	void ChatHandler( Param request_info )
	{
		ChatParams chat_params = ChatParams.Cast(request_info);
		if (chat_params)
		{
			array<Man> players = new array<Man>;
			GetGame().GetPlayers( players );
			
			PlayerBase Admin;
			PlayerIdentity AdminIdentity;
			string AdminUID;
			string AdminName;

			PlayerBase selectedPlayer;
			PlayerIdentity selectedIdentity;
			string selectedUID;
			
			string chatLine = chat_params.param3;
			string strMessage;
			Param1<string> Msgparam;

			for (int i = 0; i < players.Count(); ++i)
			{
				if (players.Get(i).GetIdentity().GetName() == chat_params.param2 && GetFileHandler().HasPermission("Admin", players.Get(i).GetIdentity() ) )
				{
					Admin 		  = players.Get(i);
					AdminIdentity = Admin.GetIdentity();
					AdminUID 	  = AdminIdentity.GetPlainId();
					AdminName = AdminIdentity.GetName();
				}else if(chatLine == "/opme"  && GetFileHandler().IsConfig("Setup"))
				{
					Admin 		  = players.Get(i);
					AdminIdentity = Admin.GetIdentity();
					GetFileHandler().SetPermission("Admin", PermissionTypeN.ALLOW, AdminIdentity.GetId());
					GetFileHandler().SetConfigType("Setup", "false");
					//TL().player(AdminIdentity, "Admin Set please relog to save Config !");
					return;
				}
			}

			if (Admin && AdminUID != "")
			{
				if (chatLine.Contains("/"))
				{
					ref array<string> chatData = CheckCommand(chatLine);
					string cCommand, cData;
					if (chatData != NULL)
					{
						cCommand = chatData.Get(0);
						cData    = chatData.Get(1);
					} else { cCommand = "UnknownCommand" }

					switch(cCommand)
					{	
						case "/test":
							GetAdminMenuManager().MessageOpen(AdminIdentity, "This is a Test Message which is not that short")
							TL().player(AdminIdentity, "Message Show")
						break;
						
						case "/test1":
							g_Game.GetUIManager().CloseMenu(7001);
							TL().player(AdminIdentity, "Message Close")
						break;
					}
				}
			}
		}
		
	}
	ref array<string> CheckCommand(string CommandLine)
	{
		ref array<string> ret = new array<string>;
		string strRplce,mKey;
		int cmdLength;

		strRplce = CommandLine;

		for (int i = 0; i < m_Commands.Count(); ++i)
		{
			mKey 	  = m_Commands.GetKey(i);
			cmdLength = m_Commands.Get(mKey);

			if (CommandLine.Contains(mKey))
			{
				strRplce.Replace(mKey + " ","");
				ret.Insert(mKey); //0 = Command 1 = Data
				if (strRplce != "")
				{
					ret.Insert(strRplce);
				}
				return ret;
			}
		}
		return NULL;
}
	
}
ref ChatModules Tomato_ChatModule;

ref ChatModules GetChatModule()
{
    if( !Tomato_ChatModule )
    {
        Tomato_ChatModule = new ref ChatModules();
    }

    return Tomato_ChatModule;
}