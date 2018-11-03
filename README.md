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
  • Press CTRL + SHIFT + ` to enable console. Type give ammo in order to test all the guns. Type spawn weaponmod_rocketlauncher_homing to enable guided nails mod.

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



  
  
  
  
