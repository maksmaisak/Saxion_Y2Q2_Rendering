require('assets/scripts/object')

TutorialScreen = Object:new()

function TutorialScreen:init()
	self:startTutorial()
end

function TutorialScreen:startTutorial()

	if not Game.currentLevel or Game.currentLevel > 2 then
		return
	end

	self.levelTutorial = Game.makeActor {
		Name = "LevelTutorial",
		Transform = {
			scale = {0,0,0}
		},
		UIRect = {
			anchorMin = {0.2, 0.9},
			anchorMax = {0.2, 0.9}
		},
		Text = {
			font   = "fonts/arcadianRunes.ttf",
			fontSize = 40,
			color  = Config.textColors.primary,
			string = Game.currentLevel == 1 and "To move press arrow keys" or "To activate button press SHIFT + arrow key"
		}
	}

	self.levelTutorial:get("Transform"):tweenScale({1, 1, 1}, 2, Ease.inQuart)
end


