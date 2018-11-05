NJIT - Fall 2018 - IT 266001 - Game Mod Development
Quake 4 Modterm

What's In This Mod?
  • Changes game weapons
  • Abilities that change player size and movement
  • Wallrunning (Similar to Counter Strike Surfing)

How to Play Mod
  • Download reository's zip file - https://github.com/winielson/266Midterm/archive/master.zip
  • Extract contents into folder placed in game location
    ◦ For steam: C:\Program Files (x86)\Steam\steamapps\common\Quake 4
  • Load Quake 4
  • Click Mods option on bottom left of the screen
  • Create a new game and play
  • Press CTRL + SHIFT + ` to enable console. Type "give ammo" in order to test all the guns. Type "spawn weaponmod_rocketlauncher_homing" to enable guided nails mod. Type "give shroom" or "give small" to change size, stepsize, and jump. Type "give norm" to go back to restore normal attributes. NOTE: Can only call these once per session.

Weapon Changes:

Blaster: Imitation of Magnum from Halo
  • Shoots hitscan bullets
  • Reloadable and has clip size of 8
  • Changed entire WeaponBlaster.cpp for functionality
  
Machine Gun: Imitation of Battle Rifle from Halo
  • Shoots in burst of three (Scoped burst spread is big for presentation purpose)
  • Cannot hold fire
  • Clipe size of 36
  • Similar firerate to Halo BR
  
Shotgun: Alt-fire mode added
  • When tap clicking shotgun shoots normally
  • When attack is held a spread of DMG projectiles is shot
    ◦ Took ideas, including fireheld, from WeaponMachinegun.cpp and incorporated them into WeaponShotgun.cpp
    ◦ Added projectile header file in .cpp
    ◦ Added "def_altProjectile" into def files, as well as DMG projectile definitions

HyperBlaster: NO CHANGES

GrenadeLauncher: Grenade Launcher Grenades
  • When single click, grenade launcher grenades are thrown
  • When hold click 15 are thrown
    ◦ Incorporated fireHeld from machinegun.cpp and added alt fire state
  • Has clipsize of 1 to imitate grenades

Nailgun: Rocket Nailgun
  • Instead of nails, shoots rockets
  
Rocketlauncher: Nail Launcher
  • Shoots nails as regular projectiles
  • When "spawn weaponmod_rocketlauncher_homing" is typed into commands, multiple shot nails can be directed by holding right click
  
Railgun: Spartan Laser
  • Acts like spartan laser from halo 3
  • Does not shoot until charge time is met
  • Took charge and update attack logic from blaster.cpp and incorporated it into railgun.cpp
  
Lightninggun: NO CHANGES

DMG: NO CHANGES

Napalmgun: Baby Molotovs
  • Throws baby molotovs instead of napalm gun
  • Has clipsize of 1 to imitate grenades
  
Added Powerups:

Shroom: "give shroom"
  • Makes player's height, viewheight, crouchheight, crouchviewheight, and stepsize higher 
  • Makes jumpheight lower
  
Shroom: "give small"
  • Makes player's height, viewheight, crouchheight, crouchviewheight, and stepsize smaller
  • Makes jumpheight higher
  
Shroom: "give norm"
  • Restores default player state
  
Wallrunning: Walking speed is higher so acts as running. Wallrunning is like CS surfing. Can go up and slide slopes easily, but not flat walls. 

  
  
  
