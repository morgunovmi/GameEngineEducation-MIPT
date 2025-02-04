dt = ...
entity = world:GetEntity(entityId)
inputState = inputHandler:GetInputState()
gun = entity:GetGun()
if inputState:Test(InputCommand.Fire) and gun.numRounds > 0 then
    soundSystem:StartSound("bruh.mp3", 40.0, false, false)
    pos = entity:GetPosition()

    b = world:CreateEntity()
    b:IsA(world:GetEntityByName(gun.bullet))
    b:SetPosition(pos.x, pos.y, pos.z)
    b:SetVelocity(0.0, 0.0, gun.muzzleSpeed)
    b:AddOctaMesh()

    gun.numRounds = gun.numRounds - 1

    if gun.numRounds == 0 then
        entity:AddReloadTimer(gun.reloadTime)
    end
end