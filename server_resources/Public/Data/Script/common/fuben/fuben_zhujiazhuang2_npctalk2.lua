-------------------------------------------------
-- ף��ׯ2 npc�Ի��� ���жԻ���1��
-------------------------------------------------

x700046_CSP_B_BOSS1		=	35

x700046_g_ScriptId = 700046


x700046_Fuben_ScriptId = 700031

x700046_g_TalkTitle = "��Ի�Ӹ�"
x700046_g_TalkContent = "\t ��������˸���ƺ����������ζ�����֪�򿪻���ʲô�������֡��������������������������ġ��𡱡�"

function x700046_ProcEventEntry(sceneId, selfId, NPCId, MissionId,which)	--����������ִ�д˽ű�
	
	
	x700046_DispatchTalkInfo( sceneId, selfId, NPCId,which )
	
end


--**********************************

--�о��¼�

--**********************************

function x700046_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)
	
	local bCreatMonster2 = GetFubenData_Param(sceneId, x700031_CSP_B_BOSS1 ) ;


	if bCreatMonster2<=0 then
	
		AddQuestNumText(sceneId, x700046_g_ScriptId, x700046_g_TalkTitle,3,1)
	end
			
end



function x700046_DispatchTalkInfo( sceneId, selfId, NPCId, nParam )

	BeginQuestEvent(sceneId)

		--������Ϣ
		AddQuestText(sceneId,"#Y"..x700046_g_TalkTitle)
		AddQuestText(sceneId,x700046_g_TalkContent)
		

	EndQuestEvent()





	DispatchQuestInfo(sceneId, selfId, NPCId, x700046_g_ScriptId, -1);
end


---------------------------------------------------------------------------------------------------
--������븱��
---------------------------------------------------------------------------------------------------
function x700046_ProcAcceptCheck( sceneId, selfId, NPCId )
    return 1
end

----------------------------------------------------------------------------------------------
--��ȷ����
----------------------------------------------------------------------------------------------
function x700046_ProcAccept( sceneId, selfId )

	
	CallScriptFunction( x700046_Fuben_ScriptId, "OnNpcTalk2", sceneId, selfId) ;
	
end

