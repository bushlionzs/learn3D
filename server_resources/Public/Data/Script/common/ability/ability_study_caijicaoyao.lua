
x540000_g_ScriptId = 540000

--x540000_g_AbilityInfo ={ {id=1, name="药品合成"}, {id=2, name="珠宝加工"}, {id=3, name="首饰铸造"} }

function x540000_ProcEnumEvent( sceneId, selfId, targetId, index )
	AddQuestNumText(sceneId, x540000_g_ScriptId, "采集草药", 3,	 11)
	--AddQuestNumText(sceneId, x540000_g_ScriptId, x540000_g_AbilityInfo[2].name, -1,	x540000_g_AbilityInfo[2].id)
	--AddQuestNumText(sceneId, x540000_g_ScriptId, x540000_g_AbilityInfo[3].name, -1,	x540000_g_AbilityInfo[3].id)
end


function x540000_ProcEventEntry( sceneId , selfId , targetId , state , index )
	local abilityLevel = QueryPlayerAbilityLevel( sceneId, selfId, index )
	local costMoney=0
	local costExp=0
	local limitLevel=0
	costMoney, costExp, limitLevel = GetAbilityLevelupConfig(index, abilityLevel)
	local studyOrLevelup = 0;

	--if abilityLevel > 0 then	--如果学过这个技能
		--studyOrLevelup = 2
	--else 
		--studyOrLevelup = 1
	--end
	DispatchAbilityInfo(sceneId, selfId, targetId,x540000_g_ScriptId, index, costMoney, studyOrLevelup, costExp, limitLevel);
end