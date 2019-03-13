
-- engine
width  = 1920
height = 1080
fullscreen = false
framerateCap = 240
vsync = false
enableStaticBatching = true
enableDebugOutput    = true
referenceResolution = {1920, 1080}
startScene = 'assets/scripts/UI/mainMenu.lua'
--startScene = 'assets/scripts/scenes/level1.lua'
--startScene = 'assets/scripts/scenes/test/luaScene.lua'
--startScene = 'assets/scripts/scenes/test/testTweening.lua'

-- custom
player = 'assets/scripts/player.lua'
firstLevelPath = 'assets/scripts/scenes/level1.lua'
laser = 'assets/scripts/laser.lua'
resultScreen = 'assets/scripts/UI/resultScreen.lua'
saveFile = 'assets/scripts/save.lua'
levelsDefinition = 'assets/scripts/levelsDefinition.lua'
textColors = {
    primary = {168/255, 130/255, 97/255, 1},
    backdrop = {25/255, 14/255, 4/255, 0.8}
}