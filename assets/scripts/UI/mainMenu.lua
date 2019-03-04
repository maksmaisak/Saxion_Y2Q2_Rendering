require ('assets/scripts/level/level')


local isBlocked = false
local isChooseLevelOpened = false
local MainMenuPanel
local chooseLevelPanel
local creditsPanel
local levelIndex = 1
local numberOfLevels = 4
local ratio
local buttonSize = 60

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


function scene:start()

	IsMenuOpened = true

	Game.makeActors(scenery)

	-- Start Main Buttons Panel
   	Game.makeActor {
		Name = "MainMenuPanel",
		Transform = {},
		UIRect = {
			anchorMin	= {0, 0},
			anchorMax	= {1, 1}
		}
	}

	Game.makeActor {
		Name = "ButtonsPanel",
		Transform = {
			parent = "MainMenuPanel"
		},
		UIRect = {
			anchorMin	= {0.85, 0.05},
			anchorMax	= {0.85, 0.35},
			offsetMin	= {-150, 0},
			offsetMax	= { 150, 0}
		},
	}

	local startButton = Game.makeActor {
		Name = "StartButton",
		Transform = {
			scale  = {1,1,1},
			parent = "ButtonsPanel"
		},
		Text = {
			font   = "fonts/kenyanCoffee.ttf",
			fontSize = 50,
			color  = {1, 1, 1, 1},
			string = "Start"
        },
		UIRect = {
			anchorMin = {0, 0.75},
			anchorMax = {1, 1},
			offsetMin = {0,5},
			offsetMax = {0,-5}
		},
		Sprite = {
			material = {
				shader	= "sprite",
				texture = "textures/transparent.png"
			}
		},
		LuaBehavior = {
			onMouseDown = function(self, button)
				if button == 1 then
					Game.loadScene(Config.firstLevelPath)
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

	local chooseLevelButton = Game.makeActor {
		Name = "ChooseLevelButton",
		Transform = {
			parent = "ButtonsPanel"
		},
		Text = {
			font = "fonts/kenyanCoffee.ttf",
			fontSize = 50,
			color = {1, 1, 1, 1},
			string = "Choose Level"
        },
		UIRect = {
			anchorMin = {0, 0.5},
			anchorMax = {1, 0.75},
			offsetMin = {0,5},
			offsetMax = {0,-5}
		},
		Sprite = {
			material = {
				shader	= "sprite",
				texture = "textures/transparent.png"
			}
		},
		LuaBehavior = {
			onMouseDown = function(self, button)
				if button == 1 then
					isChooseLevelOpened = true
					chooseLevelPanel:get("UIRect").isEnabled = true
					MainMenuPanel:get("UIRect").isEnabled = false
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

	local creditsButton = Game.makeActor {
		Name = "CreditsButton",
		Transform = {
			parent = "ButtonsPanel"
		},
		UIRect = {
			anchorMin = {0, 0.25},
			anchorMax = {1, 0.5},
			offsetMin = {0,5},
			offsetMax = {0,-5}

		},
		Text = {
			font = "fonts/kenyanCoffee.ttf",
			fontSize = 50,
			color = {1, 1, 1, 1},
			string = "Credits"
        },
		Sprite = {
			material = {
				shader	= "sprite",
				texture = "textures/transparent.png"
			}
		},
		LuaBehavior = {
			onMouseDown = function(self, button)
				if button == 1 then
					creditsPanel:get("UIRect").isEnabled		= true
					MainMenuPanel:get("UIRect").isEnabled	= false
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

	local exitButton = Game.makeActor {
		Name = "ExitButton",
		Transform = {
			parent = "ButtonsPanel"
		},
		UIRect = {
			anchorMin = {0, 0},
			anchorMax = {1, 0.25},
			offsetMin = {0,5},
			offsetMax = {0,-5}
		},
		Text = {
			font = "fonts/kenyanCoffee.ttf",
			fontSize = 50,
			color = {1, 1, 1, 1},
			string = "Exit"
        },
		Sprite = {
			material = {
				shader	= "sprite",
				texture = "textures/transparent.png"
			}
		},
		LuaBehavior = {
			onMouseDown = function(self, button)
				if button == 1 then
					Game.quit()
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
					Game.loadScene("assets/scripts/scenes/level"..levelIndex..".lua")
					print("Loaded scene : " ..levelIndex)
				end
			end
		}
	}

	local backButtonChooseLevel = Game.makeActor {
		Name = "BackButtonChooseLevel",
		Transform = {
			parent = "ChooseLevelPanel"
		},
		UIRect = {
			anchorMin = {0.5, 0.15},
			anchorMax = {0.5, 0.1},
		},
		Text = {
			font = "fonts/kenyanCoffee.ttf",
			fontSize = 50,
			color = {1, 1, 1, 1},
			string = "Back"
        },
		Sprite = {
			material = {
				shader	= "sprite",
				texture = "textures/transparent.png"
			}
		},
		LuaBehavior = {
			onMouseDown = function(self, button)
				if button == 1 then
					isChooseLevelOpened = false
					print("Go back to main")
					MainMenuPanel:get("UIRect").isEnabled = true
					chooseLevelPanel:get("UIRect").isEnabled = false
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

	local backButtonCredits = Game.makeActor {
		Name = "BackButtonCredits",
		Transform = {
			parent = "CreditsPanel"
		},
		UIRect = {
			anchorMin = {0.5, 0.1},
			anchorMax = {0.5, 0.1}
		},
		Text = {
			font	= "fonts/kenyanCoffee.ttf",
			fontSize = 50,
			color	= {1, 1, 1, 1},
			string	= "Back"
        },
		Sprite = {
			material = {
				shader	= "sprite",
				texture = "textures/transparent.png"
			}
		},
		LuaBehavior = {
			onMouseDown = function(self, button)
				if button == 1 then
					creditsPanel:get("UIRect").isEnabled	 = false
					MainMenuPanel:get("UIRect").isEnabled = true
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


--End Credits Panel

	Game.makeActor {
		Name = "MainPanel",
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

	MainMenuPanel = Game.find("MainMenuPanel")
	chooseLevelPanel = Game.find("ChooseLevelPanel")
	creditsPanel	 = Game.find("CreditsPanel")

	creditsPanel:get("UIRect").isEnabled	 = false
	chooseLevelPanel:get("UIRect").isEnabled = false
	arrowLeft:get("UIRect").isEnabled = false

	keepAspectRatio(chooseLevelImage,500)
	keepAspectRatio(backButtonChooseLevel,95)
	keepAspectRatio(backButtonCredits,95)
	keepAspectRatio(arrowLeft,256)
	keepAspectRatio(arrowRight,256)

end

return scene
