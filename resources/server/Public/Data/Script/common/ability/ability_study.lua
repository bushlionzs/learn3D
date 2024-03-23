--首饰铸造

x890000_g_ScriptId = 890000

--x890000_g_AbilityInfo ={ {id=1, name="药品合成"}, {id=2, name="珠宝加工"}, {id=3, name="首饰铸造"} }

function x890000_ProcEnumEvent( sceneId, selfId, targetId, index )
	AddQuestNumText(sceneId, x890000_g_ScriptId, "罗马铸甲术", 3,	 3)
	--AddQuestNumText(sceneId, x890000_g_ScriptId, x890000_g_AbilityInfo[2].name, -1,	x890000_g_AbilityInfo[2].id)
	--AddQuestNumText(sceneId, x890000_g_ScriptId, x890000_g_AbilityInfo[3].name, -1,	x890000_g_AbilityInfo[3].id)
end


function x890000_ProcEventEntry( sceneId , selfId , targetId , state , index )
	local abilityLevel = QueryPlayerAbilityLevel( sceneId, selfId, index )
	local costMoney=0
	local costExp=0
	local limitLevel=0
	costMoney, costExp, limitLevel = GetAbilityLevelupConfig(index, abilityLevel)
	local studyOrLevelup = 0;

	DispatchAbilityInfo(sceneId, selfId, targetId,x890000_g_ScriptId, index, costMoney, studyOrLevelup, costExp, limitLevel);
end



function x890000_OnLevelupSucc( sceneId, selfId )
	SendSpecificImpactToUnit(sceneId, selfId, selfId, selfId, 14318, 0)
end