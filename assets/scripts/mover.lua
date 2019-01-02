--
-- User: maks
-- Date: 2/1/19
-- Time: 18:25
--

Mover = Object:new()

function Mover:start()
    self.transform = self.gameObject.getComponent("Transform")
end

function Mover:update(dt)
    self.transform.move(0, dt, 0);
end

return Mover

