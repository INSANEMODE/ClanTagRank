# ClanTagRank

# Warning: 

This plugin is currently only intended to run on Plutonium t6 zombies!

# Description:

This C++ Plutonium t6 plugin and  C# iw4m-admin plugin are used together to grab the iw4m-admin role for a player name, and set it as their clan tag in game.

# Installation:

Download the latest ClanTagRank.dll from the release page, and place it in your t6 server under ```./t6r/data/plugins```, and ClanTagRankApi.dll (from https://gitea.insanemode.org/INSANEMODE/ClanTagRankApi ) in your Iw4m-admin folder under ```./Plugins```

# Limitations:

Currently, these plugins require iw4m-admin to be running locally, on the same machine as your servers, and also needs to be running on the default port 1624.

if either of these aren't followed, you will see an error in your server's console window that looks similar to this ```curl_easy_perform() failed: Couldn't connect to server```

# Additional required files/programs
https://github.com/RaidMax/IW4M-Admin/releases

https://forum.plutonium.pw/topic/2819/how-to-install-update-plutonium-t6

https://gitea.insanemode.org/INSANEMODE/ClanTagRankApi