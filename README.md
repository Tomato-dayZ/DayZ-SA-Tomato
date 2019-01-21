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


<<<<<<< HEAD
0. If you upgrade from an older version delete all of it and start at step 1.
1. Click download, get the zip file, and open it
1. Copy DayZ-SA-Tomato to your Server AND Client main (ROOT) Folder
2. Inside "keys" folder copy SchnitzelPommes.bikey to your Servers keys folder
```
```
![alt text](https://i.ibb.co/5jcGNRQ/Screenshot-3.png)
```
```
4. include "-mod=DayZ-SA-Tomato" in Server start parameters.
5. If profiles isn't set, add "-profiles=PATH TO PROFILES FOLDER" as well then save and close.
```
```
![alt text](https://i.ibb.co/YdpXCwS/Screenshot-2.png)
```
```
6. Move the Tomato_Profiles profile folder from the mod folder's to server profiles folder. (If the folder "DayzServer/YOURPROFILESNAME/Tomato_Profiles/Config/Players/" does not exist please create it BEFORE you start your server for the first time)
```
```
![alt text](https://i.ibb.co/HgSFFbF/Screenshot-3.png)
```
```
6. Make sure DayZ-Sa-Tomato is loaded in DayZ Launcher before starting
```
```
![alt text](https://i.ibb.co/427c1Mr/Screenshot-1.png)
```
```
7. If starting game from Steam make sure to add "-mod=Dayz-Sa-Tomato" to start params.
```
```
![alt text](https://i.ibb.co/t3swkS3/Screenshot-7.png)
```
```
8. Join your server and login by pressing "T" and typing #login ADMINPW and pressing "enter"
```
```
![alt text](https://i.ibb.co/Sv78jk2/Screenshot-12.png)
```
```
9. Press "T" again and this time type /opme and press "enter"
10. ## DO NOT DO ANYTHING ELSE
11. Close out of the game and restart the server
12. Join the server once again and this time WITHOUT logging in hit "m" and there you go!
```
```
Please note that the profiles folder on the server does NOT have to be named "profiles" that was just used to clarify locations.
```
```
Check out this Link if you are using a 3rd party hoster. They changed their Wiki since a user asked them how to Install this mod probs to them https://trugaming.com/wiki/index.php?title=DayZ#Server_Side_Mods hopefully this helps a little bit
```
```
### Enabling Logs and Messages
=======
>>>>>>> parent of c8d7f7d... Update to Ver. 1.30




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

