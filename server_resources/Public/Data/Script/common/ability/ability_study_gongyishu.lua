
x540006_g_ScriptId = 540006

--x540006_g_AbilityInfo ={ {id=1, name="ҩƷ�ϳ�"}, {id=2, name="�鱦�ӹ�"}, {id=3, name="��������"} }

function x540006_ProcEnumEvent( sceneId, selfId, targetId, index )
	AddQuestNumText(sceneId, x540006_g_ScriptId, "��˹������", 3,	 7)
	--AddQuestNumText(sceneId, x540006_g_ScriptId, x540006_g_AbilityInfo[2].name, -1,	x540006_g_AbilityInfo[2].id)
	--AddQuestNumText(sceneId, x540006_g_ScriptId, x540006_g_AbilityInfo[3].name, -1,	x540006_g_AbilityInfo[3].id)
end


function x540006_ProcEventEntry( sceneId , selfId , targetId , state , index )
	local abilityLevel = QueryPlayerAbilityLevel( sceneId, selfId, index )
	local costMoney=0
	local costExp=0
	local limitLevel=0
	costMoney, costExp, limitLevel = GetAbilityLevelupConfig(index, abilityLevel)
	local studyOrLevelup = 0;

	--if abilityLevel > 0 then	--���ѧ���������
		--studyOrLevelup = 2
	--else 
		--studyOrLevelup = 1
	--end
	DispatchAbilityInfo(sceneId, selfId, targetId,x540006_g_ScriptId, index, costMoney, studyOrLevelup, costExp, limitLevel);
end