x300510_g_ScriptId = 300510
x300510_g_MissionName = "·µ»ØÍõ³Ç"

x300510_g_CountrySceneList	= {50, 150, 250, 350}

function x300510_ProcEnumEvent(sceneId, selfId, targetId, MissionId)

	AddQuestNumText(sceneId, x300510_g_ScriptId, x300510_g_MissionName, 14)

end

function x300510_ProcEventEntry(sceneId, selfId, targetId)
	
	local aimscene = x300510_g_CountrySceneList[GetCurCountry(sceneId, selfId)+1];
	NewWorld(sceneId, selfId, aimscene , 208, 40, 300510);

end