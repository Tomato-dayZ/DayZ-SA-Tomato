class FileHandler
{
	//Main Folder
	string MainFolder = "$profile:\\Dayz-Sa-Tomato";
	string MainFolderPath = "$profile:\\Dayz-Sa-Tomato\\";
	//Config Folder and Files
	string ConfigFolder = MainFolderPath + "Config";
	string ConfigFolderPath = MainFolderPath + "Config\\";
	string ConfigFile = ConfigFolderPath + "Config.txt";
	string AdminsFile = ConfigFolderPath + "Admins.txt";
	//Customization Folder and Files
	string CustomizationFolder = MainFolderPath + "Customization";
	string CustomizationFolderPath = MainFolderPath + "Customization\\";
	string TeleportFile = CustomizationFolderPath + "Teleport_Locations.txt";
	
	
	
	void FileHandler()
	{
		CheckAndCreateFiles();
	}
	void CheckAndCreateFiles()
	{
		CheckFolder(MainFolder);
		CheckFolder(ConfigFolder);
		CheckFolder(CustomizationFolder);
		
		CheckFile(ConfigFile);
		CheckFile(AdminsFile);
		CheckFile(TeleportFile);
	}
	
	void CheckFile(string File)
	{
		if(FileExist(File))
		{
			GetServerMission().Print("FileHandler : File " + File + " found!");
		}else
		{
			FileHandle file = OpenFile(File, FileMode.APPEND);
			if (file != 0)
				{
					FPrintln(file, " ");
					CloseFile(file);
				}
			if(FileExist(File))
				{
					if(File == TeleportFile)
					{
						CreateTeleportFile();
					}else
					{
					GetServerMission().Print("FileHandler : File " + File + " Created");
					}
				}
		}
	}
	
	
	void CheckFolder(string Folder)
	{
		if(FileExist(Folder))
		{
			GetServerMission().Print("FileHandler : Folder " + Folder + " found!");
		}else
		{
			MakeDirectory(Folder);
			if(FileExist(Folder))
				{
					GetServerMission().Print("FileHandler : Folder " + Folder + " Created");
				}
		}
	}
	
	void CreateTeleportFile()
	{
		FileHandle file = OpenFile(TeleportFile, FileMode.APPEND);
		if (file != 0)
			{
				FPrintln(file, "prison;2651.42 0.0 1395.8");
				FPrintln(file, "mogilevka;7572.65 0.0 5182.3");
				FPrintln(file, "stary;6192.39 0.0 7666.5");
				FPrintln(file, "msta;11206.6 0.0 5398.70");
				FPrintln(file, "solni;13436.5 0.0 6158.7");
				FPrintln(file, "cherno;6350.99 0.0 2666.12");
				FPrintln(file, "elektro;10432.1 0.0 2218.56");
				FPrintln(file, "berez;12661.4 0.0 9465.03");
				FPrintln(file, "tisy;1890.45 0.0 13704.6");
				FPrintln(file, "gorka;9678.94 0.0 8828.93");
				FPrintln(file, "balota;4546.92 0.0 2416.4");
				FPrintln(file, "vybor;3916.85 0.0 8795.59");
				FPrintln(file, "vybora;4107.80 0.0 11205.29");
				FPrintln(file, "severo;8318.51 0.0 12743.4");
				FPrintln(file, "severor;7986.21 0.0 12737.1");
				CloseFile(file);
			}
	}
}