# DayZ SA Tomato

Dayz Standalone UI Admin Tool



## Changelog

See CHANGELOG.md

## News

## 15.12.2018 23:00

### Fixed

- For 1.0 Update (make sure to kopy the Key from Keys folder again !)

### Added 

- Teleport Locations Check the Config/List Folder u can add your own Locations to it (Adding Locations from ingame does not work since filewrite is bugged at the moment)

 ### next up
 - 


#### If Someone got the mod to work on a 3rd Party hoster Cantact me or join https://discord.gg/Svgz48m

##  Notes

You can do with this tool what you want as the licence says if you add any features to it i would appreciate if you would share your code so that everyone can benefit from it.


You could cantact me per mail at DayZ-SA-Tomato@Primary-Network.de
Or @Discord https://discord.gg/qqjwVXV

### Installing

0. Check out this Link if you are using a 3rd party hoster they changed there Wiki since a user asked them how to Install this mod probs to them https://trugaming.com/wiki/index.php?title=DayZ#Server_Side_Mods hoefully this helps a little bit 
1. Copy DayZ-SA-Tomato to your Server/Client main Folder
2. Copy SchnitzelPommes.bikey to your Servers keys folder
3. Make sure YourServerFolder/DayZ-Sa-Tomato/Config/Admins.txt file exist (You can delete it Client side)
4. If You need to use the mod folder with an @ Make sure to create DayZ-Sa-Tomato Folder with the Config Folder in it or it wont load Admins.txt and TpLocations file 
5. Make sure when step 3 completed add your Steam64ID to this file(for every ID 1 line)
6. Set start param -mod=DayZ-SA-Tomato at Server/Client 
7. If not exist Add -profiles=D:\YourProfileFolderMaybe/DayzServer/Log and -scrAllowFileWrite To your server Parameters
![alt text](https://steamuserimages-a.akamaihd.net/ugc/43117016076707122/9D374D1F7933C13B477EE6792A3735D9FFAC74B4/)


Also Available in the Steam workshop (not updated all the time)
https://steamcommunity.com/sharedfiles/filedetails/?id=1575615457






## Test and Use

Start your Server and login

Check your Server log for 

```
Adding Admin:
```

If this Meessage appears the server loadet the tool if not you did something wrong

```
In Game press "M" Key
```
If Your Client is configured with the mod a Message will appear @chat
If Your Server is also configured correct and Admins.txt Contains your id The Ui will open

## Features

* **In Game** - M Key brings up the UI
* **In Game** - Insert Key go to Camera Mode Insert again to tp to Cursor
* **In Game** - N Key to Teleport to Cursor

------------

* **Commands Tab** - Toggle In Game Keys
* **Commands Tab** - Self Heal
* **Commands Tab** - Daytime
* **Commands Tab** - Nighttime
* **Commands Tab** - Spawn Car repaired and filled
* **Commands Tab** - Refill nearest Car

------------

* **Spawn Tab** - Item/AI/Building Spawning 

------------

* **Player Tab** - Player List
* **Player Tab** - Tp Players and tp to Players
* **Player Tab** - Strip Player
* **Player Tab** - Position of Player
* **Player Tab** - Disable Stamina for specific Player 
* **Player Tab** - Heal Player
* **Player Tab** - Kill Player

------------

* **Map Tab** - Shows Location of all Players on the Map


### Known Issues
* **Spwan Tab** - Item Preview (right side not working)
* **Spwan Tab** - Building spawning in ground
* **Player Tab** - Blood Energy not showing correctly (sometimes it does)
* **Player Tab** - Send Message not working

## License

This project is licensed under the GNU v3 License - see the [LICENSE.md](LICENSE.md) file for details

## Acknowledgments

* Everyone on the Forums/Discord who answered question (not only me but everyone)
* DayZCommunityOfflineMode for Snippets

