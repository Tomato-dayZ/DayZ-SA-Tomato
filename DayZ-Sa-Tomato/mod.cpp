class CfgMods
{
	class DayZSATomato
	{
		dir = "DayZ-SA-Tomato";
		picture = "";
		action = "";
		hideName = 1;
		hidePicture = 1;
		name = "DayZ-SA-Tomato";
		credits = "";
		author = "DayZ-SA-Tomato";
		authorID = "0"; 
		version = "1.0"; 
		extra = 0;
		type = "mod";
		
		dependencies[] = {"Game", "World", "Mission"};
		
		class defs
		{
			class gameScriptModule
			{
				value = "";
				files[] = {"com/DayZ-SA-Tomato/scripts/3_Game"};
			};

			class worldScriptModule
			{
				value = "";
				files[] = {"com/DayZ-SA-Tomato/scripts/4_World"};
			};

			class missionScriptModule
			{
				value = "";
				files[] = {"com/DayZ-SA-Tomato/scripts/5_Mission"};
			};
		}
	};
};
