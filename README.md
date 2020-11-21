# ClanTagRank
![preview](https://gitea.insanemode.org/INSANEMODE/ClanTagRank/raw/branch/master/preview/Screenshot%20%281472%29.png)

# Description:

This C++ plugin for Plutonium t6mp, t6zm, and iw5.
the function of this plugin is to allow the clan tag to be set through rcon/console. 

This can be paired with [SetClanTagCommands](https://github.com/INSANEMODE/ClanTagRankCommnads) to grab the iw4m-admin permission level name (Owner, Admin, etc) or a custom tag for a client, and set it as their clan tag in game.

# Usage
```setclantag <client slot> <clantag name>``` : set a single client's clan tag
```setclantags <clantag name>``` : set all clients' clantag in the lobby
```setclantagraw <client slot> <clantag name>``` : same as setclantag, but allow raw strings to be set as clantags (allows things like color codes)
```setclantagsraw <clantag name>``` : same as setclantags, but allow raw strings to be set as clantags
# Installation:

- Download the latest ClanTagRank.dll from the release page, and place it in your t6 server under ```./t6r/data/plugins```.

- if you want to pair it with iw4m-admin, download ClanTagRankCommands.dll (from https://github.com/INSANEMODE/ClanTagRankCommands ) in your Iw4m-admin folder under ```./Plugins```

- everything is now handled through rcon, so there is no longer a need to set your iw4m-admin url in the config file. it can be safely deleted.

# Additional Required Files/Programs
https://github.com/RaidMax/IW4M-Admin/releases

https://forum.plutonium.pw/

https://github.com/INSANEMODE/ClanTagRankCommands

# Special Thanks to:
  - https://github.com/fedddddd
  - for improving upon my idea, and adding support for addtional games.
