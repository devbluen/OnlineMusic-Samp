/*

        Stocks:
            PlayOnlineAudio(playerid, musicName[], Float:posX = 0.0, Float:posY = 0.0, Float:posZ = 0.0, Float:distance = 50.0, usepos = 0)
            PlayOnlineAudio_Duration(playerid);
            PlayOnlineAudio_DurationS(playerid);
            PlayOnlineAudio_Title(playerid);
            PlayOnlineAudio_Channel(playerid);
            PlayOnlineAudio_Verified(playerid);
            PlayOnlineAudio_UploadAt(playeid);
            PlayOnlineAudio_Views(playerid);
        
        Callback:
            OnPlayerAudioOnline(playerid, musicName[])

        Example:
            PlayOnlineAudio(playerid, "The weeknd some else");
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
forward             OnPlayAudio_Request(playerid, response_code, const data[]);

enum incOnlineMusic_Enum {
    incOnlineMusic_Token,
    incOnlineMusic_Timer,
    incOnlineMusic_Views,
    incOnlineMusic_Duration[10],
    incOnlineMusic_DurationS,
    incOnlineMusic_Titulo[60],
    incOnlineMusic_Channel[60],
    incOnlineMusic_UploadAt[15],
    bool:incOnlineMusic_Verified,

        /*  Config   */
    Float:incOnlineMusic_Posicao[3],
    Float:incOnlineMusic_Distance,
    incOnlineMusic_UsePos
};

new incOnlineMusic[MAX_PLAYERS][incOnlineMusic_Enum];

public OnPlayerDisconnect(playerid, reason) {

	PlayOnlineAudio_Reset(playerid);

	if (funcidx("OM_OnPlayerDisconnect") != -1)
		return CallLocalFunction("OM_OnPlayerDisconnect", "ii", playerid, reason);
		
	return 1;
}

#if defined _ALS_OnPlayerDisconnect
	#undef OnPlayerDisconnect
#else
	#define _ALS_OnPlayerDisconnect
#endif
#define OnGameModeInit OM_OnPlayerDisconnect
forward OM_OnPlayerDisconnect();



/*

                    .oooooo..o ooooooooooooo   .oooooo.     .oooooo.   oooo    oooo  .oooooo..o 
                    d8P'    `Y8 8'   888   `8  d8P'  `Y8b   d8P'  `Y8b  `888   .8P'  d8P'    `Y8 
                    Y88bo.           888      888      888 888           888  d8'    Y88bo.      
                    `"Y8888o.       888      888      888 888           88888[       `"Y8888o.  
                        `"Y88b      888      888      888 888           888`88b.         `"Y88b 
                    oo     .d8P      888      `88b    d88' `88b    ooo   888  `88b.  oo     .d8P 
                    8""88888P'      o888o      `Y8bood8P'   `Y8bood8P'  o888o  o888o 8""88888P'  

*/

stock PlayOnlineAudio(playerid, musicName[], Float:posX = 0.0, Float:posY = 0.0, Float:posZ = 0.0, Float:distance = 50.0, usepos = 0) {

    PlayOnlineAudio_Reset(playerid);    // Prevent Bugs.

        /*          Config          */
    new tempToken = gettime();

    incOnlineMusic[playerid][incOnlineMusic_Posicao][0] = posX;
    incOnlineMusic[playerid][incOnlineMusic_Posicao][1] = posY;
    incOnlineMusic[playerid][incOnlineMusic_Posicao][2] = posZ;
    incOnlineMusic[playerid][incOnlineMusic_Distance] = distance;
    incOnlineMusic[playerid][incOnlineMusic_UsePos] = usepos;
    incOnlineMusic[playerid][incOnlineMusic_Token] = tempToken;

    SetPVarInt(playerid, "incOnlineToken", tempToken);

    PlayOnlineAudio_Fix(musicName, musicName, strlen(musicName));

    new tempString[36 + 60 + 5 + 1];
    format(tempString, sizeof tempString, "dev.rippzy.com/api/v1/Search.php?n=%s", musicName);
    HTTP(playerid, HTTP_GET, tempString, "", "OnPlayAudio_Request");
    return true;
}

stock PlayOnlineAudio_Duration(playerid)
    return (incOnlineMusic[playerid][incOnlineMusic_DurationS]);

stock PlayOnlineAudio_DurationS(playerid) {
    new tempString[10 + 1];
    strcat(tempString, incOnlineMusic[playerid][incOnlineMusic_Duration]);
    return (tempString);
}

stock PlayOnlineAudio_Title(playerid) {
    new tempString[60 + 1];
    strcat(tempString, incOnlineMusic[playerid][incOnlineMusic_Titulo]);
    return (tempString);
}

stock PlayOnlineAudio_Channel(playerid) {
    new tempString[60 + 1];
    strcat(tempString, incOnlineMusic[playerid][incOnlineMusic_Channel]);
    return (tempString);
}

stock bool:PlayOnlineAudio_Verified(playerid)
    return (incOnlineMusic[playerid][incOnlineMusic_Verified]);

stock PlayOnlineAudio_Views(playerid)
    return (incOnlineMusic[playerid][incOnlineMusic_Views]);

stock bool:PlayOnlineAudio_UploadAt(playerid) {
    new tempString[15 + 1];
    strcat(tempString, incOnlineMusic[playerid][incOnlineMusic_UploadAt]);
    return (tempString);
}

stock PlayOnline_Index(const text[], const text1[], const text2[]) {
    new 
        pos1 = strfind(text, text1, true),
        pos2 = strfind(text, text2, true);
    
    new str[256];
    strmid(str, text, pos1 + strlen(text1), pos2);
    return str;
}

stock PlayOnlineAudio_Fix(const input[], output[], tamanho) {
    new indice = 0;
    for(new i = 0; input[i] != '\0' && i < tamanho; i++)
    {
        if(input[i] != ' ')
        {
            output[indice] = input[i];
            indice++;
        }
    }
    output[indice] = '\0'; // Finalizando a string
}

stock PlayOnlineAudio_Reset(playerid) {
    
    new dsada[incOnlineMusic_Enum];
    incOnlineMusic[playerid] = dsada;
    return true;
}



/*

                    ooooooooo.   ooooo     ooo oooooooooo.  ooooo        ooooo   .oooooo.   
                    `888   `Y88. `888'     `8' `888'   `Y8b `888'        `888'  d8P'  `Y8b  
                    888   .d88'  888       8   888     888  888          888  888          
                    888ooo88P'   888       8   888oooo888'  888          888  888          
                    888          888       8   888    `88b  888          888  888          
                    888          `88.    .8'   888    .88P  888       o  888  `88b    ooo  
                    o888o           `YbodP'    o888bood8P'  o888ooooood8 o888o  `Y8bood8P'  

*/

public OnPlayAudio_Request(playerid, response_code, const data[]) {

    switch(response_code)
    {
        case 200:
        {
            if(!IsPlayerConnected(playerid)) return true;
            if(incOnlineMusic[playerid][incOnlineMusic_Token] != GetPVarInt(playerid, "incOnlineToken")) return true;   // Prevent Slow Loading Bug
            DeletePVar(playerid, "incOnlineToken");

                /*       Strings        */
            format(incOnlineMusic[playerid][incOnlineMusic_Titulo], 60, PlayOnline_Index(data, "<title>", "</title>"));
            format(incOnlineMusic[playerid][incOnlineMusic_Duration], 10, PlayOnline_Index(data, "<duration>", "</duration>"));
            format(incOnlineMusic[playerid][incOnlineMusic_Channel], 60, PlayOnline_Index(data, "<channelName>", "</channelName>"));
            format(incOnlineMusic[playerid][incOnlineMusic_UploadAt], 15, PlayOnline_Index(data, "<uploadedAt>", "</uploadedAt>"));
            
                /*       Ints           */
            sscanf(PlayOnline_Index(data, "<views>", "</views>"), "d", incOnlineMusic[playerid][incOnlineMusic_Views]);
            sscanf(PlayOnline_Index(data, "<durationseconds>", "</durationseconds>"), "d", incOnlineMusic[playerid][incOnlineMusic_DurationS]);
            sscanf(PlayOnline_Index(data, "<verified>", "</verified>"), "d", incOnlineMusic[playerid][incOnlineMusic_Verified]);

                /*      Config          */
            incOnlineMusic[playerid][incOnlineMusic_Timer] = gettime() + incOnlineMusic[playerid][incOnlineMusic_DurationS] + 6;

			new tempURL[128 + 30 + 1];
			format(tempURL, sizeof tempURL, "http://dev.rippzy.com/api/v1/Play.php?n=%s", PlayOnline_Index(data, "<id>", "</id>"));
            PlayAudioStreamForPlayer(playerid, tempURL, \ 
                incOnlineMusic[playerid][incOnlineMusic_Posicao][0], \ 
                incOnlineMusic[playerid][incOnlineMusic_Posicao][1], \ 
                incOnlineMusic[playerid][incOnlineMusic_Posicao][2], \ 
                incOnlineMusic[playerid][incOnlineMusic_Distance], \ 
                incOnlineMusic[playerid][incOnlineMusic_UsePos]);

            CallLocalFunction("OnPlayerAudioOnline", "d", playerid);
        }
        default: return printf("[Online Music:Error]: (%d) Error request informations (%d)", playerid, response_code);
    }
    return true;
}
