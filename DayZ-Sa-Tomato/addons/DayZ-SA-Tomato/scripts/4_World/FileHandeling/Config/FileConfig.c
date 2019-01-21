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
class FileConfig
{
	ref array< ref FileConfig > Children;
	string ConfigName;
    ConfigType IsConfigType;
	string ConfigData;
	ref FileConfig Parent;
	void FileConfig( string name, ConfigType type = true, string data = "", ref FileConfig parent = NULL )
    {
        ConfigName = name;
		IsConfigType = type;
		ConfigData = data;
        Parent = parent;
		
        IsConfigType = ConfigType.next;
        if ( Parent == NULL )
        {
            IsConfigType = ConfigType.true;
        }

        Children = new ref array< ref FileConfig >;
    }
	
	void WriteToFile()
	{
		array<string> ConfigNames = new array<string>;
		array<string> ConfigTypes = new array<string>;
		string type;
		for ( int i = 0; i < Children.Count(); i++ )
            {
				ConfigNames.Insert(Children[i].ConfigName);
				
				if(Children[i].IsConfigType == ConfigType.true)
				{
					type = "1";
				}else if(Children[i].IsConfigType == ConfigType.custom)
				{
					type = Children[i].ConfigData;
				}else
				{
					type = "0";
				}
				ConfigTypes.Insert(type);
            }
			
		FileHandle file = OpenFile( GetFileHandler().ConfigFile, FileMode.WRITE );
		
		if ( file != 0 )
        {

            for ( int t = 0; t < ConfigNames.Count(); t++ )
            {
				string WriteData = ConfigNames[t] + " = " + ConfigTypes[t];
                FPrintln( file, WriteData );
            }
            
            CloseFile(file);
            
            Print("Wrote Config to File" + GetFileHandler().ConfigFile);
        } else
        {
            Print("Could not open File " + GetFileHandler().ConfigFile + " to Write Config to!");
        }
	}
	
	void ~FileConfig()
    {
        //delete Children;
    }
	
	bool IsConfig( string Configname )
    {
        for ( int i = 0; i < Children.Count(); i++ )
            {
                if ( Children[i].ConfigName == Configname && Children[i].IsConfigType == ConfigType.true)
                {
                    return true;
                }
            }
		return false;
    }
	
	string GetConfigData( string Configname )
    {
		string ReturnData = "";
        for ( int i = 0; i < Children.Count(); i++ )
            {
                if ( Children[i].ConfigName == Configname ) //&& Children[i].IsConfigType == ConfigType.custom
                {
					ReturnData = Children[i].ConfigData;
                    return ReturnData;
                }
            }
		return ReturnData;
    }
	
	void SetConfigType(ConfigType type)
	{

		IsConfigType = type;
		//GetFileHandler().RootConfig.WriteToFile()

	}
	
	void SetConfigData(string data)
	{
		ConfigData = data;
		//GetFileHandler().RootConfig.WriteToFile()
	}
	
	void PrintAll()
	{
		for ( int i = 0; i < Children.Count(); i++ )
				{
					Print(" ");
					Print("Printing Child  with number " + i);
					Print("Name = " + Children[i].ConfigName);
					Print("ConfigType = " + Children[i].IsConfigType);
					Print("ConfigData = " + Children[i].ConfigData);
					Print("Parent = " + Children[i].Parent);
					Print("End Of Child with Number " + i);
					Print(" ");
				}
	}
	
	void ConfigInitialize()
	{
		array<string> ConfigLine = new array<string>;
		array<string> ConfigStringCut = new array<string>;
		FileHandle file = OpenFile( GetFileHandler().ConfigFile, FileMode.READ );
		if ( file != 0 )
		{
			Print("ConfigInitialize - File Found");
			string line;

			while ( FGets( file, line ) > 0 )
			{
				ConfigLine.Insert( line );
			}

			CloseFile( file );

			if(Children.Count() == ConfigLine.Count() )
			{
				for ( int i = 0; i < ConfigLine.Count(); i++ )
				{
					ConfigStringCut.Clear();
					ConfigLine[i].Split( " = ", ConfigStringCut );
					ConfigType type;
					string configData = "";
					if(ConfigLine.Count() == Children.Count())
					{
						int len = ConfigStringCut[1].LengthUtf8(); 
						len = len - 2;
						string ConfigTypeCut = ConfigStringCut[1].Substring(2, len);
						if(ConfigTypeCut == "1")
						{
							type = ConfigType.true;
						}else if(ConfigTypeCut == "0")
						{
							type = ConfigType.false;
						}else
						{
							type = ConfigType.custom;
							configData = ConfigTypeCut;
							
						}
					}else 
					{
						if(ConfigStringCut[1] == "= 1")
						{
							type = ConfigType.true;
						}else if(ConfigStringCut[1] == "= 0")
						{
							type = ConfigType.false;
						}else
						{
							type = ConfigType.custom;
							configData = ConfigTypeCut;
						}
					}
					//Function needet TODO !
				Children[i].SetConfigType(type);
				Children[i].SetConfigData(configData);
				}
				WriteToFile();
			}else
			{
				Print("Config File has Wrong number of Configs recreateing file !");
				WriteToFile();
			}
		} else
		{
			Print( "File. " + GetFileHandler().ConfigFile + " Not found Creating new one");
			WriteToFile();
		}
	}
	
	// void LoadConfig( string ConfigString, ConfigType ConfigTypefunc = ConfigType.next )
    // {

        // array<string> ConfigStringCut = new array<string>;
        // ConfigString.Split( " = ", ConfigStringCut );

        // ConfigType type;
        // if (ConfigStringCut.Count() == 2 ) // Loaded will be 1
        // {
            // if ( ConfigStringCut[1].Contains( "1" ) )
            // {
                // type = ConfigType.true;
            // } else if ( ConfigStringCut[1].Contains( "0" ) )
            // {
                // type = ConfigType.false;
            // } else 
            // {
                // type = ConfigType.false;
            // }
        // } else if ( ConfigStringCut.Count() < 2 ) //New One will Be Count 1 make Type what it should be
        // {
            // type = ConfigTypefunc;

        // } else {
            // Print( "LoadConfig Error Given String : " + ConfigString + " and should be Config = 1 ");
            // return;
        // }
        
        // CheckIfNewConfig(ConfigStringCut[0], type);
        
    // }
	void RegisterNewconfig(string name, string stype, string configdata = "")
	{
		Print("RegisterNewConfig Data = " + configdata)
		ConfigType type;
		if(stype == "true"){type = ConfigType.true;}
		else if(stype == "false"){type = ConfigType.false;}
		else{type = ConfigType.custom;}
		CheckIfNewConfig(name, type, configdata);
	}
	
	void CheckIfNewConfig( string name, ConfigType type, string configData = "" )
    {
		Print("CheckIfNewConfig Data = " + configData)
        ref FileConfig nChild = NULL;

        for ( int i = 0; i < Children.Count(); i++ )
        {
            if ( name == Children[i].ConfigName )
            {
                nChild = Children[i];
                break;
            }
        }
            
        if ( nChild == NULL )
        {
            nChild = new FileConfig( name, type, configData, this );
            //nChild.IsConfigType = type;
			// nChild.ConfigData = configData;
            Children.Insert( nChild );
			for ( i = 0; i < Children.Count(); i++ )
			{
				if(Children[i].ConfigName == name)
				{
					Children[i].SetConfigType(type);
					Children[i].SetConfigData(configData);
				}
			}
        }
    }
}