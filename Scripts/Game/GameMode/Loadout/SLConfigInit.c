modded class SCR_BaseGameMode
{
	static ref SquadLimitsStruct m_SquadLoadoutConfig;
	static ref PlayerIDStruct m_PlayerId_SLC;
	static ref SCR_JsonLoadContext configLoadContainer;
	static string m_SquadLoadoutConfigFile = "$profile:SquadLoadoutConfig/SquadLoadoutConfig.json";
	
	bool hasBeenLoaded = false;
	
	[RplProp(onRplName: "UpdateAvailableLoadouts")]
	protected ref array<ref string> availableLoadouts;
	
	[RplProp(onRplName: "UpdateClientId")]
	protected string menuPlayerId;
	
	[RplRpc(RplChannel.Reliable, RplRcver.Server)]
	protected void RpcAsk_Authority_Loadout(array<ref string> newValue)
	{
		if(availableLoadouts == newValue)	return;
		availableLoadouts = newValue;
		Replication.BumpMe();
	}
	
	[RplRpc(RplChannel.Reliable, RplRcver.Server)]
	protected void RpcAsk_Authority_ID(string newValue)
	{
		if(menuPlayerId == newValue)	return;
		menuPlayerId = newValue;
		Replication.BumpMe();
	}
	
	protected void UpdateAvailableLoadouts()
	{
		m_PlayerId_SLC.slc_availableLoadouts = new array<ref string>();
		m_PlayerId_SLC.slc_availableLoadouts = availableLoadouts;
	}
	
	protected void UpdateClientId()
	{
		m_PlayerId_SLC.slc_menuPlayerId = menuPlayerId;
	}
	
	void DoClientLoadoutUpdate()
	{
		availableLoadouts = new array<ref string>();
		availableLoadouts = m_PlayerId_SLC.slc_availableLoadouts;
		Replication.BumpMe();
	}
	
	void DoClientIdUpdate()
	{
		menuPlayerId = m_PlayerId_SLC.slc_menuPlayerId;
		Replication.BumpMe();
	}
	
	void DoClientLoadoutRPCs()
	{
		Rpc(RpcAsk_Authority_Loadout, availableLoadouts);
	}
	
	void DoClientIdRPCs()
	{
		Rpc(RpcAsk_Authority_ID, menuPlayerId);
	}
	
	bool LoadSLConfig()
	{
		configLoadContainer = new SCR_JsonLoadContext();
		if (!FileIO.FileExists(m_SquadLoadoutConfigFile))
		{
			Print("[SLC ERROR] File not found! Creating folder, generating default config...", LogLevel.ERROR);
			if (!FileIO.FileExists("$profile:SquadLoadoutConfig/"))
				FileIO.MakeDirectory("$profile:SquadLoadoutConfig/");
			m_SquadLoadoutConfig = new SquadLimitsStruct();
			m_SquadLoadoutConfig.BuildDefaultSLConfig();
			SaveSLConfig();
		}
		
		configLoadContainer.LoadFromFile( m_SquadLoadoutConfigFile );
		if (!configLoadContainer.LoadFromFile( m_SquadLoadoutConfigFile ))
		{
			Print("[SLConfig ERROR] File not found!", LogLevel.ERROR);
			return false;
		}
		
		if (!configLoadContainer.ReadValue("", m_SquadLoadoutConfig))
		{
			Print("[SLConfig ERROR] Load file failed!", LogLevel.ERROR);
			return false;
		}
		configLoadContainer.ReadValue("version", m_SquadLoadoutConfig.version);
		if (m_SquadLoadoutConfig.version == "0.7")
		{
			Print("[SLC LOADED] Version check PASSED!");
		} else {
			Print("[SLC ERROR] Version check FAILED! Updating version...", LogLevel.ERROR);
			m_SquadLoadoutConfig.UpdateConfig();
			SaveSLConfig();
		}
		configLoadContainer.ReadValue("Class01", m_SquadLoadoutConfig.Class01);
		configLoadContainer.ReadValue("Class02", m_SquadLoadoutConfig.Class02);
		configLoadContainer.ReadValue("Class03", m_SquadLoadoutConfig.Class03);
		configLoadContainer.ReadValue("Class04", m_SquadLoadoutConfig.Class04);
		configLoadContainer.ReadValue("Class05", m_SquadLoadoutConfig.Class05);
		configLoadContainer.ReadValue("Class06", m_SquadLoadoutConfig.Class06);
		configLoadContainer.ReadValue("Class07", m_SquadLoadoutConfig.Class07);
		configLoadContainer.ReadValue("Class08", m_SquadLoadoutConfig.Class08);
		configLoadContainer.ReadValue("Class09", m_SquadLoadoutConfig.Class09);
		configLoadContainer.ReadValue("Class10", m_SquadLoadoutConfig.Class10);
		configLoadContainer.ReadValue("Class11", m_SquadLoadoutConfig.Class11);
		configLoadContainer.ReadValue("Class12", m_SquadLoadoutConfig.Class12);
		configLoadContainer.ReadValue("Class13", m_SquadLoadoutConfig.Class13);
		configLoadContainer.ReadValue("Class14", m_SquadLoadoutConfig.Class14);
		configLoadContainer.ReadValue("Class15", m_SquadLoadoutConfig.Class15);
		configLoadContainer.ReadValue("Class16", m_SquadLoadoutConfig.Class16);
		configLoadContainer.ReadValue("Class17", m_SquadLoadoutConfig.Class17);
		configLoadContainer.ReadValue("Class18", m_SquadLoadoutConfig.Class18);
		configLoadContainer.ReadValue("Class19", m_SquadLoadoutConfig.Class19);
		configLoadContainer.ReadValue("Class20", m_SquadLoadoutConfig.Class20);
		configLoadContainer.ReadValue("Class21", m_SquadLoadoutConfig.Class21);
		configLoadContainer.ReadValue("Class22", m_SquadLoadoutConfig.Class22);
		configLoadContainer.ReadValue("Class23", m_SquadLoadoutConfig.Class23);
		configLoadContainer.ReadValue("Class24", m_SquadLoadoutConfig.Class24);
		configLoadContainer.ReadValue("Class25", m_SquadLoadoutConfig.Class25);
		configLoadContainer.ReadValue("Class26", m_SquadLoadoutConfig.Class26);
		configLoadContainer.ReadValue("Class27", m_SquadLoadoutConfig.Class27);
		configLoadContainer.ReadValue("Class28", m_SquadLoadoutConfig.Class28);
		configLoadContainer.ReadValue("Class29", m_SquadLoadoutConfig.Class29);
		configLoadContainer.ReadValue("Class30", m_SquadLoadoutConfig.Class30);
		configLoadContainer.ReadValue("Class31", m_SquadLoadoutConfig.Class31);
		configLoadContainer.ReadValue("Class32", m_SquadLoadoutConfig.Class32);
		
			Print("[SLC] version = " + m_SquadLoadoutConfig.version);
			if(m_SquadLoadoutConfig.Class01[0] != "")	Print("[SLC] Class01 = " + m_SquadLoadoutConfig.Class01[0] + ", limited to: " + m_SquadLoadoutConfig.Class01[1]);
			if(m_SquadLoadoutConfig.Class02[0] != "")	Print("[SLC] Class02 = " + m_SquadLoadoutConfig.Class02[0] + ", limited to: " + m_SquadLoadoutConfig.Class02[1]);
			if(m_SquadLoadoutConfig.Class03[0] != "")	Print("[SLC] Class03 = " + m_SquadLoadoutConfig.Class03[0] + ", limited to: " + m_SquadLoadoutConfig.Class03[1]);
			if(m_SquadLoadoutConfig.Class04[0] != "")	Print("[SLC] Class04 = " + m_SquadLoadoutConfig.Class04[0] + ", limited to: " + m_SquadLoadoutConfig.Class04[1]);
			if(m_SquadLoadoutConfig.Class05[0] != "")	Print("[SLC] Class05 = " + m_SquadLoadoutConfig.Class05[0] + ", limited to: " + m_SquadLoadoutConfig.Class05[1]);
			if(m_SquadLoadoutConfig.Class06[0] != "")	Print("[SLC] Class06 = " + m_SquadLoadoutConfig.Class06[0] + ", limited to: " + m_SquadLoadoutConfig.Class06[1]);
			if(m_SquadLoadoutConfig.Class07[0] != "")	Print("[SLC] Class07 = " + m_SquadLoadoutConfig.Class07[0] + ", limited to: " + m_SquadLoadoutConfig.Class07[1]);
			if(m_SquadLoadoutConfig.Class08[0] != "")	Print("[SLC] Class08 = " + m_SquadLoadoutConfig.Class08[0] + ", limited to: " + m_SquadLoadoutConfig.Class08[1]);
			if(m_SquadLoadoutConfig.Class09[0] != "")	Print("[SLC] Class09 = " + m_SquadLoadoutConfig.Class09[0] + ", limited to: " + m_SquadLoadoutConfig.Class09[1]);
			if(m_SquadLoadoutConfig.Class10[0] != "")	Print("[SLC] Class10 = " + m_SquadLoadoutConfig.Class10[0] + ", limited to: " + m_SquadLoadoutConfig.Class10[1]);
			if(m_SquadLoadoutConfig.Class11[0] != "")	Print("[SLC] Class11 = " + m_SquadLoadoutConfig.Class11[0] + ", limited to: " + m_SquadLoadoutConfig.Class11[1]);
			if(m_SquadLoadoutConfig.Class12[0] != "")	Print("[SLC] Class12 = " + m_SquadLoadoutConfig.Class12[0] + ", limited to: " + m_SquadLoadoutConfig.Class12[1]);
			if(m_SquadLoadoutConfig.Class13[0] != "")	Print("[SLC] Class13 = " + m_SquadLoadoutConfig.Class13[0] + ", limited to: " + m_SquadLoadoutConfig.Class13[1]);
			if(m_SquadLoadoutConfig.Class14[0] != "")	Print("[SLC] Class14 = " + m_SquadLoadoutConfig.Class14[0] + ", limited to: " + m_SquadLoadoutConfig.Class14[1]);
			if(m_SquadLoadoutConfig.Class15[0] != "")	Print("[SLC] Class15 = " + m_SquadLoadoutConfig.Class15[0] + ", limited to: " + m_SquadLoadoutConfig.Class15[1]);
			if(m_SquadLoadoutConfig.Class16[0] != "")	Print("[SLC] Class16 = " + m_SquadLoadoutConfig.Class16[0] + ", limited to: " + m_SquadLoadoutConfig.Class16[1]);
			if(m_SquadLoadoutConfig.Class17[0] != "")	Print("[SLC] Class17 = " + m_SquadLoadoutConfig.Class17[0] + ", limited to: " + m_SquadLoadoutConfig.Class17[1]);
			if(m_SquadLoadoutConfig.Class18[0] != "")	Print("[SLC] Class18 = " + m_SquadLoadoutConfig.Class18[0] + ", limited to: " + m_SquadLoadoutConfig.Class18[1]);
			if(m_SquadLoadoutConfig.Class19[0] != "")	Print("[SLC] Class19 = " + m_SquadLoadoutConfig.Class19[0] + ", limited to: " + m_SquadLoadoutConfig.Class19[1]);
			if(m_SquadLoadoutConfig.Class20[0] != "")	Print("[SLC] Class20 = " + m_SquadLoadoutConfig.Class20[0] + ", limited to: " + m_SquadLoadoutConfig.Class20[1]);
			if(m_SquadLoadoutConfig.Class21[0] != "")	Print("[SLC] Class21 = " + m_SquadLoadoutConfig.Class21[0] + ", limited to: " + m_SquadLoadoutConfig.Class21[1]);
			if(m_SquadLoadoutConfig.Class22[0] != "")	Print("[SLC] Class22 = " + m_SquadLoadoutConfig.Class22[0] + ", limited to: " + m_SquadLoadoutConfig.Class22[1]);
			if(m_SquadLoadoutConfig.Class23[0] != "")	Print("[SLC] Class23 = " + m_SquadLoadoutConfig.Class23[0] + ", limited to: " + m_SquadLoadoutConfig.Class23[1]);
			if(m_SquadLoadoutConfig.Class24[0] != "")	Print("[SLC] Class24 = " + m_SquadLoadoutConfig.Class24[0] + ", limited to: " + m_SquadLoadoutConfig.Class24[1]);
			if(m_SquadLoadoutConfig.Class25[0] != "")	Print("[SLC] Class25 = " + m_SquadLoadoutConfig.Class25[0] + ", limited to: " + m_SquadLoadoutConfig.Class25[1]);
			if(m_SquadLoadoutConfig.Class26[0] != "")	Print("[SLC] Class26 = " + m_SquadLoadoutConfig.Class26[0] + ", limited to: " + m_SquadLoadoutConfig.Class26[1]);
			if(m_SquadLoadoutConfig.Class27[0] != "")	Print("[SLC] Class27 = " + m_SquadLoadoutConfig.Class27[0] + ", limited to: " + m_SquadLoadoutConfig.Class27[1]);
			if(m_SquadLoadoutConfig.Class28[0] != "")	Print("[SLC] Class28 = " + m_SquadLoadoutConfig.Class28[0] + ", limited to: " + m_SquadLoadoutConfig.Class28[1]);
			if(m_SquadLoadoutConfig.Class29[0] != "")	Print("[SLC] Class29 = " + m_SquadLoadoutConfig.Class29[0] + ", limited to: " + m_SquadLoadoutConfig.Class29[1]);
			if(m_SquadLoadoutConfig.Class30[0] != "")	Print("[SLC] Class30 = " + m_SquadLoadoutConfig.Class30[0] + ", limited to: " + m_SquadLoadoutConfig.Class30[1]);
			if(m_SquadLoadoutConfig.Class31[0] != "")	Print("[SLC] Class31 = " + m_SquadLoadoutConfig.Class31[0] + ", limited to: " + m_SquadLoadoutConfig.Class31[1]);
			if(m_SquadLoadoutConfig.Class32[0] != "")	Print("[SLC] Class32 = " + m_SquadLoadoutConfig.Class32[0] + ", limited to: " + m_SquadLoadoutConfig.Class32[1]);
			
				
		SCR_BaseGameMode instance = SCR_BaseGameMode.Cast(GetGame().GetGameMode());
		if (!instance)	return false;
				
		return true;
	}
	
	bool SaveSLConfig()
	{
		SCR_JsonSaveContext configSaveContainer = new SCR_JsonSaveContext();
				
		configSaveContainer.WriteValue("version", m_SquadLoadoutConfig.version);
		configSaveContainer.WriteValue("Class01", m_SquadLoadoutConfig.Class01);
		configSaveContainer.WriteValue("Class02", m_SquadLoadoutConfig.Class02);
		configSaveContainer.WriteValue("Class03", m_SquadLoadoutConfig.Class03);
		configSaveContainer.WriteValue("Class04", m_SquadLoadoutConfig.Class04);
		configSaveContainer.WriteValue("Class05", m_SquadLoadoutConfig.Class05);
		configSaveContainer.WriteValue("Class06", m_SquadLoadoutConfig.Class06);
		configSaveContainer.WriteValue("Class07", m_SquadLoadoutConfig.Class07);
		configSaveContainer.WriteValue("Class08", m_SquadLoadoutConfig.Class08);
		configSaveContainer.WriteValue("Class09", m_SquadLoadoutConfig.Class09);
		configSaveContainer.WriteValue("Class10", m_SquadLoadoutConfig.Class10);
		configSaveContainer.WriteValue("Class11", m_SquadLoadoutConfig.Class11);
		configSaveContainer.WriteValue("Class12", m_SquadLoadoutConfig.Class12);
		configSaveContainer.WriteValue("Class13", m_SquadLoadoutConfig.Class13);
		configSaveContainer.WriteValue("Class14", m_SquadLoadoutConfig.Class14);
		configSaveContainer.WriteValue("Class15", m_SquadLoadoutConfig.Class15);
		configSaveContainer.WriteValue("Class16", m_SquadLoadoutConfig.Class16);
		configSaveContainer.WriteValue("Class17", m_SquadLoadoutConfig.Class17);
		configSaveContainer.WriteValue("Class18", m_SquadLoadoutConfig.Class18);
		configSaveContainer.WriteValue("Class19", m_SquadLoadoutConfig.Class19);
		configSaveContainer.WriteValue("Class20", m_SquadLoadoutConfig.Class20);
		configSaveContainer.WriteValue("Class21", m_SquadLoadoutConfig.Class21);
		configSaveContainer.WriteValue("Class22", m_SquadLoadoutConfig.Class22);
		configSaveContainer.WriteValue("Class23", m_SquadLoadoutConfig.Class23);
		configSaveContainer.WriteValue("Class24", m_SquadLoadoutConfig.Class24);
		configSaveContainer.WriteValue("Class25", m_SquadLoadoutConfig.Class25);
		configSaveContainer.WriteValue("Class26", m_SquadLoadoutConfig.Class26);
		configSaveContainer.WriteValue("Class27", m_SquadLoadoutConfig.Class27);
		configSaveContainer.WriteValue("Class28", m_SquadLoadoutConfig.Class28);
		configSaveContainer.WriteValue("Class29", m_SquadLoadoutConfig.Class29);
		configSaveContainer.WriteValue("Class30", m_SquadLoadoutConfig.Class30);
		configSaveContainer.WriteValue("Class31", m_SquadLoadoutConfig.Class31);
		configSaveContainer.WriteValue("Class32", m_SquadLoadoutConfig.Class32);
		
		configSaveContainer.SaveToFile(m_SquadLoadoutConfigFile);
		if (!configSaveContainer.SaveToFile( m_SquadLoadoutConfigFile ))	return false;
		
		return true;
	}
	//------------------------------------------------------------------------------------------------
	
	static bool SlotIsAvailable(string slotName)
	{
		SCR_BaseGameMode instance = SCR_BaseGameMode.Cast(GetGame().GetGameMode());
		
		Print("[SLC] searching for Whitelisted Slot "+slotName+" for ID: "+m_PlayerId_SLC.slc_menuPlayerId);
		if(Replication.IsServer()){	
			m_PlayerId_SLC.slc_menuPlayerId = instance.menuPlayerId;
			Print("[SLC server] searching for Whitelisted Slot "+slotName+" for ID: "+m_PlayerId_SLC.slc_menuPlayerId);
			if (slotName == SCR_BaseGameMode.m_SquadLoadoutConfig.Class01[0]){
				if(SCR_BaseGameMode.m_SquadLoadoutConfig.Class01.Contains(m_PlayerId_SLC.slc_menuPlayerId)){
					Print("[SLC] Found Whitelisted Slot "+slotName+" for ID: "+m_PlayerId_SLC.slc_menuPlayerId);
					m_PlayerId_SLC.slc_availableLoadouts.Insert(slotName);
					return true;
				}
			}
			if (slotName == SCR_BaseGameMode.m_SquadLoadoutConfig.Class02[0]){
				if(SCR_BaseGameMode.m_SquadLoadoutConfig.Class02.Contains(m_PlayerId_SLC.slc_menuPlayerId)){
					Print("[SLC] Found Whitelisted Slot "+slotName+" for ID: "+m_PlayerId_SLC.slc_menuPlayerId);
					m_PlayerId_SLC.slc_availableLoadouts.Insert(slotName);
					return true;
				}
			}
			if (slotName == SCR_BaseGameMode.m_SquadLoadoutConfig.Class03[0]){
				if(SCR_BaseGameMode.m_SquadLoadoutConfig.Class03.Contains(m_PlayerId_SLC.slc_menuPlayerId)){
					Print("[SLC] Found Whitelisted Slot "+slotName+" for ID: "+m_PlayerId_SLC.slc_menuPlayerId);
					m_PlayerId_SLC.slc_availableLoadouts.Insert(slotName);
					return true;
				}
			}
			if (slotName == SCR_BaseGameMode.m_SquadLoadoutConfig.Class04[0]){
				if(SCR_BaseGameMode.m_SquadLoadoutConfig.Class04.Contains(m_PlayerId_SLC.slc_menuPlayerId)){
					Print("[SLC] Found Whitelisted Slot "+slotName+" for ID: "+m_PlayerId_SLC.slc_menuPlayerId);
					m_PlayerId_SLC.slc_availableLoadouts.Insert(slotName);
					return true;
				}
			}
			if (slotName == SCR_BaseGameMode.m_SquadLoadoutConfig.Class05[0]){
				Print("[SLC] slot "+slotName+" found!");
				if(SCR_BaseGameMode.m_SquadLoadoutConfig.Class05.Contains(m_PlayerId_SLC.slc_menuPlayerId)){
					Print("[SLC] Found Whitelisted Slot "+slotName+" for ID: "+m_PlayerId_SLC.slc_menuPlayerId);
					m_PlayerId_SLC.slc_availableLoadouts.Insert(slotName);
					return true;
				}
			}
			if (slotName == SCR_BaseGameMode.m_SquadLoadoutConfig.Class06[0]){
				if(SCR_BaseGameMode.m_SquadLoadoutConfig.Class06.Contains(m_PlayerId_SLC.slc_menuPlayerId)){
					Print("[SLC] Found Whitelisted Slot "+slotName+" for ID: "+m_PlayerId_SLC.slc_menuPlayerId);
					m_PlayerId_SLC.slc_availableLoadouts.Insert(slotName);
					return true;
				}
			}
			if (slotName == SCR_BaseGameMode.m_SquadLoadoutConfig.Class07[0]){
				if(SCR_BaseGameMode.m_SquadLoadoutConfig.Class07.Contains(m_PlayerId_SLC.slc_menuPlayerId)){
					Print("[SLC] Found Whitelisted Slot "+slotName+" for ID: "+m_PlayerId_SLC.slc_menuPlayerId);
					m_PlayerId_SLC.slc_availableLoadouts.Insert(slotName);
					return true;
				}
			}
			if (slotName == SCR_BaseGameMode.m_SquadLoadoutConfig.Class08[0]){
				if(SCR_BaseGameMode.m_SquadLoadoutConfig.Class08.Contains(m_PlayerId_SLC.slc_menuPlayerId)){
					Print("[SLC] Found Whitelisted Slot "+slotName+" for ID: "+m_PlayerId_SLC.slc_menuPlayerId);
					m_PlayerId_SLC.slc_availableLoadouts.Insert(slotName);
					return true;
				}
			}
			if (slotName == SCR_BaseGameMode.m_SquadLoadoutConfig.Class09[0]){
				if(SCR_BaseGameMode.m_SquadLoadoutConfig.Class09.Contains(m_PlayerId_SLC.slc_menuPlayerId)){
					Print("[SLC] Found Whitelisted Slot "+slotName+" for ID: "+m_PlayerId_SLC.slc_menuPlayerId);
					m_PlayerId_SLC.slc_availableLoadouts.Insert(slotName);
					return true;
				}
			}
			if (slotName == SCR_BaseGameMode.m_SquadLoadoutConfig.Class10[0]){
				if(SCR_BaseGameMode.m_SquadLoadoutConfig.Class10.Contains(m_PlayerId_SLC.slc_menuPlayerId)){
					Print("[SLC] Found Whitelisted Slot "+slotName+" for ID: "+m_PlayerId_SLC.slc_menuPlayerId);
					m_PlayerId_SLC.slc_availableLoadouts.Insert(slotName);
					return true;
				}
			}
			if (slotName == SCR_BaseGameMode.m_SquadLoadoutConfig.Class11[0]){
				if(SCR_BaseGameMode.m_SquadLoadoutConfig.Class11.Contains(m_PlayerId_SLC.slc_menuPlayerId)){
					Print("[SLC] Found Whitelisted Slot "+slotName+" for ID: "+m_PlayerId_SLC.slc_menuPlayerId);
					m_PlayerId_SLC.slc_availableLoadouts.Insert(slotName);
					return true;
				}
			}
			if (slotName == SCR_BaseGameMode.m_SquadLoadoutConfig.Class12[0]){
				if(SCR_BaseGameMode.m_SquadLoadoutConfig.Class12.Contains(m_PlayerId_SLC.slc_menuPlayerId)){
					Print("[SLC] Found Whitelisted Slot "+slotName+" for ID: "+m_PlayerId_SLC.slc_menuPlayerId);
					m_PlayerId_SLC.slc_availableLoadouts.Insert(slotName);
					return true;
				}
			}
			if (slotName == SCR_BaseGameMode.m_SquadLoadoutConfig.Class13[0]){
				if(SCR_BaseGameMode.m_SquadLoadoutConfig.Class13.Contains(m_PlayerId_SLC.slc_menuPlayerId)){
					Print("[SLC] Found Whitelisted Slot "+slotName+" for ID: "+m_PlayerId_SLC.slc_menuPlayerId);
					m_PlayerId_SLC.slc_availableLoadouts.Insert(slotName);
					return true;
				}
			}
			if (slotName == SCR_BaseGameMode.m_SquadLoadoutConfig.Class14[0]){
				if(SCR_BaseGameMode.m_SquadLoadoutConfig.Class14.Contains(m_PlayerId_SLC.slc_menuPlayerId)){
					Print("[SLC] Found Whitelisted Slot "+slotName+" for ID: "+m_PlayerId_SLC.slc_menuPlayerId);
					m_PlayerId_SLC.slc_availableLoadouts.Insert(slotName);
					return true;
				}
			}
			if (slotName == SCR_BaseGameMode.m_SquadLoadoutConfig.Class15[0]){
				if(SCR_BaseGameMode.m_SquadLoadoutConfig.Class15.Contains(m_PlayerId_SLC.slc_menuPlayerId)){
					Print("[SLC] Found Whitelisted Slot "+slotName+" for ID: "+m_PlayerId_SLC.slc_menuPlayerId);
					m_PlayerId_SLC.slc_availableLoadouts.Insert(slotName);
					return true;
				}
			}
			if (slotName == SCR_BaseGameMode.m_SquadLoadoutConfig.Class16[0]){
				if(SCR_BaseGameMode.m_SquadLoadoutConfig.Class16.Contains(m_PlayerId_SLC.slc_menuPlayerId)){
					Print("[SLC] Found Whitelisted Slot "+slotName+" for ID: "+m_PlayerId_SLC.slc_menuPlayerId);
					m_PlayerId_SLC.slc_availableLoadouts.Insert(slotName);
					return true;
				}
			}
			if (slotName == SCR_BaseGameMode.m_SquadLoadoutConfig.Class17[0]){
				if(SCR_BaseGameMode.m_SquadLoadoutConfig.Class17.Contains(m_PlayerId_SLC.slc_menuPlayerId)){
					Print("[SLC] Found Whitelisted Slot "+slotName+" for ID: "+m_PlayerId_SLC.slc_menuPlayerId);
					m_PlayerId_SLC.slc_availableLoadouts.Insert(slotName);
					return true;
				}
			}
			if (slotName == SCR_BaseGameMode.m_SquadLoadoutConfig.Class18[0]){
				if(SCR_BaseGameMode.m_SquadLoadoutConfig.Class18.Contains(m_PlayerId_SLC.slc_menuPlayerId)){
					Print("[SLC] Found Whitelisted Slot "+slotName+" for ID: "+m_PlayerId_SLC.slc_menuPlayerId);
					m_PlayerId_SLC.slc_availableLoadouts.Insert(slotName);
					return true;
				}
			}
			if (slotName == SCR_BaseGameMode.m_SquadLoadoutConfig.Class19[0]){
				if(SCR_BaseGameMode.m_SquadLoadoutConfig.Class19.Contains(m_PlayerId_SLC.slc_menuPlayerId)){
					Print("[SLC] Found Whitelisted Slot "+slotName+" for ID: "+m_PlayerId_SLC.slc_menuPlayerId);
					m_PlayerId_SLC.slc_availableLoadouts.Insert(slotName);
					return true;
				}
			}
			if (slotName == SCR_BaseGameMode.m_SquadLoadoutConfig.Class20[0]){
				if(SCR_BaseGameMode.m_SquadLoadoutConfig.Class20.Contains(m_PlayerId_SLC.slc_menuPlayerId)){
					Print("[SLC] Found Whitelisted Slot "+slotName+" for ID: "+m_PlayerId_SLC.slc_menuPlayerId);
					m_PlayerId_SLC.slc_availableLoadouts.Insert(slotName);
					return true;
				}
			}
			if (slotName == SCR_BaseGameMode.m_SquadLoadoutConfig.Class21[0]){
				if(SCR_BaseGameMode.m_SquadLoadoutConfig.Class21.Contains(m_PlayerId_SLC.slc_menuPlayerId)){
					Print("[SLC] Found Whitelisted Slot "+slotName+" for ID: "+m_PlayerId_SLC.slc_menuPlayerId);
					m_PlayerId_SLC.slc_availableLoadouts.Insert(slotName);
					return true;
				}
			}
			if (slotName == SCR_BaseGameMode.m_SquadLoadoutConfig.Class22[0]){
				if(SCR_BaseGameMode.m_SquadLoadoutConfig.Class22.Contains(m_PlayerId_SLC.slc_menuPlayerId)){
					Print("[SLC] Found Whitelisted Slot "+slotName+" for ID: "+m_PlayerId_SLC.slc_menuPlayerId);
					m_PlayerId_SLC.slc_availableLoadouts.Insert(slotName);
					return true;
				}
			}
			if (slotName == SCR_BaseGameMode.m_SquadLoadoutConfig.Class23[0]){
				if(SCR_BaseGameMode.m_SquadLoadoutConfig.Class23.Contains(m_PlayerId_SLC.slc_menuPlayerId)){
					Print("[SLC] Found Whitelisted Slot "+slotName+" for ID: "+m_PlayerId_SLC.slc_menuPlayerId);
					m_PlayerId_SLC.slc_availableLoadouts.Insert(slotName);
					return true;
				}
			}
			if (slotName == SCR_BaseGameMode.m_SquadLoadoutConfig.Class24[0]){
				if(SCR_BaseGameMode.m_SquadLoadoutConfig.Class24.Contains(m_PlayerId_SLC.slc_menuPlayerId)){
					Print("[SLC] Found Whitelisted Slot "+slotName+" for ID: "+m_PlayerId_SLC.slc_menuPlayerId);
					m_PlayerId_SLC.slc_availableLoadouts.Insert(slotName);
					return true;
				}
			}
			if (slotName == SCR_BaseGameMode.m_SquadLoadoutConfig.Class25[0]){
				if(SCR_BaseGameMode.m_SquadLoadoutConfig.Class25.Contains(m_PlayerId_SLC.slc_menuPlayerId)){
					Print("[SLC] Found Whitelisted Slot "+slotName+" for ID: "+m_PlayerId_SLC.slc_menuPlayerId);
					m_PlayerId_SLC.slc_availableLoadouts.Insert(slotName);
					return true;
				}
			}
			if (slotName == SCR_BaseGameMode.m_SquadLoadoutConfig.Class26[0]){
				if(SCR_BaseGameMode.m_SquadLoadoutConfig.Class26.Contains(m_PlayerId_SLC.slc_menuPlayerId)){
					Print("[SLC] Found Whitelisted Slot "+slotName+" for ID: "+m_PlayerId_SLC.slc_menuPlayerId);
					m_PlayerId_SLC.slc_availableLoadouts.Insert(slotName);
					return true;
				}
			}
			if (slotName == SCR_BaseGameMode.m_SquadLoadoutConfig.Class27[0]){
				if(SCR_BaseGameMode.m_SquadLoadoutConfig.Class27.Contains(m_PlayerId_SLC.slc_menuPlayerId)){
					Print("[SLC] Found Whitelisted Slot "+slotName+" for ID: "+m_PlayerId_SLC.slc_menuPlayerId);
					m_PlayerId_SLC.slc_availableLoadouts.Insert(slotName);
					return true;
				}
			}
			if (slotName == SCR_BaseGameMode.m_SquadLoadoutConfig.Class28[0]){
				if(SCR_BaseGameMode.m_SquadLoadoutConfig.Class28.Contains(m_PlayerId_SLC.slc_menuPlayerId)){
					Print("[SLC] Found Whitelisted Slot "+slotName+" for ID: "+m_PlayerId_SLC.slc_menuPlayerId);
					m_PlayerId_SLC.slc_availableLoadouts.Insert(slotName);
					return true;
				}
			}
			if (slotName == SCR_BaseGameMode.m_SquadLoadoutConfig.Class29[0]){
				if(SCR_BaseGameMode.m_SquadLoadoutConfig.Class29.Contains(m_PlayerId_SLC.slc_menuPlayerId)){
					Print("[SLC] Found Whitelisted Slot "+slotName+" for ID: "+m_PlayerId_SLC.slc_menuPlayerId);
					m_PlayerId_SLC.slc_availableLoadouts.Insert(slotName);
					return true;
				}
			}
			if (slotName == SCR_BaseGameMode.m_SquadLoadoutConfig.Class30[0]){
				if(SCR_BaseGameMode.m_SquadLoadoutConfig.Class30.Contains(m_PlayerId_SLC.slc_menuPlayerId)){
					Print("[SLC] Found Whitelisted Slot "+slotName+" for ID: "+m_PlayerId_SLC.slc_menuPlayerId);
					m_PlayerId_SLC.slc_availableLoadouts.Insert(slotName);
					return true;
				}
			}
			if (slotName == SCR_BaseGameMode.m_SquadLoadoutConfig.Class31[0]){
				if(SCR_BaseGameMode.m_SquadLoadoutConfig.Class31.Contains(m_PlayerId_SLC.slc_menuPlayerId)){
					Print("[SLC] Found Whitelisted Slot "+slotName+" for ID: "+m_PlayerId_SLC.slc_menuPlayerId);
					m_PlayerId_SLC.slc_availableLoadouts.Insert(slotName);
					return true;
				}
			}
			if (slotName == SCR_BaseGameMode.m_SquadLoadoutConfig.Class32[0]){
				if(SCR_BaseGameMode.m_SquadLoadoutConfig.Class32.Contains(m_PlayerId_SLC.slc_menuPlayerId)){
					Print("[SLC] Found Whitelisted Slot "+slotName+" for ID: "+m_PlayerId_SLC.slc_menuPlayerId);
					m_PlayerId_SLC.slc_availableLoadouts.Insert(slotName);
					return true;
				}
			}
		
			protected SCR_RespawnSystemComponent myRespawnSystemComponent = SCR_RespawnSystemComponent.GetInstance();
			array<int> players = {};
			PlayerManager pm = GetGame().GetPlayerManager();
			pm.GetAllPlayers(players);
			int C01Slots, C02Slots, C03Slots, C04Slots, C05Slots, C06Slots, C07Slots, C08Slots, C09Slots, C10Slots, C11Slots, C12Slots, C13Slots, C14Slots, C15Slots, C16Slots, C17Slots, C18Slots, C19Slots, C20Slots, C21Slots, C22Slots, C23Slots, C24Slots, C25Slots, C26Slots, C27Slots, C28Slots, C29Slots, C30Slots, C31Slots, C32Slots;
			
			foreach (int playerId : players)
			{
				if (myRespawnSystemComponent)
				{
					ArmaReforgerScripted game = GetGame();
					if (!game)	return 0;
					FactionManager factionManager = game.GetFactionManager();
					string loadoutStr = "None";
					if (factionManager)
					{
						SCR_FactionPlayerLoadout loadoutFaction = SCR_FactionPlayerLoadout.Cast(SCR_LoadoutManager.SGetPlayerLoadout(playerId));
						if (loadoutFaction)	loadoutStr = loadoutFaction.GetLoadoutName();
					} else {
						SCR_BasePlayerLoadout loadout = SCR_LoadoutManager.SGetPlayerLoadout(playerId);
						if (loadout)	loadoutStr = loadout.GetLoadoutName();
					}
					if (loadoutStr == SCR_BaseGameMode.m_SquadLoadoutConfig.Class01[0])	C01Slots++;
					if (loadoutStr == SCR_BaseGameMode.m_SquadLoadoutConfig.Class02[0])	C02Slots++;
					if (loadoutStr == SCR_BaseGameMode.m_SquadLoadoutConfig.Class03[0])	C03Slots++;
					if (loadoutStr == SCR_BaseGameMode.m_SquadLoadoutConfig.Class04[0])	C04Slots++;
					if (loadoutStr == SCR_BaseGameMode.m_SquadLoadoutConfig.Class05[0])	C05Slots++;
					if (loadoutStr == SCR_BaseGameMode.m_SquadLoadoutConfig.Class06[0])	C06Slots++;
					if (loadoutStr == SCR_BaseGameMode.m_SquadLoadoutConfig.Class07[0])	C07Slots++;
					if (loadoutStr == SCR_BaseGameMode.m_SquadLoadoutConfig.Class08[0])	C08Slots++;
					if (loadoutStr == SCR_BaseGameMode.m_SquadLoadoutConfig.Class09[0])	C09Slots++;
					if (loadoutStr == SCR_BaseGameMode.m_SquadLoadoutConfig.Class10[0])	C10Slots++;
					if (loadoutStr == SCR_BaseGameMode.m_SquadLoadoutConfig.Class11[0])	C11Slots++;
					if (loadoutStr == SCR_BaseGameMode.m_SquadLoadoutConfig.Class12[0])	C12Slots++;
					if (loadoutStr == SCR_BaseGameMode.m_SquadLoadoutConfig.Class13[0])	C13Slots++;
					if (loadoutStr == SCR_BaseGameMode.m_SquadLoadoutConfig.Class14[0])	C14Slots++;
					if (loadoutStr == SCR_BaseGameMode.m_SquadLoadoutConfig.Class15[0])	C15Slots++;
					if (loadoutStr == SCR_BaseGameMode.m_SquadLoadoutConfig.Class16[0])	C16Slots++;
					if (loadoutStr == SCR_BaseGameMode.m_SquadLoadoutConfig.Class17[0])	C17Slots++;
					if (loadoutStr == SCR_BaseGameMode.m_SquadLoadoutConfig.Class18[0])	C18Slots++;
					if (loadoutStr == SCR_BaseGameMode.m_SquadLoadoutConfig.Class19[0])	C19Slots++;
					if (loadoutStr == SCR_BaseGameMode.m_SquadLoadoutConfig.Class20[0])	C20Slots++;
					if (loadoutStr == SCR_BaseGameMode.m_SquadLoadoutConfig.Class21[0])	C21Slots++;
					if (loadoutStr == SCR_BaseGameMode.m_SquadLoadoutConfig.Class22[0])	C22Slots++;
					if (loadoutStr == SCR_BaseGameMode.m_SquadLoadoutConfig.Class23[0])	C23Slots++;
					if (loadoutStr == SCR_BaseGameMode.m_SquadLoadoutConfig.Class24[0])	C24Slots++;
					if (loadoutStr == SCR_BaseGameMode.m_SquadLoadoutConfig.Class25[0])	C25Slots++;
					if (loadoutStr == SCR_BaseGameMode.m_SquadLoadoutConfig.Class26[0])	C26Slots++;
					if (loadoutStr == SCR_BaseGameMode.m_SquadLoadoutConfig.Class27[0])	C27Slots++;
					if (loadoutStr == SCR_BaseGameMode.m_SquadLoadoutConfig.Class28[0])	C28Slots++;
					if (loadoutStr == SCR_BaseGameMode.m_SquadLoadoutConfig.Class29[0])	C29Slots++;
					if (loadoutStr == SCR_BaseGameMode.m_SquadLoadoutConfig.Class30[0])	C30Slots++;
					if (loadoutStr == SCR_BaseGameMode.m_SquadLoadoutConfig.Class31[0])	C31Slots++;
					if (loadoutStr == SCR_BaseGameMode.m_SquadLoadoutConfig.Class32[0])	C32Slots++;
				}
			}

			// Squad Loadouts Limits-----------------------------------------------------------------------
			if (SCR_BaseGameMode.m_SquadLoadoutConfig.Class01[0] != "" && slotName == SCR_BaseGameMode.m_SquadLoadoutConfig.Class01[0] && C01Slots >= SCR_BaseGameMode.m_SquadLoadoutConfig.Class01[1].ToInt())	return false;
			if (SCR_BaseGameMode.m_SquadLoadoutConfig.Class02[0] != "" && slotName == SCR_BaseGameMode.m_SquadLoadoutConfig.Class02[0] && C02Slots >= SCR_BaseGameMode.m_SquadLoadoutConfig.Class02[1].ToInt())	return false;
			if (SCR_BaseGameMode.m_SquadLoadoutConfig.Class03[0] != "" && slotName == SCR_BaseGameMode.m_SquadLoadoutConfig.Class03[0] && C03Slots >= SCR_BaseGameMode.m_SquadLoadoutConfig.Class03[1].ToInt())	return false;
			if (SCR_BaseGameMode.m_SquadLoadoutConfig.Class04[0] != "" && slotName == SCR_BaseGameMode.m_SquadLoadoutConfig.Class04[0] && C04Slots >= SCR_BaseGameMode.m_SquadLoadoutConfig.Class04[1].ToInt())	return false;
			if (SCR_BaseGameMode.m_SquadLoadoutConfig.Class05[0] != "" && slotName == SCR_BaseGameMode.m_SquadLoadoutConfig.Class05[0] && C05Slots >= SCR_BaseGameMode.m_SquadLoadoutConfig.Class05[1].ToInt())	return false;
			if (SCR_BaseGameMode.m_SquadLoadoutConfig.Class06[0] != "" && slotName == SCR_BaseGameMode.m_SquadLoadoutConfig.Class06[0] && C06Slots >= SCR_BaseGameMode.m_SquadLoadoutConfig.Class06[1].ToInt())	return false;
			if (SCR_BaseGameMode.m_SquadLoadoutConfig.Class07[0] != "" && slotName == SCR_BaseGameMode.m_SquadLoadoutConfig.Class07[0] && C07Slots >= SCR_BaseGameMode.m_SquadLoadoutConfig.Class07[1].ToInt())	return false;
			if (SCR_BaseGameMode.m_SquadLoadoutConfig.Class08[0] != "" && slotName == SCR_BaseGameMode.m_SquadLoadoutConfig.Class08[0] && C08Slots >= SCR_BaseGameMode.m_SquadLoadoutConfig.Class08[1].ToInt())	return false;
			if (SCR_BaseGameMode.m_SquadLoadoutConfig.Class09[0] != "" && slotName == SCR_BaseGameMode.m_SquadLoadoutConfig.Class09[0] && C09Slots >= SCR_BaseGameMode.m_SquadLoadoutConfig.Class09[1].ToInt())	return false;
			if (SCR_BaseGameMode.m_SquadLoadoutConfig.Class10[0] != "" && slotName == SCR_BaseGameMode.m_SquadLoadoutConfig.Class10[0] && C10Slots >= SCR_BaseGameMode.m_SquadLoadoutConfig.Class10[1].ToInt())	return false;
			if (SCR_BaseGameMode.m_SquadLoadoutConfig.Class11[0] != "" && slotName == SCR_BaseGameMode.m_SquadLoadoutConfig.Class11[0] && C11Slots >= SCR_BaseGameMode.m_SquadLoadoutConfig.Class11[1].ToInt())	return false;
			if (SCR_BaseGameMode.m_SquadLoadoutConfig.Class12[0] != "" && slotName == SCR_BaseGameMode.m_SquadLoadoutConfig.Class12[0] && C12Slots >= SCR_BaseGameMode.m_SquadLoadoutConfig.Class12[1].ToInt())	return false;
			if (SCR_BaseGameMode.m_SquadLoadoutConfig.Class13[0] != "" && slotName == SCR_BaseGameMode.m_SquadLoadoutConfig.Class13[0] && C13Slots >= SCR_BaseGameMode.m_SquadLoadoutConfig.Class13[1].ToInt())	return false;
			if (SCR_BaseGameMode.m_SquadLoadoutConfig.Class14[0] != "" && slotName == SCR_BaseGameMode.m_SquadLoadoutConfig.Class14[0] && C14Slots >= SCR_BaseGameMode.m_SquadLoadoutConfig.Class14[1].ToInt())	return false;
			if (SCR_BaseGameMode.m_SquadLoadoutConfig.Class15[0] != "" && slotName == SCR_BaseGameMode.m_SquadLoadoutConfig.Class15[0] && C15Slots >= SCR_BaseGameMode.m_SquadLoadoutConfig.Class15[1].ToInt())	return false;
			if (SCR_BaseGameMode.m_SquadLoadoutConfig.Class16[0] != "" && slotName == SCR_BaseGameMode.m_SquadLoadoutConfig.Class16[0] && C16Slots >= SCR_BaseGameMode.m_SquadLoadoutConfig.Class16[1].ToInt())	return false;
			if (SCR_BaseGameMode.m_SquadLoadoutConfig.Class17[0] != "" && slotName == SCR_BaseGameMode.m_SquadLoadoutConfig.Class17[0] && C17Slots >= SCR_BaseGameMode.m_SquadLoadoutConfig.Class17[1].ToInt())	return false;
			if (SCR_BaseGameMode.m_SquadLoadoutConfig.Class18[0] != "" && slotName == SCR_BaseGameMode.m_SquadLoadoutConfig.Class18[0] && C18Slots >= SCR_BaseGameMode.m_SquadLoadoutConfig.Class18[1].ToInt())	return false;
			if (SCR_BaseGameMode.m_SquadLoadoutConfig.Class19[0] != "" && slotName == SCR_BaseGameMode.m_SquadLoadoutConfig.Class19[0] && C19Slots >= SCR_BaseGameMode.m_SquadLoadoutConfig.Class19[1].ToInt())	return false;
			if (SCR_BaseGameMode.m_SquadLoadoutConfig.Class20[0] != "" && slotName == SCR_BaseGameMode.m_SquadLoadoutConfig.Class20[0] && C20Slots >= SCR_BaseGameMode.m_SquadLoadoutConfig.Class20[1].ToInt())	return false;
			if (SCR_BaseGameMode.m_SquadLoadoutConfig.Class21[0] != "" && slotName == SCR_BaseGameMode.m_SquadLoadoutConfig.Class21[0] && C21Slots >= SCR_BaseGameMode.m_SquadLoadoutConfig.Class21[1].ToInt())	return false;
			if (SCR_BaseGameMode.m_SquadLoadoutConfig.Class22[0] != "" && slotName == SCR_BaseGameMode.m_SquadLoadoutConfig.Class22[0] && C22Slots >= SCR_BaseGameMode.m_SquadLoadoutConfig.Class22[1].ToInt())	return false;
			if (SCR_BaseGameMode.m_SquadLoadoutConfig.Class23[0] != "" && slotName == SCR_BaseGameMode.m_SquadLoadoutConfig.Class23[0] && C23Slots >= SCR_BaseGameMode.m_SquadLoadoutConfig.Class23[1].ToInt())	return false;
			if (SCR_BaseGameMode.m_SquadLoadoutConfig.Class24[0] != "" && slotName == SCR_BaseGameMode.m_SquadLoadoutConfig.Class24[0] && C24Slots >= SCR_BaseGameMode.m_SquadLoadoutConfig.Class24[1].ToInt())	return false;
			if (SCR_BaseGameMode.m_SquadLoadoutConfig.Class25[0] != "" && slotName == SCR_BaseGameMode.m_SquadLoadoutConfig.Class25[0] && C25Slots >= SCR_BaseGameMode.m_SquadLoadoutConfig.Class25[1].ToInt())	return false;
			if (SCR_BaseGameMode.m_SquadLoadoutConfig.Class26[0] != "" && slotName == SCR_BaseGameMode.m_SquadLoadoutConfig.Class26[0] && C26Slots >= SCR_BaseGameMode.m_SquadLoadoutConfig.Class26[1].ToInt())	return false;
			if (SCR_BaseGameMode.m_SquadLoadoutConfig.Class27[0] != "" && slotName == SCR_BaseGameMode.m_SquadLoadoutConfig.Class27[0] && C27Slots >= SCR_BaseGameMode.m_SquadLoadoutConfig.Class27[1].ToInt())	return false;
			if (SCR_BaseGameMode.m_SquadLoadoutConfig.Class28[0] != "" && slotName == SCR_BaseGameMode.m_SquadLoadoutConfig.Class28[0] && C28Slots >= SCR_BaseGameMode.m_SquadLoadoutConfig.Class28[1].ToInt())	return false;
			if (SCR_BaseGameMode.m_SquadLoadoutConfig.Class29[0] != "" && slotName == SCR_BaseGameMode.m_SquadLoadoutConfig.Class29[0] && C29Slots >= SCR_BaseGameMode.m_SquadLoadoutConfig.Class29[1].ToInt())	return false;
			if (SCR_BaseGameMode.m_SquadLoadoutConfig.Class30[0] != "" && slotName == SCR_BaseGameMode.m_SquadLoadoutConfig.Class30[0] && C30Slots >= SCR_BaseGameMode.m_SquadLoadoutConfig.Class30[1].ToInt())	return false;
			if (SCR_BaseGameMode.m_SquadLoadoutConfig.Class31[0] != "" && slotName == SCR_BaseGameMode.m_SquadLoadoutConfig.Class31[0] && C31Slots >= SCR_BaseGameMode.m_SquadLoadoutConfig.Class31[1].ToInt())	return false;
			if (SCR_BaseGameMode.m_SquadLoadoutConfig.Class32[0] != "" && slotName == SCR_BaseGameMode.m_SquadLoadoutConfig.Class32[0] && C32Slots >= SCR_BaseGameMode.m_SquadLoadoutConfig.Class32[1].ToInt())	return false;
			m_PlayerId_SLC.slc_availableLoadouts.Insert(slotName);
		} else {
			m_PlayerId_SLC.slc_availableLoadouts = instance.availableLoadouts;
			CountAvailableLoadouts();
			if(m_PlayerId_SLC.slc_availableLoadouts && !m_PlayerId_SLC.slc_availableLoadouts.Contains(slotName))	return false;
		}
		
		return true;
	}
		
	static void CountAvailableLoadouts()
	{
		SCR_BaseGameMode instance = SCR_BaseGameMode.Cast(GetGame().GetGameMode());
		if(Replication.IsServer()){
			if(instance)	instance.DoClientLoadoutUpdate();
		}
	}
	
	//-------------------------------------------------------------------------------------
	//-------------------------------------------------------------------------------------
	//----------------------------------	Overrides	-----------------------------------
	//-------------------------------------------------------------------------------------
	//-------------------------------------------------------------------------------------

	override event void OnWorldPostProcess(World world)
	{
		super.OnWorldPostProcess(world);
		if(Replication.IsServer())	LoadSLConfig();
	};

	//------------------------------------------------------------------------------------------------
	override void OnPlayerAuditSuccess(int iPlayerID)
	{
		BackendApi api = GetGame().GetBackendApi();
		PlayerIDStruct.slc_menuPlayerId = api.GetPlayerUID(iPlayerID);
		DoClientIdUpdate();
		Print("[SLC] Player connected, bohemia ID: "+m_PlayerId_SLC.slc_menuPlayerId);
		super.OnPlayerAuditSuccess(iPlayerID);
		SCR_LoadoutManager loadoutManager = GetGame().GetLoadoutManager();
		SCR_RespawnSystemComponent respawnSystem = SCR_RespawnSystemComponent.GetInstance();
		SCR_FactionManager factionManager = SCR_FactionManager.Cast(GetGame().GetFactionManager());
		Faction faction = factionManager.SGetPlayerFaction(iPlayerID);
		array<ref SCR_BasePlayerLoadout> loadouts = {};
		int factionCount = factionManager.GetFactionsCount();
		string name;
		loadoutManager.GetPlayerLoadoutsByFaction(faction, loadouts);	}
	
	//------------------------------------------------------------------------------------------------
	override void HandleOnFactionAssigned(int playerID, Faction assignedFaction)
	{
		SCR_LoadoutManager loadoutManager = GetGame().GetLoadoutManager();
		array<ref SCR_BasePlayerLoadout> loadouts = {};
		loadoutManager.GetPlayerLoadoutsByFaction(assignedFaction, loadouts);
		if(Replication.IsServer()){
			BackendApi api = GetGame().GetBackendApi();
			menuPlayerId = api.GetPlayerUID(playerID);
			m_PlayerId_SLC.slc_menuPlayerId = menuPlayerId;
		}
		super.HandleOnFactionAssigned(playerID, assignedFaction);
	}
	
	override void HandleOnLoadoutAssigned(int playerID, SCR_BasePlayerLoadout assignedLoadout)
	{
		super.HandleOnLoadoutAssigned(playerID, assignedLoadout);
		
//		SCR_RespawnSuperMenu menu = SCR_RespawnSuperMenu.GetInstance();
		
		protected SCR_RespawnSystemComponent myRespawnSystemComponent = SCR_RespawnSystemComponent.GetInstance();
		array<int> players = {};
		PlayerManager pm = GetGame().GetPlayerManager();
		pm.GetAllPlayers(players);
		PlayerController playerController = GetGame().GetPlayerManager().GetPlayerController(playerID);
		SCR_PlayerFactionAffiliationComponent pfaComp = SCR_PlayerFactionAffiliationComponent.Cast(playerController.FindComponent(SCR_PlayerFactionAffiliationComponent));
		Faction playerFaction = pfaComp.GetAffiliatedFaction();
		foreach (int playerId : players)
		{
			if (myRespawnSystemComponent)
			{
				ArmaReforgerScripted game = GetGame();
				if (!game)	return;
				MenuManager pMenuManager = GetGame().GetMenuManager();
				if (!pMenuManager)	return;
				else {
					IEntity player = GetGame().GetPlayerManager().GetPlayerControlledEntity(playerId);
					SCR_LoadoutRequestUIComponent menu = SCR_LoadoutRequestUIComponent.Cast(player.FindComponent(SCR_LoadoutRequestUIComponent));
					if(pfaComp && menu)	menu.ShowAvailableLoadouts(playerFaction);
				}
			}
		}
	}
	
	protected override void OnPlayerKilled(int playerId, IEntity player, IEntity killer)
	{
		super.OnPlayerKilled(playerId, player, killer);
		SCR_RespawnSystemComponent respawnSystem = SCR_RespawnSystemComponent.GetInstance();
		SCR_FactionManager factionManager = SCR_FactionManager.Cast(GetGame().GetFactionManager());
		Faction faction = factionManager.GetPlayerFaction(playerId);
//		respawnSystem.RemovePlayerRespawnInfo(playerId);
		int factionIndex = factionManager.GetFactionIndex(faction);
		PlayerController playerController = GetGame().GetPlayerManager().GetPlayerController(playerId);
		SCR_PlayerFactionAffiliationComponent pfaComp = SCR_PlayerFactionAffiliationComponent.Cast(playerController.FindComponent(SCR_PlayerFactionAffiliationComponent));
		Faction playerFaction = pfaComp.GetAffiliatedFaction();
		if (pfaComp.CanRequestFaction(playerFaction))	pfaComp.RequestFaction(playerFaction);
		
		
//		SCR_ArsenalManagerComponent m_ArsenalManagerComp;
		
		array<int> players = {};
		PlayerManager pm = GetGame().GetPlayerManager();
		pm.GetAllPlayers(players);
		foreach (int playerID : players)
		{
			if (respawnSystem)
			{
				ArmaReforgerScripted game = GetGame();
				if (!game)	return;
				MenuManager pMenuManager = GetGame().GetMenuManager();
				if (!pMenuManager)	return;
				else {
					IEntity menuPlayer = IEntity.Cast(GetGame().GetPlayerManager().GetPlayerControlledEntity(playerID));
					SCR_LoadoutRequestUIComponent menu = SCR_LoadoutRequestUIComponent.Cast(menuPlayer.FindComponent(SCR_LoadoutRequestUIComponent));
					if(menu)	menu.ShowAvailableLoadouts(playerFaction);
				}
//				else {
//					SCR_ArsenalManagerComponent.GetArsenalManager(m_ArsenalManagerComp);
//					if (m_ArsenalManagerComp)	m_ArsenalManagerComp.GetOnLoadoutUpdated().Insert(UpdateLoadouts);
//				}
			}
		}
	}
}