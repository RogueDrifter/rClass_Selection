# rClass_Selection

[![sampctl](https://shields.southcla.ws/badge/sampctl-rClass_Selection-2f2f2f.svg?style=for-the-badge)](https://github.com/RogueDrifter/rClass_Selection)

## Installation

Simply install to your project:

```bash
sampctl package install RogueDrifter/rClass_Selection
```

Include in your code and begin using the library:

```pawn
#include <rClass_Selection>
```

## Usage

```pawn
#define MAX_SKINS_USED [NUMBER] //Max skins you use
```

Example code:
```pawn
public OnGameModeInit() 
{ 
    AddSkin(25001);//add skin id 25001 to the class selection. 
    return 1; 
}  
```

To add skins through game:
```pawn
/addrclass
```
To remove them:
```pawn
/removerclass
```

  - Buttons to use are hold Spacebar and L-ALT to enter the class selection mode or /rclass if u enable my cmds and do that again in the class selection to exit or use /saverskin, you can switch between skins using buttons Y and N.<br/>
<br/>
 - Custom place for the skin selection with a text you can edit through the include its 0.3.8 skins by default.<br/>

```pawn
#define ENABLE_COMMANDS // Enables commands.
#define ENABLE_CMSGS // Enables connect messages.
forward OnAddSkin(skinid); //Called the moment a skin is added.
AddSkin(skinid); //Used to add skins.
```

## Testing

To test, simply run the package:

```bash
sampctl package run
```
