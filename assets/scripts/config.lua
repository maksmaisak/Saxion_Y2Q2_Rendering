--
-- User: maks
-- Date: 29/12/18
-- Time: 01:26
--

width  = 1920
height = 1200

startScene = 'assets/scripts/arena.lua'

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