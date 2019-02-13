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
class HordeModule
{
	 
	
	void HordeModule()
	{
		GetDayZGame().Event_OnRPC.Insert( this.ReceiveRPC );
	}
	
	void Spawn(vector horde_pos, int Spawned_Horde = 50, int Spawned_Distance = 50 , string name = "", PlayerIdentity sender = NULL)
	{
		if ( GetGame().IsServer() ) 
		{
			vector hdynamic_pos; 
			for(int hor = 0; hor < Spawned_Horde; hor++) 
			{ 
				float ha = Math.RandomFloat(0.4, 1.0) * 2 * Math.PI; 
				float hr = Spawned_Distance * Math.Sqrt(Math.RandomFloat(0.4, 1.0)); 
				hdynamic_pos = horde_pos; 
				hdynamic_pos[0] = hdynamic_pos[0]+(hr * Math.Cos(ha)); 
				hdynamic_pos[2] = hdynamic_pos[2]+(hr * Math.Sin(ha)); 
				hdynamic_pos[1] = GetGame().SurfaceY(hdynamic_pos[0], hdynamic_pos[2]) + 0.3; 
				GetGame().CreateObject(R_Horde.GetRandomElement(), hdynamic_pos, false, true);
				
			}
			if(name == "")
				{
					TL().status(sender, "Horde Spawned at Position: " + horde_pos.ToString(false));
				}else{
					if (GetFileHandler().IsConfig("Horde_Message"))
						{
							string msg = GetFileHandler().GetConfig("Horde_Message_Location");
							int count = msg.Replace("{Location}", name);
							GetGame().ChatPlayer(msg);
							TL().status(sender, msg);	
						}
						TL().status(sender, "Horde Spawned at Location : " + name);	
				}
		}else{
			ScriptRPC Rpc = new ScriptRPC();
			Rpc.Write(horde_pos);
			Rpc.Write(Spawned_Horde);
			Rpc.Write(Spawned_Distance);
			Rpc.Write(name);
			Rpc.Send(NULL, M_RPCs.M_Admin_Horde, true, NULL);
		}
		
		
	}
	
	void ReceiveRPC( PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx ) 
	{
		switch(rpc_type)
		{
			
			case M_RPCs.M_Admin_Horde:
				vector HPos;	//Vector Postition
				int HCount;	//Vector Postition
				int HDist;	//Vector Postition
				string name;
				ctx.Read(HPos);
				ctx.Read(HCount);
				ctx.Read(HDist);
				ctx.Read(name);
					if ( GetGame().IsServer() ) 
						{
							Spawn(HPos, HCount, HDist,name, sender);
						}	
					
			break;
		}
	}
	
	protected ref TStringArray R_Horde = 
	{ 
	"ZmbF_BlueCollarFat_Green", 
	"ZmbF_BlueCollarFat_Red", 
	"ZmbF_BlueCollarFat_White", 
	"ZmbF_CitizenANormal_Beige", 
	"ZmbF_CitizenANormal_Blue", 
	"ZmbF_CitizenANormal_Brown", 
	"ZmbF_CitizenBSkinny", 
	"ZmbF_Clerk_Normal_Blue", 
	"ZmbF_Clerk_Normal_Green", 
	"ZmbF_Clerk_Normal_Red", 
	"ZmbF_Clerk_Normal_White", 
	"ZmbF_DoctorSkinny", 
	"ZmbF_HikerSkinny_Blue", 
	"ZmbF_HikerSkinny_Green", 
	"ZmbF_HikerSkinny_Grey", 
	"ZmbF_HikerSkinny_Red", 
	"ZmbF_JoggerSkinny_Blue", 
	"ZmbF_JoggerSkinny_Brown", 
	"ZmbF_JoggerSkinny_Green", 
	"ZmbF_JoggerSkinny_Red", 
	"ZmbF_JournalistNormal_Blue", 
	"ZmbF_JournalistNormal_Green", 
	"ZmbF_JournalistNormal_Red", 
	"ZmbF_JournalistNormal_White", 
	"ZmbF_MechanicNormal_Beige", 
	"ZmbF_MechanicNormal_Green", 
	"ZmbF_MechanicNormal_Grey", 
	"ZmbF_MechanicNormal_Orange", 
	"ZmbF_MilkMaidOld_Beige", 
	"ZmbF_MilkMaidOld_Black", 
	"ZmbF_MilkMaidOld_Green", 
	"ZmbF_MilkMaidOld_Grey", 
	"ZmbF_NurseFat", 
	"ZmbF_ParamedicNormal_Blue", 
	"ZmbF_ParamedicNormal_Green", 
	"ZmbF_ParamedicNormal_Red", 
	"ZmbF_PatientOld", 
	"ZmbF_PoliceWomanNormal", 
	"ZmbF_ShortSkirt_beige", 
	"ZmbF_ShortSkirt_black", 
	"ZmbF_ShortSkirt_brown", 
	"ZmbM_VillagerOld_White", 
	"ZmbM_VillagerOld_Green", 
	"ZmbM_SurvivorDean_Black", 
	"ZmbM_SoldierVest", 
	"ZmbM_SoldierHelmet", 
	"ZmbM_SoldierAlice", 
	"ZmbM_SkaterYoung_Grey", 
	"ZmbM_SkaterYoung_Blue", 
	"ZmbM_priestPopSkinny", 
	"ZmbM_PolicemanFat", 
	"ZmbM_PatrolNormal_Summer", 
	"ZmbM_ParamedicNormal_Green", 
	"ZmbM_ParamedicNormal_Black", 
	"ZmbM_OffshoreWorker_Orange", 
	};
}	
	