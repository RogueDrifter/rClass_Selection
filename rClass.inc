//0.3.8 Class selection by RogueDrifter 2018/1/17
//Topic : http://forum.sa-mp.com/showthread.php?p=3981271#post3981271
#if defined _rClassSelection_included
    #endinput
#endif
#define _rClassSelection_included

//#define ENABLE_COMMANDS //Enables commands.
//#define ENABLE_CMSGS // Enables connect messages.

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

#if !defined KEY_SCLASS
#define KEY_SCLASS KEY_SPRINT+KEY_WALK //the key used for the class selection
#endif
#if !defined KEY_RCLASS
#define KEY_RCLASS KEY_YES //key for switching between skins forward
#endif
#if !defined KEY_LCLASS
#define KEY_LCLASS KEY_NO// key for switching backwards between skins
#endif

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

enum rPlayerData
{
    PlayerChoosing,
    PlayerSkins,
    FTimer
};

new rPClass[MAX_PLAYERS][rPlayerData], SpecialSkin[MAX_SKINS_USED], rClassOb[2];

#if defined OnAddSkin
forward OnAddSkin(skinid);
#endif

#if defined OnPlayerSpecialRequestClass
forward OnPlayerSpecialRequestClass(playerid);
#endif

#if defined OnPlayerChangeSpecialClass
forward OnPlayerChangeSpecialClass(playerid, oldskin, newskin);
#endif

#if defined OnPlayerFinishSpecialClass
forward OnPlayerFinishSpecialClass(playerid, fskinid);
#endif

public OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
	if(PRESSED(KEY_SCLASS) && rPClass[playerid][PlayerChoosing] ==0)
	{
		rPClass[playerid][PlayerChoosing]=1;
		SendClientMessage(playerid, 0xFF0000A, "Returning to special class selection after next death. (press again to cancel)");
		}
	else if(PRESSED(KEY_SCLASS) && rPClass[playerid][PlayerChoosing] ==1)
	{
		rPClass[playerid][PlayerChoosing]=0;
		SendClientMessage(playerid, 0xFF0000A, "Cancelled the special class request.");
		}
	else if(PRESSED(KEY_SCLASS) && rPClass[playerid][PlayerChoosing] ==2)
	{
	SpawnPlayer(playerid);
	}
	if(PRESSED(KEY_LCLASS) && rPClass[playerid][PlayerChoosing] ==2 && rPClass[playerid][PlayerSkins] <= MAX_SKINS_USED && rPClass[playerid][PlayerSkins] >= 1)
	{
		rPClass[playerid][PlayerSkins]--;
		if(SpecialSkin[rPClass[playerid][PlayerSkins]] ==0 )
		{
			for(new i; i < MAX_SKINS_USED; i++)
			{
		    		if(SpecialSkin[i] < rPClass[playerid][PlayerSkins] && SpecialSkin[i] != 0)
					{
					    #if defined OnPlayerChangeSpecialClass
					    new oldskin = GetPlayerRSkin(playerid);
					    #endif
						SetPlayerSkin(playerid,SpecialSkin[i]);
					 	rPClass[playerid][PlayerSkins]=i;
		 				#if defined OnPlayerChangeSpecialClass
  						OnPlayerChangeSpecialClass(playerid, oldskin, GetPlayerRSkin(playerid));
						#endif
						}
					}
			}
		else
		{
		    #if defined OnPlayerChangeSpecialClass
		    new oldskin = GetPlayerRSkin(playerid);
		    #endif
			SetPlayerSkin(playerid,SpecialSkin[rPClass[playerid][PlayerSkins]]);
			#if defined OnPlayerChangeSpecialClass
  			OnPlayerChangeSpecialClass(playerid, oldskin, GetPlayerRSkin(playerid));
			#endif
			}
		}
	if(PRESSED(KEY_RCLASS) && rPClass[playerid][PlayerChoosing] ==2 && rPClass[playerid][PlayerSkins] <= MAX_SKINS_USED -1 && rPClass[playerid][PlayerSkins] >= 0)
	{
    rPClass[playerid][PlayerSkins]++;
    if(SpecialSkin[rPClass[playerid][PlayerSkins]] ==0 )
		{
			for(new i; i < MAX_SKINS_USED; i++)
			{
  				if(SpecialSkin[i] > rPClass[playerid][PlayerSkins] && SpecialSkin[i] != 0)
				{
				    #if defined OnPlayerChangeSpecialClass
				    new oldskin = GetPlayerRSkin(playerid);
				    #endif
			 		SetPlayerSkin(playerid,SpecialSkin[i]);
				  	rPClass[playerid][PlayerSkins]=i;
					#if defined OnPlayerChangeSpecialClass
				  	OnPlayerChangeSpecialClass(playerid, oldskin, GetPlayerRSkin(playerid));
					#endif
			 	    }
		    	}
			}
    	else
	 	{
	 	    #if defined OnPlayerChangeSpecialClass
	 	    new oldskin = GetPlayerRSkin(playerid);
	 	    #endif
	 		SetPlayerSkin(playerid,SpecialSkin[rPClass[playerid][PlayerSkins]]);
	 		#if defined OnPlayerChangeSpecialClass
	 		OnPlayerChangeSpecialClass(playerid, oldskin, GetPlayerRSkin(playerid));
	 		#endif
	 		}
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
	if(rPClass[playerid][PlayerChoosing]==2 && GetPlayerInterior(playerid) ==4) TogglePlayerControllable(playerid, 0);
	else if(GetPlayerInterior(playerid) ==0 && rPClass[playerid][PlayerChoosing] ==2) rPClass[playerid][PlayerChoosing]=0;
	return 1;
}

public OnPlayerDisconnect(playerid, reason)
{
	KillTimer(rPClass[playerid][FTimer]);
	#if defined OnPlayerDisConnectrClass
    return OnPlayerDisConnectrClass(playerid, reason);
	#else
	return 1;
	#endif
}

public OnPlayerConnect(playerid)
{
	rPClass[playerid][FTimer] = SetTimerEx("FreezeClass",1000,true,"d",playerid);
	rPClass[playerid][PlayerChoosing]= 0;
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
	if(rPClass[playerid][PlayerChoosing] ==1)
	{
	    #if defined OnPlayerSpecialRequestClass
	    OnPlayerSpecialRequestClass(playerid);
	    #endif
		rPClass[playerid][PlayerChoosing]=2;
		rPClass[playerid][PlayerSkins]=0;
		TogglePlayerControllable(playerid,0);
		SetPlayerPos(playerid, 305.8891,305.6985,999.1484);
		SetPlayerInterior(playerid, 4);
		SetPlayerFacingAngle(playerid, 85.0351);
		SetPlayerCameraPos(playerid, 302.58,305.86,999.15);
		SetPlayerCameraLookAt(playerid, 305.8891,305.6985,999.1484);
		#if defined ENABLE_CMSGS
		SendClientMessage(playerid,-1,".: You're now at the special class selection :.");
		SendClientMessage(playerid,-1,".: {FF0000}Press {00FF00}Y {FF0000}OR {00FF00}N {CCCCCC}to switch between skins :.");
		SendClientMessage(playerid,-1,".: {FF0000}Hold {00FF00}SPACEBAR {CCCCCC}and {FF0000}Press {00FF00}N {CCCCCC}to exit and save:.");
        #if defined ENABLE_COMMANDS
		SendClientMessage(playerid,-1,".: or type {00FF00}/saverclass {CCCCCC}:.");
		#endif
		#endif
	    }
	else if(rPClass[playerid][PlayerChoosing]==2)
	{
	    TogglePlayerControllable(playerid,1);
	    SetCameraBehindPlayer(playerid);
	    SetPlayerInterior(playerid, 0);
	    rPClass[playerid][PlayerChoosing]=0;
	    #if defined OnPlayerFinishSpecialClass
	    OnPlayerFinishSpecialClass(playerid, GetPlayerRSkin(playerid));
	    #endif
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
	if(25000 > skinid > 30000) return 0;
 	for(new i; i < MAX_SKINS_USED; i++)
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

#if defined FILTERSCRIPT

public OnFilterScriptInit()
{
	print("     [[--|| rClass V2.0 ||--]]       ");
    print("     [[--|| Specal custom skin selector by RogueDrifter V 2.0 ||--]]     ");
    print("     [[--|| Successfully Loaded! ||--]]      ");
	rClassOb[0] = CreateObject(16501, 306.32965, 305.77649, 999.73804,   0.00000, 0.00000, 0.00000,300.0);
	rClassOb[1] = CreateObject(16501, 305.11072, 305.77588, 998.07892,   0.00000, 90.00000, 0.00000,300.0);
	SetObjectMaterialText(rClassOb[0], "0.3.8 Skins", 0,OBJECT_MATERIAL_SIZE_256x64,"Segoe Print", 42, 1, 0xFFFF0000, 0xFF000000, OBJECT_MATERIAL_TEXT_ALIGN_LEFT);
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
	print("     [[--|| rClass V2.0 ||--]]       ");
    print("     [[--|| Specal custom skin selector by RogueDrifter V 2.0 ||--]]     ");
    print("     [[--|| Successfully Loaded! ||--]]      ");
	rClassOb[0] = CreateObject(16501, 306.32965, 305.77649, 999.73804,   0.00000, 0.00000, 0.00000,300.0);
	rClassOb[1] = CreateObject(16501, 305.11072, 305.77588, 998.07892,   0.00000, 90.00000, 0.00000,300.0);
	SetObjectMaterialText(rClassOb[0], "0.3.8 Skins", 0,OBJECT_MATERIAL_SIZE_256x64,"Segoe Print", 42, 1, 0xFFFF0000, 0xFF000000, OBJECT_MATERIAL_TEXT_ALIGN_LEFT);
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

CMD:checkrclass(playerid,params[])
{
 	new sString[124], ClassesString[124];
	if(!IsPlayerAdmin(playerid))
	{
		for(new i; i < MAX_SKINS_USED; i++)
		{
		    if(SpecialSkin[i] != 0 && strfind(ClassesString, SpecialSkin[i], true) == -1)
		    {
	    		format(ClassesString, sizeof(ClassesString), "%s, %d",ClassesString, SpecialSkin[i]);
	    		}
	        }
 	format(sString, sizeof(sString), "|| The added skins are %s ||",ClassesString);
	SendClientMessage(playerid, -1, sString);
	}
	return 1;
}

CMD:addrclass(playerid,params[])
{
	if(!IsPlayerAdmin(playerid))
	{
		new desiredskin;
		if(sscanf(params,"i", desiredskin) || !IsNumeric(params) ) return SendClientMessage(playerid, 0xFFFFFFF,"Syntax error, Correct usage: /addrclass [skinid]");
        if(25000 > desiredskin > 30000) return SendClientMessage(playerid,-1, ".: Please don't go below 25000 or higher than 30000 :.");
		for(new i; i < MAX_SKINS_USED; i++)
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
	if(!IsPlayerAdmin(playerid))
	{
    	new desiredskin;
		if(sscanf(params,"i", desiredskin) || !IsNumeric(params) ) return SendClientMessage(playerid, 0xFFFFFFF,"Syntax error, Correct usage: /addrclass [skinid]");
		for(new i; i < MAX_SKINS_USED; i++)
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
	if(rPClass[playerid][PlayerChoosing] ==0)
	{
		rPClass[playerid][PlayerChoosing]=1;
		SendClientMessage(playerid, 0xFF0000A, "Returning to special class selection after next death. (press again to cancel)");
		}
	else if(rPClass[playerid][PlayerChoosing] ==1)
	{
		rPClass[playerid][PlayerChoosing]=0;
		SendClientMessage(playerid, 0xFF0000A, "Cancelled the special class request.");
		}
	return 1;
}

CMD:saverclass(playerid,params[])
{
	if(rPClass[playerid][PlayerChoosing] ==2) SpawnPlayer(playerid);
	return 1;
}

#else

public OnPlayerCommandText(playerid, cmdtext[])
{
	if (strcmp("/addrclass", cmdtext, true, 10) == 0)
	{
		if(!IsPlayerAdmin(playerid))
		{
			new desiredskin;
			if(sscanf(params,"ii", desiredskin) || !IsNumeric(desiredskin) ) return SendClientMessage(playerid, 0xFFFFFFF,"Syntax error, Correct usage: /addrclass [skinid]");
 			for(new i; i < MAX_SKINS_USED; i++)
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
		if(!IsPlayerAdmin(playerid))
		{
    		new desiredskin;
			if(sscanf(params,"i", desiredskin) || !IsNumeric(desiredskin) ) return SendClientMessage(playerid, 0xFFFFFFF,"Syntax error, Correct usage: /addrclass [skinid]");
			for(new i; i < MAX_SKINS_USED; i++)
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
		if(rPClass[playerid][PlayerChoosing] ==2) SpawnPlayer(playerid);
		return 1;
		}
	if (strcmp("/rclass", cmdtext, true, 10) == 0)
	{
		if(rPClass[playerid][PlayerChoosing] ==0)
		{
			rPClass[playerid][PlayerChoosing]=1;
			SendClientMessage(playerid, 0xFF0000A, "Returning to special class selection after next death. (press again to cancel)");
			}
		else if(rPClass[playerid][PlayerChoosing] ==1)
		{
			rPClass[playerid][PlayerChoosing]=0;
			SendClientMessage(playerid, 0xFF0000A, "Cancelled the special class request.");
			}
		return 1;
		}
    if (strcmp("/checkrclass", cmdtext, true, 10) == 0)
	{
		new sString[124], ClassesString[124];
		if(!IsPlayerAdmin(playerid))
		{
			for(new i; i < MAX_SKINS_USED; i++)
			{
		    	if(SpecialSkin[i] != 0 && strfind(ClassesString, SpecialSkin[i], true) == -1)
		    	{
	    			format(ClassesString, sizeof(ClassesString), "%s, %d",ClassesString, SpecialSkin[i]);
	    			}
	        	}
 			format(sString, sizeof(sString), "|| The added skins are %s ||",ClassesString);
			SendClientMessage(playerid, -1, sString);
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

stock GetPlayerRSkin(playerid)
{
	if(GetPlayerCustomSkin(playerid) ==0) return GetPlayerSkin(playerid);
	else if(GetPlayerCustomSkin(playerid) != 0) return GetPlayerCustomSkin(playerid);
	return 1;
}

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
