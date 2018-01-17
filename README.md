# 0.3.8-Include-Special-skin-class-selection.
This is an extra class selection for custom 0.3.8 skins.
Visit this topic for info: http://forum.sa-mp.com/showthread.php?p=3981271#post3981271
Explained here:


Server side class selection for 0.3.8 custom skins!

Last updated 2018/1/17

Comment:
Well i know 0.3.8 was cancelled but meh i'm still releasing this because some servers still use 0.3.8 and it will be a while til it's completely killed til the -DL feature is added on the official samp release.
=====
Why you need this:
AddPlayerClass will NOT add custom skins and will return 0 (Cj skin) on view, it will give the custom skin but will show you Cj's skin which is not something you need to deal with, this is a server-side class selection system that's very friendly.
=====
Usage & Features :
1- put #MAX_SKINS_USED [NUMBER] BEFORE the include in your script with the number of custom skins you'd want to use to avoid overloaded data you can add any number but its best to choose the number you want, its 50 by default, for ex: if i will use 50 i will do: #define MAX_USED_SKINS 50
2-You can use this simply by including it and put AddSkin(custom skin id); at OnFilterScriptInit or OnGameModeInit to add the custom skin only once for ex : 
PHP Code:
public OnGameModeInit() 
{ 
    AddSkin(25001);//add skin id 25001 to the class selection. 
    return 1; 
}  
For extended use:
1- you can control the messages player's get when they connect i made by putting:#define ENABLE_CMSGS on top of your script BEFORE the include. 
2-There's another feature which is #define ENABLE_COMMANDS that will enable commands built in the include put it BEFORE the include that put 2 exceptions for either ZCMD will use CMD: if you don't use zcmd it will use OnPlayerCommandText, but you can go into my include and take out the cmds and apply them your own, Those cmds give you the ability to: 1- Add skin ids through the game (/addrclass) and remove them too! (/removerclass).
3- Buttons to use are hold Spacebar and L-ALT to enter the class selection mode or /rclass if u enable my cmds and do that again in the class selection to exit or use /saverskin, you can switch between skins using buttons Y and N.
4- Custom place for the skin selection with a text you can edit through the script with #define RCLASS_TEX "TEXT" its set to 0.3.8 by default put that define BEFORE the include.
5- OnAddSkin(skinid); called the moment a skin is added you can use that for whatever you want.
6- Sum up you can put before including the include.
Code:
#define ENABLE_COMMANDS // Enables commands.
#define ENABLE_CMSGS // Enables connect messages.
#define RCLASS_TEX "My Server" // Enables custom place msg
forward OnAddSkin(skinid);//Called the moment a skin is added.
AddSkin(skinid); //Used to add skins. (better use only once to avoid repeated skins!.
======
Downloads:
Github : LINK
Pastebin : LINK
=====
Related:
You can check my include that fixes and patches the GetPlayerCustomSkin and gives you a IsPlayerUsingCustomSkin feature through this: LINK and for more of my releases visit my signature/pastebin/github.
======
Code:
Change.Log:
None so far.
Planning to optimize the script tomorrow.
=====
You may/may not:
1-You may edit this for your personal use.
2-You may not republish this without my permission.
3-You may not remove the credits from the script ( i didnt add any messages or anything in-game ) i don't like how some people advertise their self blatantly in their scripts with a sendclientmessage everywhere but my credits are comments and print.
======
Enjoy. Let me know if you got any questions/doubts .
