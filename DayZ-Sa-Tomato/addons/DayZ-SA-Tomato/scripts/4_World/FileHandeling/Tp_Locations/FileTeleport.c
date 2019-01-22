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
class FileTeleport
{
	ref array< ref FileTeleport > Children;
	string LocationName;
	vector LocationPos;
	bool ok = false;
	ref FileTeleport Parent;
	void FileTeleport( string name, ref FileTeleport parent = NULL, vector pos = Vector.Zero())
    {
        if(parent == NULL)
		{
			ok = true;
		}
		LocationName = name;
		LocationPos = pos;
        Parent = parent;
		//Print("Teleport Location = " + LocationName + " LocationPos = " + LocationPos);
		GetDayZGame().Event_OnRPC.Insert( this.ReceiveRPC );
        Children = new ref array< ref FileTeleport >;
    }
	
	void AddNewLocation(string PosName, vector AdminPos)
	{
		for ( int i = 0; i < Children.Count(); i++ )
		{
			if ( PosName == Children[i].LocationName )
			{
				return;
			}
		}
		//PosName = stringParam.param1;
		
		vector PosOut;
		PosOut = Vector(AdminPos[0], 0.0, AdminPos[2]);
		string stringout = PosOut.ToString(false);
		AddToFile(PosName, stringout);
		Load();							
			
	}
	
	void AddToFile(string name, string pos)
	{
		FileHandle file = OpenFile( GetFileHandler().TeleportFile, FileMode.APPEND );
		if ( file != 0 )
		{
			FPrintln(file, name + " = " + pos);
		}
		 CloseFile(file);
	}
	
	void AddChilds(string name, vector pos)
	{
		ref FileTeleport nChild = NULL;
		for ( int i = 0; i < Children.Count(); i++ )
		{
			if ( name == Children[i].LocationName )
			{
				nChild = Children[i];
				break;
			}
		}
			
			if ( nChild == NULL )
			{
				nChild = new FileTeleport( name, this, pos);

				Children.Insert( nChild );
			}
		
	}
	
	void Load()
	{
		Children.Clear();
		FileHandle file = OpenFile( GetFileHandler().TeleportFile, FileMode.READ );
		if ( file != 0 )
		{
			string line, LocationNameNew;
			vector LocationPosNew;
			array<string> TeleportLine = new array<string>;
			array<string> TeleportLineCut = new array<string>;
			array<string> TeleportPositions = new array<string>;
			float X, Y;
			while ( FGets( file, line ) > 0 )
			{
				TeleportLineCut.Clear();
				TeleportPositions.Clear();
				line.Split(" = ", TeleportLineCut);
				int len = TeleportLineCut[1].LengthUtf8(); 
				len = len - 2;
				string LocationPosPreNew = TeleportLineCut[1].Substring(2, len);
				LocationPosPreNew.Split(" ", TeleportPositions);
				X = TeleportPositions[0].ToFloat();
				Y = TeleportPositions[2].ToFloat();
				
				LocationPosNew = Vector(X, 0.0, Y);
				LocationNameNew = TeleportLineCut[0];
				
				NewTeleport(LocationNameNew, LocationPosNew);
				
			}
			 CloseFile(file);
		}
	}
	
	void NewTeleport(string name, vector loc)
	{
		ref FileTeleport nChild = NULL;
		for ( int i = 0; i < Children.Count(); i++ )
		{
			if ( name == Children[i].LocationName )
			{
				nChild = Children[i];
				break;
			}
		
		}
			if ( nChild == NULL )
			{
				nChild = new FileTeleport( name, this, loc);
				Children.Insert( nChild );
			}
	}
	
	void ReceiveRPC( PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx ) 
	{
		if(ok)
		{
			int ListCount = 0;
			PlayerBase Admin;
			//PlayerIdentity AdminIdentity;
			
			switch(rpc_type)
			{
				case M_RPCs.M_Admin_Menu_Teleport_Write:
					//Param1<string> stringParam;
					string PosName;	
					vector AdminPos;	
					ctx.Read(PosName);
					ctx.Read(AdminPos);
					Print("");
					Print("Adding Pos");
					Print(PosName);
					Print(AdminPos);
					for ( int i = 0; i < Children.Count(); i++ )
					{
						if ( PosName == Children[i].LocationName )
						{
							return;
						}
					}
					//PosName = stringParam.param1;
						if ( GetGame().IsServer() ) 
							{
									vector PosOut;
									PosOut = Vector(AdminPos[0], 0.0, AdminPos[2]);
									string stringout = PosOut.ToString(false);
									AddToFile(PosName, stringout);
									Load();							
							}
				break;
				
				
			}
		}
	}
	
}