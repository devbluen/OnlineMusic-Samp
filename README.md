# 🎷 OnlineMusic-SAMP
Play any song from YouTube on your SAMP server.<br>
This is an API created by me to play songs from YouTube on your SAMP server. However, there are still some points to be clarified about this system.

> [!Warning]
> 1. People who are abroad, outside of Brazil, might also experience some delay due to routing, regional, or country factors.
> 2. It's also possible that my hosting where my API is hosted has gone down, or some users are being blocked by Cloudflare's DDoS protection.
> 3. I will keep this include updated; if there are any problems, feel free to contact me.

# Functions
```pawn
PlayOnlineAudio(playerid, const musicName[], Float:posX = 0.0, Float:posY = 0.0, Float:posZ = 0.0, Float:distance = 50.0, usepos = 0)
```

# Callback
```pawn
OnPlayerAudioOnline(playerid, musicName[])
```

# Credits
- blueN (API)
- MTA Brasil (Suport for youtube key)
