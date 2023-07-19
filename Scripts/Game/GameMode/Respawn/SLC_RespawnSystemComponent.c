modded class SCR_RespawnSystemComponent
{
	static void RemovePlayerRespawnInfo(int playerId)
	{
		SCR_RespawnSystemComponent instance = SCR_RespawnSystemComponent.GetInstance();
		instance.RemovePlayerRespawnInfo(playerId);
	}
};