
x540004_g_ScriptId = 540004

--x540004_g_AbilityInfo ={ {id=1, name="ҩƷ�ϳ�"}, {id=2, name="�鱦�ӹ�"}, {id=3, name="��������"} }

function x540004_ProcEnumEvent( sceneId, selfId, targetId, index )
	AddQuestNumText(sceneId, x540004_g_ScriptId, "������ҽ��", 3,	 5)
	--AddQuestNumText(sceneId, x540004_g_ScriptId, x540004_g_AbilityInfo[2].name, -1,	x540004_g_AbilityInfo[2].id)
	--AddQuestNumText(sceneId, x540004_g_ScriptId, x540004_g_AbilityInfo[3].name, -1,	x540004_g_AbilityInfo[3].id)
end


function x540004_ProcEventEntry( sceneId , selfId , targetId , state , index )
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
	DispatchAbilityInfo(sceneId, selfId, targetId,x540004_g_ScriptId, index, costMoney, studyOrLevelup, costExp, limitLevel);
end