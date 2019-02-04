
width  = 1920
height = 1200
fullscreen = true
vsync = false
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

print(players[1].ai)