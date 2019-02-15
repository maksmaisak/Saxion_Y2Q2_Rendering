local scenery = {
	{
		Name = "camera",
		Transform = {
		position = { x = 0, y = 0, z = 10 }
		},
		Camera = {},
	}
}

local scene ={}

function scene.start()

	Game.makeActors(scenery)

	Game.makeActor {
		Name = "MainPanel",
		Transform = {},
		UIRect = {
			anchorMin = {0,0},
			anchorMax = {1,1}
		},
		Sprite = {
			material = {
				shader		= "sprite",
				texture		= "textures/background.png"
			}
		}
	}

	Game.makeActor {
		Name = "StartButton",
		Transform = {},
		UIRect = {
			ancorMin	= {0.5,0.5},
			anchorMax	= {0.5,0.5},
			offsetMin	= {200,200},
			offsetMax	= {100,100},
		},
		Sprite = {
			material = {
				shader = "sprite",
				texture = "textures/runicfloor.png"
			}
		},

	}
end

return scene
