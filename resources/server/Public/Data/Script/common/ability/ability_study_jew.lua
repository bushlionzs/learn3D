
x890002_g_ScriptId = 890002

--x890002_g_AbilityInfo ={ {id=1, name="ҩƷ�ϳ�"}, {id=2, name="�鱦�ӹ�"}, {id=3, name="��������"} }

function x890002_ProcEnumEvent( sceneId, selfId, targetId, index )
	AddQuestNumText(sceneId, x890002_g_ScriptId, "ӡ���鱦��", 3,	 2)
	--AddQuestNumText(sceneId, x890002_g_ScriptId, x890002_g_AbilityInfo[2].name, -1,	x890002_g_AbilityInfo[2].id)
	--AddQuestNumText(sceneId, x890002_g_ScriptId, x890002_g_AbilityInfo[3].name, -1,	x890002_g_AbilityInfo[3].id)
end


function x890002_ProcEventEntry( sceneId , selfId , targetId , state , index )
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
	DispatchAbilityInfo(sceneId, selfId, targetId,x890002_g_ScriptId, index, costMoney, studyOrLevelup, costExp, limitLevel);
end