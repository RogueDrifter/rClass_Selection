//0.3.8 Class selection by RogueDrifter 2018/1/17
//Topic: http://forum.sa-mp.com/showthread.php?p=3981271#post3981271
#if defined _rClassSelection_included
    #endinput
#endif
#define _rClassSelection_included


//#define ENABLE_COMMANDS //Enables commands.
//#define ENABLE_CMSGS // Enables connect messages.
//#define RCLASS_TEX "MESSAGE"// Enables the edited message for the class selection place.

#include <a_samp>

#if defined ENABLE_COMMANDS
#if defined CMD
#else
#include <zcmd>
#endif
#endif

#if defined PRESSED
#else
#define PRESSED(%0) \
    (((newkeys & (%0)) == (%0)) && ((oldkeys & (%0)) != (%0)))
#endif

#if defined MAX_SKINS_USED
#else
#define MAX_SKINS_USED 50 // Maximum amount of special skins change to your maximum amount you will use.
#endif

#define KEY_SCLASS KEY_SPRINT+KEY_WALK //the key used for the class selection
#define KEY_RCLASS KEY_YES //key for switching between skins forward
#define KEY_LCLASS KEY_NO// key for switching backwards between skins

#if defined OnPlayerConnectrClass
forward OnPlayerConnectrClass(playerid);
#endif

#if defined OnPlayerDisconnectrClass
forward OnPlayerDisconnectrClass(playerid, reason);
#endif

#if defined OnPlayerKeyStateChangerClass
forward OnPlayerKeyStateChangerClass(playerid,newkeys,oldkeys);
#endif

#if defined OnGameModeInitrClass
forward OnGameModeInitrClass();
#endif

#if defined OnGameModeExitrClass
forward OnGameModeExitrClass();
#endif

#if defined OnFilterScriptInitrClass
forward OnFilterScriptInitrClass();
#endif

#if defined OnFilterScriptExitrClass
forward OnFilterScriptExitrClass();
#endif

#if defined OnPlayerSpawnrClass
forward OnPlayerSpawnrClass();
#endif

new PlayerChoosing[MAX_PLAYERS], PlayerSkins[MAX_PLAYERS], SpecialSkin[MAX_SKINS_USED],rClassOb[2], FTimer[MAX_PLAYERS];

public OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
	if(PRESSED(KEY_SCLASS) && PlayerChoosing[playerid] ==0)
	{
		PlayerChoosing[playerid]=1;
		SendClientMessage(playerid, 0xFF0000A, "Returning to special class selection after next death. (press again to cancel)");
		}
	else if(PRESSED(KEY_SCLASS) && PlayerChoosing[playerid] ==1)
	{
		PlayerChoosing[playerid]=0;
		SendClientMessage(playerid, 0xFF0000A, "Cancelled the special class request.");
		}
	else if(PRESSED(KEY_SCLASS) && PlayerChoosing[playerid] ==2)
	{
	SpawnPlayer(playerid);
	}
	if(PRESSED(KEY_LCLASS) && PlayerChoosing[playerid] ==2 && PlayerSkins[playerid] <= MAX_SKINS_USED && PlayerSkins[playerid] >= 1)
	{
		PlayerSkins[playerid]--;
		if(SpecialSkin[PlayerSkins[playerid]] ==0 )
		{
			for(new i = 0; i < MAX_SKINS_USED; i++)
			{
		    		if(SpecialSkin[i] < PlayerSkins[playerid] && SpecialSkin[i] != 0) SetPlayerSkin(playerid,SpecialSkin[i]), PlayerSkins[playerid]=i;
			    	}
			}
		else SetPlayerSkin(playerid,SpecialSkin[PlayerSkins[playerid]]);
		}
	if(PRESSED(KEY_RCLASS) && PlayerChoosing[playerid] ==2 && PlayerSkins[playerid] <= MAX_SKINS_USED -1 && PlayerSkins[playerid] >= 0)
	{
    PlayerSkins[playerid]++;
    if(SpecialSkin[PlayerSkins[playerid]] ==0 )
		{
			for(new i = 0; i < MAX_SKINS_USED; i++)
			{
  				if(SpecialSkin[i] > PlayerSkins[playerid] && SpecialSkin[i] != 0) SetPlayerSkin(playerid,SpecialSkin[i]), PlayerSkins[playerid]=i;
		    	}
			}
    	else SetPlayerSkin(playerid,SpecialSkin[PlayerSkins[playerid]]);
		}
    #if defined OnPlayerKeyStateChangerClass
    return OnPlayerKeyStateChangerClass(playerid, newkeys, oldkeys);
	#else
	return 1;
	#endif
}

forward FreezeClass(playerid);
public FreezeClass(playerid)
{
	if(PlayerChoosing[playerid]==2 && GetPlayerInterior(playerid) ==4) TogglePlayerControllable(playerid, 0);
	else if(GetPlayerInterior(playerid) ==0 && PlayerChoosing[playerid] ==2) PlayerChoosing[playerid]=0;
	return 1;
}

public OnPlayerDisconnect(playerid, reason)
{
	KillTimer(FTimer[playerid]);
	#if defined OnPlayerDisConnectrClass
    return OnPlayerDisConnectrClass(playerid, reason);
	#else
	return 1;
	#endif
}
public OnPlayerConnect(playerid)
{
	FTimer[playerid] = SetTimerEx("FreezeClass",1000,true,"d",playerid);
	PlayerChoosing[playerid]= 0;
	#if defined ENABLE_CMSGS
	SendClientMessage(playerid,-1, "{CCCCCC}.: {0000FF}This server has its own custom skin class selection!{CCCCCC}:.");
	SendClientMessage(playerid,-1, ".: {FF0000}Hold {00FF00}SPACEBAR {CCCCCC}and {FF0000}Press {00FF00}N {CCCCCC}to enter {CCCCCC}:.");
	#if defined ENABLE_COMMANDS
	SendClientMessage(playerid,-1,".: or type {00FF00}/rclass {CCCCCC}:.");
	#endif
	#endif
	#if defined OnPlayerConnectrClass
    return OnPlayerConnectrClass(playerid);
	#else
	return 1;
	#endif
}

public OnPlayerSpawn(playerid)
{
	if(PlayerChoosing[playerid] ==1)
	{
		PlayerChoosing[playerid]=2;
		PlayerSkins[playerid]=0;
		TogglePlayerControllable(playerid,0);
		SetPlayerPos(playerid, 305.8891,305.6985,999.1484);
		SetPlayerInterior(playerid, 4);
		SetPlayerFacingAngle(playerid, 85.0351);
		SetPlayerCameraPos(playerid, 302.58,305.86,999.15);
		SetPlayerCameraLookAt(playerid, 305.8891,305.6985,999.1484);
		SendClientMessage(playerid,-1,".: You're now at the special class selection :.");
		SendClientMessage(playerid,-1,".: {FF0000}Press {00FF00}Y {FF0000}OR {00FF00}N {CCCCCC}to switch between skins :.");
		SendClientMessage(playerid,-1,".: {FF0000}Hold {00FF00}SPACEBAR {CCCCCC}and {FF0000}Press {00FF00}N {CCCCCC}to exit and save:.");
        #if defined ENABLE_COMMANDS
		SendClientMessage(playerid,-1,".: or type {00FF00}/saverclass {CCCCCC}:.");
		#endif
	    }
	else if(PlayerChoosing[playerid]==2)
	{
	    TogglePlayerControllable(playerid,1);
	    SetCameraBehindPlayer(playerid);
	    SetPlayerInterior(playerid, 0);
	    PlayerChoosing[playerid]=0;
	    }
	#if defined OnPlayerSpawnrClass
    return OnPlayerSpawnrClass(playerid);
	#else
	return 1;
	#endif
}

forward AddSkin(skinid);
public AddSkin(skinid)
{
	for(new i = 0; i < MAX_SKINS_USED; i++)
	{
		if(SpecialSkin[i] ==0 && SpecialSkin[i] != skinid)
		{
 			SpecialSkin[i]= skinid;
 			#if defined OnAddSkin
 			OnAddSkin(skinid);
 			#endif
		 	break;
 			}
	    }
	return 1;
}

#if defined OnAddSkin
forward OnAddSkin(skinid);
#endif

#if defined FILTERSCRIPT

public OnFilterScriptInit()
{
	print("		[[--|| rClass V1.0 ||--]]		");
	print("		[[--|| Specal custom skin selector by RogueDrifter V 1.0 ||--]]		");
	print("		[[--|| Successfully Loaded! ||--]]		");
	rClassOb[0] = CreateObject(16501, 306.32965, 305.77649, 999.73804,   0.00000, 0.00000, 0.00000,300.0);
	SetObjectMaterialText(rClassOb[0], "0.3.8 Skins", 0,OBJECT_MATERIAL_SIZE_256x64,"Segoe Print", 42, 1, 0xFFFF0000, 0xFF000000, OBJECT_MATERIAL_TEXT_ALIGN_LEFT);
 	rClassOb[1] = CreateObject(16501, 305.11072, 305.77588, 998.07892,   0.00000, 90.00000, 0.00000,300.0);
	SetObjectMaterialText(rClassOb[1], "0.3.8 Skins", 0,OBJECT_MATERIAL_SIZE_256x64,"Segoe Print", 42, 1, 0xFFFF0000, 0xFF000000, OBJECT_MATERIAL_TEXT_ALIGN_CENTER);
	#if defined OnFilterScriptInitrClass
    return OnFilterScriptInitrClass();
	#else
	return 1;
	#endif
}

public OnFilterScriptExit()
{
	DestroyObject(rClassOb[0]);
	DestroyObject(rClassOb[1]);
	rClassOb[0]= INVALID_OBJECT_ID;
	rClassOb[1]= INVALID_OBJECT_ID;
	#if defined OnFilterScriptExitrClass
    return OnFilterScriptExitrClass();
	#else
	return 1;
	#endif
}

#else

public OnGameModeInit()
{
	print("		[[--|| rClass V1.0 ||--]]		");
	print("		[[--|| Specal custom skin selector by RogueDrifter V 1.0 ||--]]		");
	print("		[[--|| Successfully Loaded! ||--]]		");
	rClassOb[0] = CreateObject(16501, 306.32965, 305.77649, 999.73804,   0.00000, 0.00000, 0.00000,300.0);
	SetObjectMaterialText(rClassOb[0], "0.3.8 Skins", 0,OBJECT_MATERIAL_SIZE_256x64,"Segoe Print", 42, 1, 0xFFFF0000, 0xFF000000, OBJECT_MATERIAL_TEXT_ALIGN_LEFT);
 	rClassOb[1] = CreateObject(16501, 305.11072, 305.77588, 998.07892,   0.00000, 90.00000, 0.00000,300.0);
	SetObjectMaterialText(rClassOb[1], "0.3.8 Skins", 0,OBJECT_MATERIAL_SIZE_256x64,"Segoe Print", 42, 1, 0xFFFF0000, 0xFF000000, OBJECT_MATERIAL_TEXT_ALIGN_CENTER);
 	#if defined OnGameModeInitrClass
    return OnGameModeInitrClass();
	#else
	return 1;
	#endif
}

public OnGameModeExit()
{
	DestroyObject(rClassOb[0]);
	DestroyObject(rClassOb[1]);
	rClassOb[0]= INVALID_OBJECT_ID;
	rClassOb[1]= INVALID_OBJECT_ID;
	#if defined OnGameModeExitrClass
    return OnGameModeExitrClass();
	#else
	return 1;
	#endif
}

#endif

#if defined ENABLE_COMMANDS

#if defined sscanf

#else

stock sscanf(string[], format[], {Float,_}:...)// Obviously picked from sscanf include.
{
	new
		formatPos = 0,
		stringPos = 0,
		paramPos = 2,
		paramCount = numargs();

	while (paramPos < paramCount && string[stringPos])
	{
		switch (format[formatPos++])
		{
			case '\0':
			{
				return 0;
			}
			case 'i', 'd':
			{
				new
					neg = 1,
					num = 0,
					ch = string[stringPos];
				if (ch == '-')
				{
					neg = -1;
					ch = string[++stringPos];
				}
				do
				{
					stringPos++;
					if (ch >= '0' && ch <= '9')
					{
						num = (num * 10) + (ch - '0');
					}
					else
					{
						return 1;
					}
				}
				while ((ch = string[stringPos]) && ch != ' ');
				setarg(paramPos, 0, num * neg);
			}
			case 'h', 'x':
			{
				new
					ch,
					num = 0;
				while ((ch = string[stringPos++]))
				{
					switch (ch)
					{
						case 'x', 'X':
						{
							num = 0;
							continue;
						}
						case '0' .. '9':
						{
							num = (num << 4) | (ch - '0');
						}
						case 'a' .. 'f':
						{
							num = (num << 4) | (ch - ('a' - 10));
						}
						case 'A' .. 'F':
						{
							num = (num << 4) | (ch - ('A' - 10));
						}
						case ' ':
						{
							break;
						}
						default:
						{
							return 1;
						}
					}
				}
				setarg(paramPos, 0, num);
			}
			case 'c':
			{
				setarg(paramPos, 0, string[stringPos++]);
			}
			case 'f':
			{
                new tmp[25];
                strmid(tmp, string, stringPos, stringPos+sizeof(tmp)-2);
				setarg(paramPos, 0, _:floatstr(tmp));
			}
			case 's', 'z':
			{
				new
					i = 0,
					ch;
				if (format[formatPos])
				{
					while ((ch = string[stringPos++]) && ch != ' ')
					{
						setarg(paramPos, i++, ch);
					}
					if (!i) return 1;
				}
				else
				{
					while ((ch = string[stringPos++]))
					{
						setarg(paramPos, i++, ch);
					}
				}
				stringPos--;
				setarg(paramPos, i, '\0');
			}
			default:
			{
				continue;
			}
		}
		while (string[stringPos] && string[stringPos] != ' ')
		{
			stringPos++;
		}
		while (string[stringPos] == ' ')
		{
			stringPos++;
		}
		paramPos++;
	}
	while (format[formatPos] == 'z') formatPos++;
	return format[formatPos];
}

#endif

#if defined IsNumeric
#else

stock IsNumeric(const string[]) // Picked from utils.inc
{
	for (new i = 0, j = strlen(string); i < j; i++)
	{
		if (string[i] > '9' || string[i] < '0') return 0;
	}
	return 1;
}

#endif

#if defined CMD

CMD:addrclass(playerid,params[])
{
	if(IsPlayerAdmin(playerid))
	{
		new desiredskin;
		if(sscanf(params,"i", desiredskin) || !IsNumeric(params) ) return SendClientMessage(playerid, 0xFFFFFFF,"Syntax error, Correct usage: /addrskin [skinid]");
 		for(new i = 0; i < MAX_SKINS_USED; i++)
		{
			if(SpecialSkin[i] == desiredskin) return SendClientMessage(playerid,-1, ".: Skin already added! :.");
 			}
		AddSkin(desiredskin);
		SendClientMessage(playerid,-1,".: Skin added! :.");
    	}
	return 1;
}

CMD:removerclass(playerid,params[])
{
	if(IsPlayerAdmin(playerid))
	{
    	new desiredskin;
		if(sscanf(params,"i", desiredskin) || !IsNumeric(params) ) return SendClientMessage(playerid, 0xFFFFFFF,"Syntax error, Correct usage: /addrskin [skinid]");
		for(new i = 0; i < MAX_SKINS_USED; i++)
		{
			if(SpecialSkin[i] == desiredskin)
			{
 				SpecialSkin[i] =0;
 				}
			}
		SendClientMessage(playerid,-1,".: Skin removed! :.");
		}
	return 1;
}

CMD:rclass(playerid, params[])
{
	if(PlayerChoosing[playerid] ==0)
	{
		PlayerChoosing[playerid]=1;
		SendClientMessage(playerid, 0xFF0000A, "Returning to special class selection after next death. (press again to cancel)");
		}
	else if(PlayerChoosing[playerid] ==1)
	{
		PlayerChoosing[playerid]=0;
		SendClientMessage(playerid, 0xFF0000A, "Cancelled the special class request.");
		}
	return 1;
}

CMD:saverclass(playerid,params[])
{
	if(PlayerChoosing[playerid] ==2) SpawnPlayer(playerid);
	return 1;
}

#else

public OnPlayerCommandText(playerid, cmdtext[])
{
	if (strcmp("/addrclass", cmdtext, true, 10) == 0)
	{
		if(IsPlayerAdmin(playerid))
		{
			new desiredskin;
			if(sscanf(params,"ii", desiredskin) || !IsNumeric(desiredskin) ) return SendClientMessage(playerid, 0xFFFFFFF,"Syntax error, Correct usage: /addrskin [skinid]");
 			for(new i = 0; i < MAX_SKINS_USED; i++)
			{
				if(SpecialSkin[i] == desiredskin) return SendClientMessage(playerid,-1, ".: Skin already added! :.");
 				}
			AddSkin(desiredskin);
			SendClientMessage(playerid,-1,".: Skin added! :.");
    		}
		return 1;
		}
	if (strcmp("/removerclass", cmdtext, true, 10) == 0)
	{
		if(IsPlayerAdmin(playerid))
		{
    		new desiredskin;
			if(sscanf(params,"i", desiredskin) || !IsNumeric(desiredskin) ) return SendClientMessage(playerid, 0xFFFFFFF,"Syntax error, Correct usage: /addrskin [skinid]");
			for(new i = 0; i < MAX_SKINS_USED; i++)
			{
				if(SpecialSkin[i] == desiredskin)
				{
 					SpecialSkin[i] =0;
 					}
				}
			SendClientMessage(playerid,-1,".: Skin removed! :.");
			}
		return 1;
		}
 	if (strcmp("/saverclass", cmdtext, true, 10) == 0)
	{
		if(PlayerChoosing[playerid] ==2) SpawnPlayer(playerid);
		return 1;
		}
	if (strcmp("/rclass", cmdtext, true, 10) == 0)
	{
		if(PlayerChoosing[playerid] ==0)
		{
			PlayerChoosing[playerid]=1;
			SendClientMessage(playerid, 0xFF0000A, "Returning to special class selection after next death. (press again to cancel)");
			}
		else if(PlayerChoosing[playerid] ==1)
		{
			PlayerChoosing[playerid]=0;
			SendClientMessage(playerid, 0xFF0000A, "Cancelled the special class request.");
			}
		return 1;
		}
	#if defined OnPlayerCommandTextrClass
    return OnPlayerCommandTextrClass(playerid, cmdtext[]);
	#else
	return 0;
	#endif
}

#endif
#endif

#if defined _ALS_OnPlayerKeyStateChange
  #undef OnPlayerStateChange
#else
	#define _ALS_OnPlayerKeyStateChange
#endif

#define OnPlayerKeyStateChange OnPlayerKeyStateChangerClass


#if defined _ALS_OnFilterScriptInit
  #undef OnFilterScriptInit
#else
	#define _ALS_OnFilterScriptInit
#endif

#define OnFilterScriptInit OnFilterScriptInitrClass

#if defined _ALS_OnFilterScriptExit
  #undef OnFilterScriptExit
#else
	#define _ALS_OnFilterScriptExit
#endif

#define OnFilterScriptExit OnFilterScriptExitrClass

#if defined _ALS_OnGameModeInit
  #undef OnGameModeInit
#else
	#define _ALS_OnGameModeInit
#endif

#define OnGameModeInit OnGameModeInitrClass

#if defined _ALS_OnGameModeExit
  #undef OnGameModeExit
#else
	#define _ALS_OnGameModeExit
#endif

#define OnGameModeExit OnGameModeExitrClass

#if defined _ALS_OnPlayerSpawn
  #undef OnPlayerSpawn
#else
	#define _ALS_OnPlayerSpawn
#endif

#define OnPlayerSpawn OnPlayerSpawnrClass

#if defined _ALS_OnPlayerConnect
  #undef OnPlayerConnect
#else
	#define _ALS_OnPlayerConnect
#endif

#define OnPlayerConnect OnPlayerConnectrClass

#if defined _ALS_OnPlayerDisconnect
  #undef OnPlayerDisconnect
#else
	#define _ALS_OnPlayerDisconnect
#endif

#define OnPlayerDisconnect OnPlayerDisconnectrClass
