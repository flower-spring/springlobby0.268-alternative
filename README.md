# springlobby0.268-alternative

springlobby 0.268 with some fixes and new features.


|                           Summary                            |      |
| :----------------------------------------------------------: | ---- |
| [Fixes and new features made to springlobby 0.268](#Level_1_summary) |      |
| [Problems present in 0.268 and still exist with 0.268-alternative](#Level_2_summary) |      |
|           [Features to consider](#Level_3_summary)           |      |
| [Contact/infos about springlobby0.268-alternative](#Level_4_summary) |      |
| [The exes at https://github.com/flower-spring/springlobby0.268-alternative/releases/tag/1](#Level_5_summary) |      |
| [Readme from springlobby original (https://github.com/springlobby/springlobby)](#Level_6_summary) |      |


&nbsp;  
&nbsp;  


# Fixes and new features made to springlobby 0.268 <a id="Level_1_summary"></a>


## Battlerrom tab : 

* contextual menu fixed: some elements wasn't working. Now, in tchat bar, no more needed to type "!ring playername" necessarily. Just right click on a player name and then click on ring.
  &nbsp;  
   ![alt text](images_for_readme/contextual_menu.png)     
  &nbsp;  

* better behavior with cases to tick.
  ![alt text](images_for_readme/spectator_imready_autolaunch_fix.png)

  At least, auto-launch game case is not auto ticked when you go spectator. So game not autolaunch.

  
  &nbsp;  
  &nbsp;  

* 4 new buttons : !status, !balance, !fixcolors, !ring.
  ![alt text](images_for_readme/4_buttons_added_battleroom_tab.png)
  &nbsp;  
  (before:
  ![alt text](images_for_readme/battleroom_tab_buttons_before.png)
  )
  &nbsp;  
  &nbsp;  

* Fixed the disappearance of some buttons if you changed the size of the window with battleroomtab activated. Sometime the start button was disappearing. Now it should be solved by placing buttons on 2 lines. (Tested. Worked for windows. Not for linux.)
&nbsp;  


| As you could see Spectate button is like rogned | ![alt text](images_for_readme/sometimes_start_button_disappeared.png) |
| ----------------------------------------------- | ------------------------------------------------------------ |
|                                                 |                                                              |

&nbsp;  
&nbsp;  

### Select map window : now background is black, instead grey. Could less hurt eyes.

| before                                                                          | after                                                                            |
| ------------------------------------------------------------------------------- | -------------------------------------------------------------------------------- |
| ![alt text](images_for_readme/select_map_grey_background.png) | ![alt text](images_for_readme/select_map_black_background.png) |
&nbsp;    

## Chat tab : new column with TS displayed (after you joined battleroom tab at least one time): so you can have ts of all players now visible here.
&nbsp;  
  ![alt text](images_for_readme/ts_added_official_server_size_reduced.png)     

&nbsp;  


## Battlelist tab : new column with TS displayed (after you joined battleroom at least one time)
![alt text](images_for_readme/battlelist_tab.png)
&nbsp;  
&nbsp;  

## Message : "You are already in a battle..." removed.
![alt text](images_for_readme/window_you_are_already_in_a_battle.png)
&nbsp;  
***

# Problems in 0.268 and still existing with 0.268-alternative :<a id="Level_2_summary"></a>

- After the map is changed from selectmap window the map name visible in battleroom tab is not changed.
- Country flags are not displayed when mouse is over a player name (unsure if this situation is generalized or it's just for me).
- Maps are not sorted correctly after you selected one item. It's needed to click on sign "<" or ">".  
- Parameters are displayed two times instead only one, in select map window.

| Parameters displayed two times in select map window. | ![parameters_in_double_selectmap_window](images_for_readme/parameters_in_double_selectmap_window.png) |
| ---------------------------------------------------- | ------------------------------------------------------------ |
|                                                      |                                                              |

&nbsp;  
&nbsp;  

# Features to consider:<a id="Level_3_summary"></a>
- Auto launch a replay if double click on a line of the replays list (it is when you are in replays tab): could be less complicated than having to click on the button watch.
- Display geos positions on the map

| Actually geos positions are not displayed on map | ![feature_request_show_geospots_on_map](images_for_readme/feature_request_show_geospots_on_map.png) |
| :----------------------------------------------: | ------------------------------------------------------------ |
|                                                  |                                                              |

&nbsp;  
&nbsp;  
&nbsp;  

# Contact/infos about springlobby0.268-alternative:<a id="Level_4_summary"></a>

You could contact me on discord, github or in springlobby: my pseudo is flower.
&nbsp;  
&nbsp;  
&nbsp;  

# The exes at https://github.com/flower-spring/springlobby0.268-alternative/releases/tag/1 :<a id="Level_5_summary"></a>

I didn't uploaded an installer like the original lobby had with an installation in Program Files(x86). It took time to understand how to do. Maybe in the future I'll upload one. For the moment, you should have the choice between

-  an exe (22Mb)
- an installer (witch contain the same exe (22Mb), except the installer has a smaller size (about 6Mb) and you need more steps to obtain the exe(22Mb) after you have downloaded the installer(6Mb)).
&nbsp;  
&nbsp;  
&nbsp;  

# Readme from springlobby original (https://github.com/springlobby/springlobby)<a id="Level_6_summary"></a>

all installation information can be found here:
https://github.com/springlobby/springlobby/wiki/Install

for compiling from source see:
https://github.com/springlobby/springlobby/wiki/InstallFromSource

[![Build Status](https://travis-ci.org/springlobby/springlobby.svg?branch=master)](https://travis-ci.org/springlobby/springlobby)

#License

SpringLobby is released under GPL v2 (or later):

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License along
with this program; if not, write to the Free Software Foundation, Inc.,
51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.



