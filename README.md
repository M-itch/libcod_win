The Call of Duty extension *libcod* is adding new server-side functions to:

 - Call of Duty 2 1.0 (Supported OS: Windows XP, Windows 10)
 - Call Of Duty 2 1.3 (Supported OS: Windows XP, Windows 10)

To improve overall Windows support, the binary must be rewritten as shown here: https://killtube.org/showthread.php?2569-Hooking-exe-without-dll-injection-the-simple-way-D

ATM these .dll's are not supposed to be injected, that would likely crash the server. I plan to just add all Windows version by hand. This will make it easier in future to use libcod_win, because injecting a .dll all the time is just annoying and not very obvious for beginners.

Mods depending on *libcod*:
- http://killtube.org/showthread.php?1533-DOWNLOAD-CoD2-Surf-Mod
- http://killtube.org/showthread.php?1527-DOWNLOAD-CoD2-Basetdm-Mod
- http://killtube.org/showthread.php?1593-DOWNLOAD-CoD2-Portal-Mod
- Jump-Mod by IzNoGoD
	
Little overview of added functions:
- MySQL
- setVelocity, getVelocity, addVelocity (needed for the mods: portal, surf)
- keyPressed-functions for left, right, forward, backward, leanleft, leanright, jump etc., (needed for: surf, doublejump made by IzNoGod)
- blazing fast astar-implementation (needed for: zombots)
- setAlive-function (needed for: zombots, so xmodels are damagable without damage-trigger... zombots in stockmaps)
- disableGlobalPlayerCollision() 
	
Community / Help: http://killtube.org/forum.php
