# DayZ-SA-Tomato

Dayz Standalone GUI Based Admin Tool



## Changelog

See CHANGELOG.md

## News

## 01.14.2019 00:26


### Added 

- Teleport Locations added right from in-game gui.
- Spawn a changable size horde of zombies by a simple click on the map or on a defined location.
- Delete Object on cursor
- Player files sorted by Steam64ID for easy adding of admin to the server.
- Teleport on Map click
- Horde on Map Click 
- Customizable Kill feed (standard is disabled, change it in Config.txt File in your profiles folder)
- Customizable Welcome message
- Kill log file 
- Spectate Player


 ### next up
 
- TBA


#### If Someone has this mod working on a 3rd Party host (GSP) PLEASE Cantact me or join https://discord.gg/Svgz48m to let us know to help others with the same service get their mod working as well

##  Notes

You can do what you like with this tool as the license states. But if you add any features to it, i would appreciate if you would share your code so that everyone can benefit from it.


You could cantact me by email at DayZ-SA-Tomato@Primary-Network.de
Or @Discord https://discord.gg/qqjwVXV

### Installation

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
6. Move the DayZ-Sa-Tomato profile folder from the mod folder's Tomato_Profiles folder to server profiles folder. 
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

-First thing you do is to go in to your server and open DayZServer/URPROFILES/Tomato_Profiles/Config/Config.txt file. Find the features you'd like to add and change the number 0 at the end to a 1 to enable it.

-Next if you want to customize the messages you can but REMEMBER you can not change certain parts or you wont get all your information from the message. Make sure you DO NOT edit anyting BEFORE the = symbol, the = symbol, or anything in the {} brackets.
```
```
![alt text](https://i.ibb.co/4KWcsCJ/Screenshot-2.png)
```
```

## Troubleshooting

-If you are still not able to access the admin tool with "M" there IS another way to activate the menu on your server. First, go to your DayZ server root and find your "profiles" (or whatever you named your profiles folder) and open it. Inside that folder will be a DayZ-Sa-Tomato folder. Inside that there is a "config" folder and inside that one is a "players" folder. There should be a file in there YOURSTEAM64ID.player (i.e. 76561198161388867.Player). right click and edit that to change Admin = 0 to Admin = 1 save and close that file. Back out to the "config" folder and edit config.txt to change the first option Setup = 0 to setup = 1. Restart the server and join your server and "M" should now work for you.
```
```
![alt text](https://i.ibb.co/NKWzG6q/Screenshot-1.png)
```
```
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
* **Commands Tab** - Delete at cursor




![alt text](https://i.ibb.co/f2f231q/COMMANDS.jpg)

------------

* **Spawn Tab** - Item/AI/Building Spawning




![alt text](https://i.ibb.co/rGY1kWS/SPAWN.jpg)

------------

* **Player Tab** - Player List
* **Player Tab** - Tp Players and tp to Players
* **Player Tab** - Strip Player
* **Player Tab** - Position of Player
* **Player Tab** - Disable Stamina for specific Player 
* **Player Tab** - Heal Player
* **Player Tab** - Kill Player
* **Player Tab** - Spectate Player




![alt text](https://i.ibb.co/HNtddT5/PLAYER.jpg)

------------

* **Teleport Tab** - Teleport location list
* **Teleport Tab** - Add/remove teleport locations in list
* **Teleport Tab** - Spawn zombie hordes on locations




![alt text](https://i.ibb.co/XxWSmCb/TELEPORT.jpg)

------------

* **Map Tab** - Shows Location of all Players on the Map
* **Map Tab** - Spawn Zombie Horde on map
* **Map Tab** - Teleport by map




![alt text](https://i.ibb.co/h73WcvQ/MAP.jpg)

------------

* **About Tab** - All the information about support for DayZ-Sa-Tomato




![alt text](https://i.ibb.co/sVfqfTx/20190119155652-1.jpg)


------------


### Known Issues
* **Spwan Tab** - Item Preview (right side not working)

## License

This project is licensed under the GNU v3 License - see the [LICENSE.md](LICENSE.md) file for details

## Acknowledgments

* Everyone on the Forums/Discord who answered question (not only me but everyone)
* DayZCommunityOfflineMode for Snippets

