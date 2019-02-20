
-- engine
width  = 1920
height = 1080
fullscreen = false
framerateCap = 240
startScene = 'assets/scripts/scenes/mainMenu.lua'
referenceResolution = {1920, 1080}

-- custom
player = 'assets/scripts/player.lua'
firstLevelPath = 'assets/scripts/scenes/test/level1.lua'

-- old stuff
bulletSpeed = 30
levelRestartDelay = 2
arenaSize = 60
maxNumActiveBullets = 10
players = {
    {
        color = {1, 0, 0},
        ai = 'assets/scripts/playerA.lua'
    },
    {
        color = {0, 0, 1},
        ai = 'assets/scripts/playerA.lua'
    }
}
ai = {
    maxSteeringForce = 10000,
    shootCooldown = 2
}