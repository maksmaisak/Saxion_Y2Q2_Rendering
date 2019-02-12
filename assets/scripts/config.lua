
-- engine
width  = 1920
height = 1200
fullscreen = false
framerateCap = 60
startScene = 'assets/scripts/scenes/level.lua'

-- custom
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