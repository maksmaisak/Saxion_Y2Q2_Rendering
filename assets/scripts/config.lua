
-- engine
width  = 1920
height = 1080
fullscreen = false
framerateCap = 240
startScene = 'assets/scripts/scenes/test/testUI.lua'
firstLevelDefinition = 'assets/scripts/scenes/definition1.lua'

-- custom
bulletSpeed = 30
levelRestartDelay = 2
arenaSize = 60
maxNumActiveBullets = 10
player = 'assets/scripts/player.lua'
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