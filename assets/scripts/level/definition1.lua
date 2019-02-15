require('assets/scripts/level/map')

local map = Map:new { 
	gridSize = {x = 10, y = 10}
}

local obstaclePositions = 
{
	{ x = 1, y = 2},
	{ x = 5, y = 5},
}

local buttonPositions = 
{
	{ x = 3, y = 3}
}

local playerStartPosition = {x = 2, y = 3}

local nextLevelDefinitionPath = 'assets/scripts/scenes/definition2.lua'