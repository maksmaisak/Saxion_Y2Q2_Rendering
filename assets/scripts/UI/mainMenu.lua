require ('assets/scripts/level/level')
require ('assets/scripts/Utility/gameSerializer')


local isBlocked = false

local mainMenuPanel
local chooseLevelPanel
local creditsPanel

local levelIndex = 1
local numberOfLevels = 4
local buttonSize = 60

local ratio

local scenery = {
	{
		Name = "Camera",
		Transform = {
			position = { x = 0, y = 0, z = 10 }
		},
		Camera = {},
	}
}

local scene = {}

local function playSoundObject(filepath, offset, loop, volume)
	local music = Game.audio.getSound(filepath)
	music.playingOffset = music.duration * offset
    music.loop = loop
    music.volume = volume
    music:play()
end

local function keepAspectRatio(actor, theight)
	
	local sprite = actor:get("Sprite")
	if not sprite then return end

	local textureSize = sprite.textureSize
	ratio = textureSize.x / textureSize.y
	local height = theight
	local width = height * ratio
	local minWidth  = (width  / 2) * -1
	local minHeight = (height / 2) * -1
	actor:get("UIRect").offsetMin = { minWidth, minHeight }
	actor:get("UIRect").offsetMax = { width / 2, height / 2}
end

function makeButton(name,parent,textString,anchorMin,anchorMax,textureFilePath)
	
	buttonActor = Game.makeActor {
		Name = name,
		Transform = {
			parent = parent
		},
		Text = {
			font   = "fonts/kenyanCoffee.ttf",
			fontSize = 50,
			color  = {1,1,1,1},
			string = textString
        },
		UIRect = {
			anchorMin = anchorMin,
			anchorMax = anchorMax,
		},
		Sprite = {
			material = {
				shader	= "sprite",
				texture = textureFilePath
			}
		},
		LuaBehavior = {
			onMouseDown = function(self, button)
				if button == 1 then
					playSoundObject('audio/UIButtonSound.wav',0,false,60)
					
					if name == "StartButton" then
						Game.currentLevel = 1
						Game.loadScene(Config.firstLevelPath)
					end

					if name == "ChooseLevelButton" then
						chooseLevelPanel:get("UIRect").isEnabled	= true
						mainMenuPanel:get("UIRect").isEnabled		= false
					end

					if name == "CreditsButton" then
						creditsPanel:get("UIRect").isEnabled	= true
						mainMenuPanel:get("UIRect").isEnabled	= false
					end

					if name == "ExitButton" then
						Game.quit()
					end

					if name == "BackButtonChooseLevel" then
						chooseLevelPanel:get("UIRect").isEnabled	= false
						mainMenuPanel:get("UIRect").isEnabled	= true
					end

					if name == "BackButtonCredits" then
						creditsPanel:get("UIRect").isEnabled	= false
						mainMenuPanel:get("UIRect").isEnabled	= true
					end
				end
			end,

			--Mouse Over Start
			onMouseEnter = function(self, button)
				self.actor:get("Transform").scale = {1.2,1.2,1.2}
			end,

			onMouseLeave = function(self, button)
				self.actor:get("Transform").scale = {1,1,1}
			end
			--Mouse Over End
		}
	}

	keepAspectRatio(buttonActor,64)
end


function scene:start()

	Game.makeActors(scenery)

	-- load saved data
	local serializer = GameSerializer:new()
	Game.serializer  = serializer
	Game.savedData   = serializer:load(Config.saveFile)

	Game.levels   = dofile(Config.levelsDefinition)
	Game.maxLevel = #Game.levels

-- Start Main Buttons Panel
   	Game.makeActor {
		Name = "MainMenuPanel",
		Transform = {},
		UIRect = {
			anchorMin	= {0, 0},
			anchorMax	= {1, 1}
		}
	}

	makeButton("StartButton","MainMenuPanel","Start",{0.5,0.8},{0.5,0.8},"textures/buttonBackground.png")
	makeButton("ChooseLevelButton","MainMenuPanel","Choose Level",{0.5,0.7},{0.5,0.7},"textures/buttonBackground.png")
	makeButton("CreditsButton","MainMenuPanel","Credits",{0.5,0.6},{0.5,0.6},"textures/buttonBackground.png")
	makeButton("ExitButton","MainMenuPanel","Exit",{0.5,0.5},{0.5,0.5},"textures/buttonBackground.png")
--End Main Buttons Panel

--Start ChooseLevel Panel
	
	Game.makeActor {
		Name = "ChooseLevelPanel",
		Transform = {},
		UIRect = {
			anchorMin = {0, 0},
			anchorMax = {1, 1}
		},		
		Sprite = {
			material = {
				shader	= "sprite",
				texture = "textures/transparent.png"
			}
		},
	}
	
	local arrowLeft = Game.makeActor {
		Name = "ArrowLeft",
		Transform = {
			parent = "ChooseLevelPanel"
		},
		UIRect = {
			anchorMin = {0.05, 0.6},
			anchorMax = {0.05, 0.6}
		},
		Sprite = {
			material = {
				shader	= "sprite",
				texture = "textures/arrowLeft.png"
			}
		},
		LuaBehavior = {
			update = function(self, dt)
				if Game.keyboard.isHeld("left") or (Game.mouse.isHeld(1) and self.actor:get("UIRect").isMouseOver) then
					self.actor:get("Transform").scale = {1.2,1.2,1.2}
				else
					self.actor:get("Transform").scale = {1,1,1}
				end
			end
		}
	}

	local arrowRight = Game.makeActor {
		Name = "ArrowRight",
		Transform = {
			parent = "ChooseLevelPanel"
		},
		UIRect = {
			anchorMin = {0.95, 0.6},
			anchorMax = {0.95, 0.6}
		},
		Sprite = {
			material = {
				shader	= "sprite",
				texture = "textures/arrowRight.png"
			}
		},
		LuaBehavior = {
			update = function(self, dt)
				if Game.keyboard.isHeld("right") or (Game.mouse.isHeld(1) and self.actor:get("UIRect").isMouseOver) then
					self.actor:get("Transform").scale = {1.2,1.2,1.2}
				else
					self.actor:get("Transform").scale = {1,1,1}
				end
			end
		}
	}

	local chooseLevelImage = Game.makeActor {
		Name = "ChooseLevelImage",
		Transform = {
			parent = "ChooseLevelPanel"
		},
		UIRect = {
			anchorMin = {0.5, 0.6},
			anchorMax = {0.5, 0.6}
		},		
		Sprite = {
			material = {
				shader	= "sprite",
				texture = "textures/level" .. levelIndex .. ".jpg"
			}
		},
		LuaBehavior = {
			update = function(self, dt)
				if(isChooseLevelOpened) then
					if(levelIndex < numberOfLevels) then
						if Game.keyboard.isDown("right") or (Game.mouse.isDown(1) and arrowRight:get("UIRect").isMouseOver) then
							print("Is pressed right")

							playSoundObject('audio/UIButtonSound.wav',0,false,60)

							levelIndex = levelIndex + 1
						
							if (levelIndex > numberOfLevels) then
								levelIndex = numberOfLevels
							end

							if (levelIndex >= numberOfLevels) then
								arrowRight:get("UIRect").isEnabled = false
							end

							if (levelIndex >= 1) then
								arrowLeft:get("UIRect").isEnabled = true
							end

							self.actor:remove("Sprite")
							self.actor:add("Sprite", {
								material = {
									shader	= "sprite",
									texture = "textures/level" .. levelIndex .. ".jpg"
								}
							})
						end
					end
					
					if(levelIndex > 1) then
						if Game.keyboard.isDown("left") or (Game.mouse.isDown(1) and arrowLeft:get("UIRect").isMouseOver) then
							print("Is pressed left")

							playSoundObject('audio/UIButtonSound.wav',0,false,60)

							levelIndex = levelIndex - 1

							if(levelIndex < 1) then
								levelIndex = 1
							end

							if (levelIndex <= 1) then
								arrowLeft:get("UIRect").isEnabled = false
							end


							if (levelIndex < numberOfLevels) then
								arrowRight:get("UIRect").isEnabled = true
							end

							self.actor:remove("Sprite")
							self.actor:add("Sprite", {
								material = {
									shader	= "sprite",
									texture = "textures/level" .. levelIndex .. ".jpg"
								}				
							})
						end
					end
				end
			end,

			onMouseDown = function(self, button)
				if button == 1 then
					playSoundObject('audio/UIButtonSound.wav',0,false,60)
					Game.loadScene("assets/scripts/scenes/level"..levelIndex..".lua")
					print("Loaded scene : " ..levelIndex)
				end
			end
		}
	}

	makeButton("BackButtonChooseLevel","ChooseLevelPanel","Back",{0.5,0.1},{0.5,0.1},"textures/buttonBackground.png")
--End ChooseLevel Panel

--Start Credits Panel

	Game.makeActor{
		Name = "CreditsPanel",
		Transform = {},
		UIRect = {
			anchorMin = {0, 0},
			anchorMax = {1, 1}
		},
		Text = {
			font	= "fonts/kenyanCoffee.ttf",
			fontSize = 50,
			color	= {1, 1, 1, 1},
			string	= "CREDITS"
        },
	}

	makeButton("BackButtonCredits","CreditsPanel","Back",{0.5,0.1},{0.5,0.1},"textures/buttonBackground.png")

--End Credits Panel

	Game.makeActor {
		Name = "MainPanelImage",
		Transform = {},
		UIRect = {
			anchorMin = {0,0},
			anchorMax = {1,1}
		},
		Sprite = {
			material = {
				shader	= "sprite",
				texture	= "textures/menuBackgrond.jpg"
			}
		}
	}

	mainMenuPanel = Game.find("MainMenuPanel")
	chooseLevelPanel = Game.find("ChooseLevelPanel")
	creditsPanel	 = Game.find("CreditsPanel")


	creditsPanel:get("UIRect").isEnabled	 = false
	chooseLevelPanel:get("UIRect").isEnabled = false
	arrowLeft:get("UIRect").isEnabled = false

	keepAspectRatio(chooseLevelImage,500)
	keepAspectRatio(arrowLeft,300)
	keepAspectRatio(arrowRight,300)

end

return scene
