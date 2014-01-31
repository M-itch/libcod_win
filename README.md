The Call of Duty extension *libcod* is adding new server-side functions to:

 - Call Of Duty 2 1.2
 - Call Of Duty 2 1.3
 - Call Of Duty 4 1.7

Run InjectDLL to inject the DLL into your server.

Mods depending on *libcod*:
- http://killtube.org/showthread.php?1533-DOWNLOAD-CoD2-Surf-Mod
- http://killtube.org/showthread.php?1527-DOWNLOAD-CoD2-Basetdm-Mod
- http://killtube.org/showthread.php?1593-DOWNLOAD-CoD2-Portal-Mod
- Jump-Mod by IzNoGod
	
Little overview of added functions:
- MySQL
- setVelocity, getVelocity, addVelocity (needed for the mods: portal, surf)
- keyPressed-functions for left, right, forward, backward, leanleft, leanright, jump etc., (needed for: surf, doublejump made by IzNoGod)
- blazing fast astar-implementation (needed for: zombots)
- setAlive-function (needed for: zombots, so xmodels are damagable without damage-trigger... zombots in stockmaps)
- disableGlobalPlayerCollision() 
	
Community / Help: http://killtube.org/forum.php
