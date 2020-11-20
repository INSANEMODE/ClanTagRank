# ClanTagRank
![preview](https://gitea.insanemode.org/INSANEMODE/ClanTagRank/raw/branch/master/preview/Screenshot%20%281472%29.png)

# Description:

This C++ plugin for Plutonium t6mp, t6zm, and iw5.
the function of this plugin is to allow the clan tag to be set through rcon/console using ```setclantag <client slot> <clantag name>```

this paired with a C# iw4m-admin plugin are used together to grab the iw4m-admin permission level name (Owner, Admin, etc) or a custom tag for a client, and set it as their clan tag in game.

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
