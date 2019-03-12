require ('assets/scripts/level/level')
require ('assets/scripts/Utility/gameSerializer')


local isBlocked = false
local isChooseLevelOpened
local mainMenuPanel
local chooseLevelPanel
local creditsPanel

local levelIndex = 1
local buttonSize = 60

local stars = {}
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

local function createStar(aMinX,aMinY,aMaxX,aMaxY)
	return Game.makeActor{
		Name = "Star",
		Transform = {
			parent = "ChooseLevelPanel"
		},
		UIRect = {
			anchorMin = {aMinX, aMinY},
			anchorMax = {aMaxX, aMaxY}
		},
		Sprite = {
			material = {
				shader	= "sprite",
				texture	= "textures/star.png",
			}
		}
	}
end

function makeButton(name,parent,textString,anchorMin,anchorMax,textureFilePath)
	
	buttonActor = Game.makeActor {
		Name = name,
		Transform = {
			parent = parent
		},
		Text = {
			font   = "fonts/arcadianRunes.ttf",
			fontSize = 36,
			color = {0,0,0,1},
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
						isChooseLevelOpened = true
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
						isChooseLevelOpened = false
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

	keepAspectRatio(buttonActor,55)
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

	makeButton("StartButton","MainMenuPanel","Start",{0.5,0.7},{0.5,0.7},"textures/buttonBackground.png")
	makeButton("ChooseLevelButton","MainMenuPanel","Choose Level",{0.5,0.6},{0.5,0.6},"textures/buttonBackground.png")
	makeButton("CreditsButton","MainMenuPanel","Credits",{0.5,0.5},{0.5,0.5},"textures/buttonBackground.png")
	makeButton("ExitButton","MainMenuPanel","Exit",{0.5,0.4},{0.5,0.4},"textures/buttonBackground.png")
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

	local textActorBackground = Game.makeActor {
		Name = "ChooseLevelImageTextBackground",
		Transform = {
			parent = "ChooseLevelPanel"
		},
		UIRect = {
			anchorMin = {0.502, 0.802},
			anchorMax = {0.502, 0.802}
		},
		Text = {
			font     = "fonts/arcadianRunes.ttf",
			fontSize = 50,
			color    = {25/255,14/255,4/255,1},
			string   = "Level : "..levelIndex
        },
	}

	local textActor = Game.makeActor {
		Name = "ChooseLevelImageText",
		Transform = {
			parent = "ChooseLevelPanel"
		},
		UIRect = {
			anchorMin = {0.5, 0.8},
			anchorMax = {0.5, 0.8}
		},
		Text = {
			font     = "fonts/arcadianRunes.ttf",
			fontSize = 50,
			color    = {168/255,130/255,97/255,1},
			string   = "Level : "..levelIndex
        },
	}

	Game.makeActor {
		Name = "ChooseLevelImage",
		Transform = {
			parent = "ChooseLevelPanel"
		},
		UIRect = {
			anchorMin = {0.5, 0.55},
			anchorMax = {0.5, 0.55}
		},		
		Sprite = {
			material = {
				shader	= "sprite",
				texture = "textures/level" .. levelIndex .. ".jpg"
			}
		},
		LuaBehavior = {
			start = function(self)
				self.isFirstUpdate = true
			end,
			update = function(self, dt)
				if(isChooseLevelOpened) then
					local isLevelChanged = false
					
					if self.isFirstUpdate then
						self.isFirstUpdate = false
						isLevelChanged = true
					end

					if levelIndex < Game.maxLevel then
						if Game.keyboard.isDown("right") or (Game.mouse.isDown(1) and arrowRight:get("UIRect").isMouseOver) then
							print("Is pressed right")

							playSoundObject('audio/UIButtonSound.wav',0,false,60)

							levelIndex = levelIndex + 1

							textActor:get("Text").string = "Level : "..levelIndex
							textActorBackground:get("Text").string = "Level : "..levelIndex
						
							if levelIndex > Game.maxLevel then
								levelIndex = Game.maxLevel
							end

							if levelIndex >= Game.maxLevel then
								arrowRight:get("UIRect").isEnabled = false
							end

							if levelIndex >= 1 then
								arrowLeft:get("UIRect").isEnabled = true
							end

							isLevelChanged = true
						end
					end
					
					if levelIndex > 1 then
						if Game.keyboard.isDown("left") or (Game.mouse.isDown(1) and arrowLeft:get("UIRect").isMouseOver) then
							print("Is pressed left")

							playSoundObject('audio/UIButtonSound.wav',0,false,60)

							levelIndex = levelIndex - 1

							textActor:get("Text").string = "Level : "..levelIndex
							textActorBackground:get("Text").string = "Level : "..levelIndex

							if levelIndex < 1 then
								levelIndex = 1
							end

							if levelIndex <= 1 then
								arrowLeft:get("UIRect").isEnabled = false
							end


							if levelIndex < Game.maxLevel then
								arrowRight:get("UIRect").isEnabled = true
							end

							isLevelChanged = true
						end
					end

					if isLevelChanged then
						isLevelChanged = false

						-- destroy all the stars from previous level before creating
						-- the new ones
						for k,v in ipairs(stars) do
							if v ~= nil then
								v:remove("Sprite")
								v = nil
							end
						end

						local totalNumberOfStars = 0
						local savedLevel = Game.savedData[levelIndex]

						if savedLevel ~= nil then
							totalNumberOfStars = savedLevel.stars

						self.actor:remove("Sprite")
						self.actor:add("Sprite", {
							material = {
								shader	= "sprite",
								texture = "textures/levelCompleted/level"..levelIndex.."Complete.png"
							}				
						})
						end

						local anchorValue = 0.4
						local anchorStep  = 0.1

						if savedLevel == nil then
							self.actor:remove("Sprite")
							self.actor:add("Sprite", {
							material = {
								shader	= "sprite",
								texture = "textures/levelUncompleted/level"..levelIndex.."Uncomplete.png"
							}				
							})
						end

						for i = 1, totalNumberOfStars do
							print("Created star")
							self.starActor = createStar(anchorValue,0.3,anchorValue,0.3)
							stars[#stars + 1] = self.starActor
							keepAspectRatio(self.starActor,100)
							anchorValue = anchorValue + anchorStep
						end
					end
				end


				if Game.keyboard.isDown("enter") or (Game.mouse.isDown(1) and chooseLevelImage:get("UIRect").isMouseOver) then
					local level = Game.savedData[levelIndex]
					
					if level == nil then
						return
					end

					playSoundObject('audio/UIButtonSound.wav',0,false,60)
					Game.loadScene(Game.levels[levelIndex].path)
					print("Loaded scene : " ..levelIndex)
					Game.currentLevel = levelIndex
				end
			end
		}
	}

	makeButton("BackButtonChooseLevel","ChooseLevelPanel","Back",{0.5,0.15},{0.5,0.15},"textures/buttonBackground.png")
--End ChooseLevel Panel

--Start Credits Panel

	Game.makeActor{
		Name = "CreditsPanel",
		Transform = {},
		UIRect = {
			anchorMin = {0, 0},
			anchorMax = {1, 1}
		}
	}

	Game.makeActor {
		Name = "CreditsText",
		Transform = {
			parent = "CreditsPanel",
		},
		UIRect = {
			anchorMin = {0.01, 0.05},
			anchorMax = {1, 1}
		},
		Text = {
			font   = "fonts/arcadianRunes.ttf",
			fontSize = 30,
			color = {168/255,130/255,97/255,1},
			string = "        Credits\n\nEngineers\n\nMaks Maisak\nCosmin Bararu\nGeorge Popa\n\nDesigners\n\nKaterya Malyk\nGustav Eckrodt\nEmre Hamazkaya\nLea Kemper\nYucen Bao"
		}
	}

	Game.makeActor {
		Name = "CreditsTextBackround",
		Transform = {
			parent = "CreditsPanel",
		},
		UIRect = {
			anchorMin = {0.01002, 0.05002},
			anchorMax = {1.002, 1.002}
		},
		Text = {
			font   = "fonts/arcadianRunes.ttf",
			fontSize = 30,
			color = {25/255,14/255,4/255,0.8},
			string = "        Credits\n\nEngineers\n\nMaks Maisak\nCosmin Bararu\nGeorge Popa\n\nDesigners\n\nKaterya Malyk\nGustav Eckrodt\nEmre Hamazkaya\nLea Kemper\nYucen Bao"
		}
	}

	makeButton("BackButtonCredits","CreditsPanel","Back",{0.5,0.15},{0.5,0.15},"textures/buttonBackground.png")

--End Credits Panel

	menuBackground = Game.makeActor {
		Name = "MainPanelImage",
		Transform = {},
		UIRect = {
			anchorMin = {0,0},
			anchorMax = {1,1}
		},
		Sprite = {
			material = {
				shader	= "sprite",
				texture	= "textures/menuBackground.jpg"
			}
		}
	}

	mainMenuPanel = Game.find("MainMenuPanel")
	chooseLevelPanel = Game.find("ChooseLevelPanel")
	chooseLevelImage = Game.find("ChooseLevelImage")
	creditsPanel	 = Game.find("CreditsPanel")


	creditsPanel:get("UIRect").isEnabled	 = false
	chooseLevelPanel:get("UIRect").isEnabled = false
	arrowLeft:get("UIRect").isEnabled = false

	keepAspectRatio(chooseLevelImage,400)
	keepAspectRatio(arrowLeft,300)
	keepAspectRatio(arrowRight,300)

end

return scene
