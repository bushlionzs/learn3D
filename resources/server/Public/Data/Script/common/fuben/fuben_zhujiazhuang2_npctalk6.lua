-------------------------------------------------
-- ף��ׯ2 npc�Ի��� ���жԻ�(5)
-------------------------------------------------

x700050_CSP_B_BOSS5		=	39

x700050_g_ScriptId = 700050


x700050_Fuben_ScriptId = 700031

x700050_g_TalkTitle = "��뼼��"
x700050_g_TalkContent = "\t ��������޻����ƺ����������ζ�����֪�򿪻���ʲô�������֡��������������������������ġ�������"

function x700050_ProcEventEntry(sceneId, selfId, NPCId, MissionId,which)	--����������ִ�д˽ű�
	
	
	x700050_DispatchTalkInfo( sceneId, selfId, NPCId,which )
	
end


--**********************************

--�о��¼�

--**********************************

function x700050_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)
	
	local bCreatMonster2 = GetFubenData_Param(sceneId, x700050_CSP_B_BOSS5 ) ;


	if bCreatMonster2<=0 then
	
		AddQuestNumText(sceneId, x700050_g_ScriptId, x700050_g_TalkTitle,3,1)
	end
			
end



function x700050_DispatchTalkInfo( sceneId, selfId, NPCId, nParam )

	BeginQuestEvent(sceneId)

		--������Ϣ
		AddQuestText(sceneId,"#Y"..x700050_g_TalkTitle)
		AddQuestText(sceneId,x700050_g_TalkContent)
		

	EndQuestEvent()





	DispatchQuestInfo(sceneId, selfId, NPCId, x700050_g_ScriptId, -1);
end


---------------------------------------------------------------------------------------------------
--������븱��
---------------------------------------------------------------------------------------------------
function x700050_ProcAcceptCheck( sceneId, selfId, NPCId )
    return 1
end

----------------------------------------------------------------------------------------------
--��ȷ����
----------------------------------------------------------------------------------------------
function x700050_ProcAccept( sceneId, selfId )

	
	CallScriptFunction( x700050_Fuben_ScriptId, "OnNpcTalk6", sceneId, selfId) ;
	
end

