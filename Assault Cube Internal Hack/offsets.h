// Offsets for Assault Cube 1.2.0.2

#pragma once

/*
Player Position XY : 0x4
Player Position XY : 0x8
Player Position Z : 0xC
Player Yaw : 0x40
Player Pitch : 0x44
Player Roll : 0x48

Player Armor : 0xFC
Player Pistol : 0x114
Player Carbine : 0x118
Player Shotgun : 0x11C
Player MachineGun : 0x120
Player Sniper : 0x124
wPlayer A - Rifle : 0x128
Player Pistol Clip : 0x13C
Player Carbine Clip : 0x140
Player Shotgun Clip        0x144
Player MachineGun Clip : 0x148
Player Sniper Clip : 0x14C
Player A - Rifle Clip : 0x150
Player Grenade Ammo : 0x158
Time Between Knifes : 0x160
Pistol Timer : 0x164
Carbine Timer : 0x168
Shotgun Timer : 0x16C
Machine Gun Timer : 0x170
Sniper Timer : 0x174
A - Rifle Timer : 0x178
Grenade Timer : 0x180
TeamNum1 : 0x204
Mouse Button Down(? ) : 0x224
TeamNum2 : 0x32C

Entity Base : "ac_client.exe" + 0x110D90 / 510D90
EntityBase Offsets : 0x0
0x0 + (4 bytes each player, starts at 0) 

Shot Start -             0x46367F
Remove Gun Animation -         0x463704
All Guns Auto JMP -         0x463716
All Guns Auto NOP -         0x46371B
Recoil Begin -             0x463781
Recoil End -             0x46378E
No Time Between Shots NOP -     0x4637E4
Gun Shot Dec - 004637E9
Shoots In Odd Direction NOP -     0x463841
Bullets Don't Fly NOP -     0x463849
Shoots Around Feet NOP -     0x46384E
Only Shoots Directly Up NOP -     0x463861
Shot End -             0x4638DB

AoB
------------------------------------------------------------------
Remove Gun Animation -
            \x89\xB1\x00\x00\x00\x00\x8B\x56\x0C
            xx????xxx

All Guns Auto JMP -
            \x75\x09\x8B\x46\x08
            xxxxx

All Guns Auto NOP -
            \x88\x98\x24\x02\x00\x00\x8B\x4E\x04
            xxxxxxxxx

Recoil -
            \x8B\x16\x8B\x52\x14\x50\x8D\x4C\x24\x1C\x51\x8B\xCE\xFF\xD2\x8B\x46\x08
            xxxxxxxxxxxxxxxxxx

No Time Between Shots NOP -
            \x89\x0A\x8B\x76\x14
            xxxxx

Gun Shot Dec - 5 BYTES IN FRONT
            \x89\x0A\x8B\x76\x14\xFF\x0E\x57\x8B\x7C\x24\x14\x8D\x74\x24\x28\xE8\x00\x00\x00\x00
            xxxxxxxxxxxxxxxxx????
*/

const unsigned int ClientAddress = 0x400000;  
const unsigned int playerX = 0x4;
const unsigned int playerY = 0x8;
const unsigned int playerZ = 0xC;
const unsigned int PlayerHealth = 0xF8;
const unsigned int PlayerBaseOffset = 0x109B74;
const std::vector<unsigned int> PlayerAmmo = { 0x378, 0x14, 0x0 };
const unsigned int RecoilBegin = 0x463781;
const unsigned int entityListOffset = 0x10f4f8;
const unsigned int totalPlayersOffset = 0x10F500;
const unsigned int teamOffset = 0x32C;
const unsigned int playerYaw = 0x40;
const unsigned int playerPitch = 0x44;
