/*

        Stock:
            PlayOnlineAudio(playerid, const musicName[], Float:posX = 0.0, Float:posY = 0.0, Float:posZ = 0.0, Float:distance = 50.0, usepos = 0)
        
        Callback:
            OnPlayerAudioOnline(playerid, musicName[])

*/

#if defined _inc_musicApi
	#undef _inc_musicApi
#endif
#if defined _musicApi_included
	#endinput
#endif
#define _musicApi_included

            // Definers
#define             AUDIO_ONLINE_CALLBACK           (true);

            // Forward
forward             OnPlayerAudioOnline(playerid, musicName[]);



/*

                    .oooooo..o ooooooooooooo   .oooooo.     .oooooo.   oooo    oooo  .oooooo..o 
                    d8P'    `Y8 8'   888   `8  d8P'  `Y8b   d8P'  `Y8b  `888   .8P'  d8P'    `Y8 
                    Y88bo.           888      888      888 888           888  d8'    Y88bo.      
                    `"Y8888o.       888      888      888 888           88888[       `"Y8888o.  
                        `"Y88b      888      888      888 888           888`88b.         `"Y88b 
                    oo     .d8P      888      `88b    d88' `88b    ooo   888  `88b.  oo     .d8P 
                    8""88888P'      o888o      `Y8bood8P'   `Y8bood8P'  o888o  o888o 8""88888P'  

*/

stock PlayOnlineAudio(playerid, const musicName[], Float:posX = 0.0, Float:posY = 0.0, Float:posZ = 0.0, Float:distance = 50.0, usepos = 0) {

    new tempString[41 + 60 + 1];
    format(tempString, sizeof tempString, "http://dev.rippzy.com/php/musica.php?n=%s", musicName);
    PlayAudioStreamForPlayer(playerid, tempString, posX, posY, posZ, distance, usepos);

    #if AUDIO_ONLINE_CALLBACK
        CallRemoteFunction("OnPlayerAudioOnline", "ds", playerid, musicName);       // Callback
    #endif
    return true;
}