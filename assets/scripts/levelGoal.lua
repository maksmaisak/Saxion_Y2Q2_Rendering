require('math')
require('assets/scripts/object')
require('assets/scripts/vector')
require('assets/scripts/level/map')
require('assets/scripts/player')

LevelGoal = Object:new()

function LevelGoal:start()

    self.timer = 0
end

function LevelGoal:update(dt)

    self.timer = self.timer + dt
end

function LevelGoal:activateFire()

    self.goal.light.actor:tweenKill()
    self.goal.light.light:tweenIntensity(self.goal.light.initialIntensity, 2, Ease.outExpo)

    Config.audio.levelExitFire.ignition:play()
    Config.audio.levelExitFire.continuous:play()
end

function LevelGoal:deactivateFire()

    self.goal.light.actor:tweenKill()
    self.goal.light.light:tweenIntensity(0, 0.8, Ease.outExpo)

    Config.audio.levelExitFire.ignition:stop()
    Config.audio.levelExitFire.continuous:stop()
end

return function(o)
    return LevelGoal:new(o)
end