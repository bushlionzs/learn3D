-------------------------------------------------
-- ף��ׯ2 npc�Ի��� ʱǨ�Ի�
-------------------------------------------------

x700045_CSP_B_MONSTER2		=	40

x700045_g_ScriptId = 700045


x700045_Fuben_ScriptId = 700031

x700045_g_TalkTitle = "���ʱǨ"
x700045_g_TalkContent = "\t��ѽ�����ã�������ô�����ˣ��ղ��ұ����ڴ���ʱ�����������ף���ֵ�������Ҫ������ϸ��ᵽ�𴦣�ͬʱ��ף��ׯ���������޵�����Ҫ���۵�����ٸ����ͣ���ҿ�Щ�ֿ��ߣ����˿������ӻ��ڣ�"

function x700045_ProcEventEntry(sceneId, selfId, NPCId, MissionId,which)	--����������ִ�д˽ű�
	
	
	x700045_DispatchTalkInfo( sceneId, selfId, NPCId,which )
	
end


--**********************************

--�о��¼�

--**********************************

function x700045_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)
	
	local bCreatMonster2 = GetFubenData_Param(sceneId, x700045_CSP_B_MONSTER2 ) ;


	if bCreatMonster2<=0 then
	
		AddQuestNumText(sceneId, x700045_g_ScriptId, x700045_g_TalkTitle,3,1)
	end
			
end



function x700045_DispatchTalkInfo( sceneId, selfId, NPCId, nParam )

	BeginQuestEvent(sceneId)

		--������Ϣ
		AddQuestText(sceneId,"#Y"..x700045_g_TalkTitle)
		AddQuestText(sceneId,x700045_g_TalkContent)
		

	EndQuestEvent()





	DispatchQuestInfo(sceneId, selfId, NPCId, x700045_g_ScriptId, -1);
end


---------------------------------------------------------------------------------------------------
--������븱��
---------------------------------------------------------------------------------------------------
function x700045_ProcAcceptCheck( sceneId, selfId, NPCId )
    return 1
end

----------------------------------------------------------------------------------------------
--��ȷ����
----------------------------------------------------------------------------------------------
function x700045_ProcAccept( sceneId, selfId )

	
	CallScriptFunction( x700045_Fuben_ScriptId, "OnNpcTalk1", sceneId, selfId) ;
	
end

