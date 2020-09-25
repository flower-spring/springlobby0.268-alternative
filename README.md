# Springlobby0.268-alternative

springlobby 0.268 with some fixes and some changes.

# Changes compared to 0.268


## Battlerrom tab : 

* contextual menu fixed: so in tchat bar you don't have to write "!ring playername" necessarily. Just right click on a player name and then click on ring.
  &nbsp;  
   ![alt text](images_for_readme/contextual_menu.png)     
  &nbsp;  

* better behavior with cases to tick.
  ![alt text](images_for_readme/spectator_imready_autolaunch_fix.png)

  Auto-launch game case not auto ticked when you go spectator. So game not autolaunch.

  
  &nbsp;  
  &nbsp;  

* 4 new buttons : status, balance, fixcolors, ring.
  ![alt text](images_for_readme/4_buttons_added_battleroom_tab.png)
  &nbsp;  
  (before:
  ![alt text](images_for_readme/battleroom_tab_buttons_before.png)
  )
  &nbsp;  
  &nbsp;  

* Fixed the disappearance of some buttons if you changed the size of the window with battleroomtab activated. Sometime the start button was disappearing. Now it should be solved by placing buttons on 2 lines. (Tested. Worked for windows. Not for linux.)
&nbsp;  
![alt text](images_for_readme/sometimes_start_button_disappeared.png)
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

## Problems present in 0.268 and still exist with 0.268-alternative :

- After the map is changed from selectmap window the map name visible in battleroom tab is not changed.

- Country flags are not displayed when mouse is over a player name (unsure if this situation is generalized or it's just for me).
- Parameters are displayed two times instead only one, in select map window.

| Parameters displayed two times in select map window. | ![parameters_in_double_selectmap_window](images_for_readme/parameters_in_double_selectmap_window.png) |
| ---------------------------------------------------- | ------------------------------------------------------------ |
|                                                      |                                                              |
- Maps are not sorted correctly after you selected one item. It's needed to click on sign "<" or ">". 
&nbsp;  
&nbsp;  

## Features to consider:
- Auto launch a replay if double click on a line of the replays list (it is when you are in replays tab).
- Display geos positions on the map

| Actually geos positions are not displayed on map | ![feature_request_show_geospots_on_map](images_for_readme/feature_request_show_geospots_on_map.png) |
| :----------------------------------------------: | ------------------------------------------------------------ |
|                                                  |                                                              |

&nbsp;  
&nbsp;  
&nbsp;  


# Readme from springlobby original (https://github.com/springlobby/springlobby)
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



