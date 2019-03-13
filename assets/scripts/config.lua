
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

local function makeSound(path, volume, loop, offset)

    local sound = Game.audio.makeSound(path)
    if not sound then return nil end

    sound.volume = volume or 100
    sound.loop   = loop or false
    sound.playingOffset = offset and sound.duration * offset or 0
    return sound
end

local function makeMusic(path, volume, loop, offset)

    local music = Game.audio.makeMusic(path)
    if not music then return nil end

    music.volume = volume or 100
    music.loop   = loop or false
    music.playingOffset = offset and music.duration * offset or 0
    return music
end

audio = {
    ambience = makeMusic('audio/Ambience.wav'),
    door = {
        open  = makeSound('audio/doorOpen.wav' , 20),
        close = makeSound('audio/doorClose.wav', 20),
    },
    levelFinished = makeSound('audio/doorOpen.wav', 60),
    levelExitFire = {
        ignition   = makeSound('audio/levelExit/FireStart.wav'   , 20),
        continuous = makeMusic('audio/levelExit/FireLoopable.wav', 20, true)
    },
    ui = {
        buttonPress = makeSound('audio/UIButtonSound.wav', 20),
        stars = {
            makeSound('audio/stars/1Star.wav'),
            makeSound('audio/stars/2Star.wav'),
            makeSound('audio/stars/3Star.wav')
        }
    },
}