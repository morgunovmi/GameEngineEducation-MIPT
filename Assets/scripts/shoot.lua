dt = ...
entity = world:GetEntity(entityId)
inputState = inputHandler:GetInputState()
gun = entity:GetGun()
if inputState:Test(InputCommand.Fire) and gun.numRounds > 0 then
    pos = entity:GetPosition()

    b = world:CreateEntity()
    b:IsA(gun.bullet)
    b:SetPosition(pos.x, pos.y, pos.z)
    b:SetVelocity(0.0, 0.0, gun.muzzleSpeed)
    b:AddOctaMesh()

    gun.numRounds = gun.numRounds - 1
end