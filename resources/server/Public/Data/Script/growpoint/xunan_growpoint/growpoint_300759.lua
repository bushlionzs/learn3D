x300803_g_scriptId  = 300803
x300803_g_Impact1   = -1 --Ч��ID
x300803_g_Impact2   = -1 --����

x300803_g_MissionId 	= 7558			--����ID
x300803_g_ItemId 		= 13011605		--��ƷID
x300803_g_ScriptId 		= 300759		--�ű�ID

x300803_g_UseSceneID	= 350			--ʹ����Ʒ����
x300803_g_UsePosX		= 122			--ʹ����Ʒλ��
x300803_g_UsePosZ		= 58


--**********************************
--�¼��������
--**********************************
function x300803_ProcEventEntry( sceneId, selfId, bagIndex )
--SendSpecificImpactToUnit(sceneId, selfId, selfId, selfId, x300803_g_Impact1, 0); --��Ч
	local x,z = GetWorldPos (sceneId,selfId)
	if(x300803_g_UseSceneID == sceneId and abs(x300803_g_UsePosX - x) < 30 and abs(x300803_g_UsePosZ - z) < 30) then
	else
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"�˴�����ʹ�ø���Ʒ��")
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		return 0;
	end
	
	local bHaveMission	= IsHaveQuestNM(sceneId, selfId, x300803_g_MissionId);
	if(bHaveMission > 0) then
	    local misIndex = GetQuestIndexByID(sceneId, selfId, x300803_g_MissionId);
		local bDone = GetQuestParam(sceneId, selfId, misIndex, 7);
		if(bDone == 0) then
			return CallScriptFunction( x300803_g_ScriptId, "OnPositionUseItem", sceneId, selfId, x300803_g_MissionId, x300803_g_ItemId );
		else
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"���Ѿ�����������")
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)
		end
	else
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"��û���������")
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
	end
	return 0;
end


function x300803_IsSkillLikeScript( sceneId, selfId)
 
	return 0; --����ű���Ҫ����֧��    
	--����0���������ProcEventEntry�߼�
	--����1����������߼�
end

function x300803_CancelImpacts( sceneId, selfId )
	return 0; --����Ҫ����ӿڣ���Ҫ�����պ���,����ʼ�շ���0��
end

function x300803_OnConditionCheck( sceneId, selfId )
	return 0
end

function x300803_OnDeplete( sceneId, selfId )

	return 1
end

function x300803_OnActivateOnce( sceneId, selfId )
end

function x300803_OnActivateEachTick( sceneId, selfId)
	return 1; --���������Խű�, ֻ�����պ���.
end
