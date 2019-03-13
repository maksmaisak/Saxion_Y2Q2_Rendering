require('assets/scripts/object')

TutorialScreen = Object:new()

function TutorialScreen:init()
	self:startTutorial()
end

function TutorialScreen:startTutorial()

	if Game.currentLevel then
		if Game.currentLevel <=2 then
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
					color  = {0, 0, 0, 1},
					string = ""
				}
			}

			local text = "To move press arrow keys"

			if Game.currentLevel == 2 then
				text = "To activate button press SHIFT + arrow key"
			end
		
			self.levelTutorial:get("Text").string = text

			self.levelTutorial:get("Transform"):tweenScale({1,1,1}, 8, Ease.inOutQuart)
		end
	end
end


