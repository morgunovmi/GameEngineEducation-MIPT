dt = ...
speed = 10.0
jumpSpeed = 10.0
eps = 0.1
entity = world:GetEntity(entityId)
inputState = inputHandler:GetInputState()

deltaVel = { x = 0.0, y = 0.0, z = 0.0 }

if inputState:Test(InputCommand.GoLeft) then
    deltaVel.x = deltaVel.x - speed
end
if inputState:Test(InputCommand.GoRight) then
    deltaVel.x = deltaVel.x + speed
end
if inputState:Test(InputCommand.GoForward) then
    deltaVel.z = deltaVel.z + speed
end
if inputState:Test(InputCommand.GoBack) then
    deltaVel.z = deltaVel.z - speed
end

velocity = entity:GetVelocity()
if inputState:Test(InputCommand.Jump) then
    pos = entity:GetPosition()
    plane = entity:GetBouncePlane()
    if plane.x * pos.x + plane.y * pos.y + plane.z * pos.z < plane.w + eps then
        entity:SetVelocity(velocity.x, jumpSpeed, velocity.z)
    end
end

entity:SetVelocity(velocity.x + deltaVel.x * dt, velocity.y + deltaVel.y * dt, velocity.z + deltaVel.z * dt)