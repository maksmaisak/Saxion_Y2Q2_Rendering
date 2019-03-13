
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

--defaultSkybox = {
--    right  = "textures/skybox/Right.png" ,
--    left   = "textures/skybox/Left.png"  ,
--    top    = "textures/skybox/Top.png"   ,
--    bottom = "textures/skybox/Bottom.png",
--    front  = "textures/skybox/Front.png" ,
--    back   = "textures/skybox/Back.png"
--}

-- The test skybox
--defaultSkybox = {
--    right  = "textures/skybox/test/right.jpg" ,
--    left   = "textures/skybox/test/left.jpg"  ,
--    top    = "textures/skybox/test/top.jpg"   ,
--    bottom = "textures/skybox/test/bottom.jpg",
--    front  = "textures/skybox/test/front.jpg" ,
--    back   = "textures/skybox/test/back.jpg"
--}

-- custom
player = 'assets/scripts/player.lua'
firstLevelPath = 'assets/scripts/scenes/level1.lua'
laser = 'assets/scripts/laser.lua'
resultScreen = 'assets/scripts/UI/resultScreen.lua'
saveFile = 'assets/scripts/save.lua'
levelsDefinition = 'assets/scripts/levelsDefinition.lua'
textColors = {
    primary  = {168/255, 130/255, 97/255, 1},
    backdrop = {25/255, 14/255, 4/255, 0.8}
}

audio = {
    door = {
        open  = {path = 'audio/doorOpen.wav' , volume = 20},
        close = {path = 'audio/doorClose.wav', volume = 20},
    },
    levelFinished = {path = 'audio/doorOpen.wav', volume = 60},
    levelExitFire = {
        ignition   = {path = "audio/levelExit/FireStart.wav"   , volume = 20},
        continuous = {path = "audio/levelExit/FireLoopable.wav", volume = 20}
    },
    ui = {
        buttonPress = {path = 'audio/UIButtonSound.wav', volume = 60}
    }
}