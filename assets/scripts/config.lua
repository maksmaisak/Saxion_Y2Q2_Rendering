
width  = 1920
height = 1200
fullscreen = false
startScene = 'assets/scripts/arena.lua'

bulletSpeed = 30
levelRestartDelay = 2
players = {
    {
        color = {1, 0, 0},
        ai = 'assets/scripts/playerAI_A.lua'
    },
    {
        color = {0, 0, 1},
        ai = 'assets/scripts/playerAI_B.lua'
    }
}

ai = {
    maxSteeringForce = 10000,
    shootCooldown = 2
}