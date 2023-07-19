modded class SCR_LoadoutManager
{
	override int GetPlayerLoadoutsByFaction(Faction faction, out notnull array<ref SCR_BasePlayerLoadout> outLoadouts)
	{
		outLoadouts.Clear();
		
		if (!m_aPlayerLoadouts)
			return 0;
		
		ArmaReforgerScripted game = GetGame();
		if (!game)
			return 0;
		
		FactionManager factionManager = game.GetFactionManager();
		if (!factionManager)
			return 0;
		
		int outCount = 0;
			
		int count = m_aPlayerLoadouts.Count();
		SCR_BaseGameMode.m_PlayerId_SLC.slc_availableLoadouts = new array<ref string>();
		for (int i = 0; i < count; i++)
		{
			SCR_FactionPlayerLoadout factionLoadout = SCR_FactionPlayerLoadout.Cast(m_aPlayerLoadouts[i]);
			if (factionLoadout)
			{
				Faction ldFaction = factionManager.GetFactionByKey(factionLoadout.m_sAffiliatedFaction);
				if (faction == ldFaction)
				{
					string loadoutStr = "None";
					loadoutStr = factionLoadout.GetLoadoutName();
					if (!SCR_BaseGameMode.SlotIsAvailable(loadoutStr))
						continue;
					
					outLoadouts.Insert(factionLoadout);
					outCount++;
				}
			}
		}
		SCR_BaseGameMode.CountAvailableLoadouts();
		
		return outCount;
	}
	
	//------------------------------------------------------------------------------------------------
	override int GetPlayerLoadouts(out notnull array<SCR_BasePlayerLoadout> outLoadouts)
	{
		protected SCR_RespawnSystemComponent myRespawnSystemComponent;
		int outCount = 0;
		outLoadouts.Clear();
		
		if (!m_aPlayerLoadouts)
			return 0;	
			
		int count = m_aPlayerLoadouts.Count();
		SCR_BaseGameMode.m_PlayerId_SLC.slc_availableLoadouts = new array<ref string>();
		for (int i = 0; i < count; i++)
		{
			string loadoutStr = "None";
			loadoutStr = m_aPlayerLoadouts[i].GetLoadoutName();
			if (!SCR_BaseGameMode.SlotIsAvailable(loadoutStr))
				continue;
			
			outLoadouts.Insert(m_aPlayerLoadouts[i]);
			outCount++;
		}
		SCR_BaseGameMode.CountAvailableLoadouts();
		
		return outCount;
	}
	
	//------------------------------------------------------------------------------------------------
	override int GetRandomLoadoutIndex(Faction faction)
	{
		if (!m_aPlayerLoadouts)
			return -1;	
			
		array<ref SCR_BasePlayerLoadout> loadouts = new array<ref SCR_BasePlayerLoadout>();
		array<int> unavailableLoadouts = new array<int>();
		int count = GetPlayerLoadoutsByFaction(faction, loadouts);
		if (count <= 0)
			return -1;
		
		string loadoutStr = "None";
		for (int i = 0; i < count; i++)
		{
			loadoutStr = m_aPlayerLoadouts[i].GetLoadoutName();
			if (!SCR_BaseGameMode.SlotIsAvailable(loadoutStr))
				continue;
			unavailableLoadouts.Insert(GetLoadoutIndex(m_aPlayerLoadouts[i]));
		}
		
		int randomIndex = Math.RandomInt(0, count);
		for (int j = 0; j < 1; j++)
		{
			if (unavailableLoadouts.Contains(randomIndex))
			{
				randomIndex = Math.RandomInt(0, count);
				j++;
			}
		}
		return randomIndex;
	}

	
	//------------------------------------------------------------------------------------------------
	override int GetRandomLoadoutIndex()
	{
		array<int> unavailableLoadouts = new array<int>();
		if (!m_aPlayerLoadouts)
			return -1;	
			
		int count = m_aPlayerLoadouts.Count();
		if (count <= 0)
			return -1;
		
		string loadoutStr = "None";
		for (int i = 0; i < count; i++)
		{
			loadoutStr = m_aPlayerLoadouts[i].GetLoadoutName();
			if (!SCR_BaseGameMode.SlotIsAvailable(loadoutStr))
				continue;
			unavailableLoadouts.Insert(GetLoadoutIndex(m_aPlayerLoadouts[i]));
		}
		
		int randomIndex = Math.RandomInt(0, count);
		for (int j = 0; j < 1; j++)
		{
			if (unavailableLoadouts.Contains(randomIndex))
			{
				randomIndex = Math.RandomInt(0, count);
				j++;
			}
		}
		return randomIndex;
	}
};