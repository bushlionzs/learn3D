-------------------------------------------------
-- ף��ׯ2 npc�Ի��� ���жԻ�(4)
-------------------------------------------------

x700049_CSP_B_BOSS4		=	38

x700049_g_ScriptId = 700049


x700049_Fuben_ScriptId = 700031

x700049_g_TalkTitle = "��Ի����"
x700049_g_TalkContent = "\t ���������̿���ƺ����������ζ�����֪�򿪻���ʲô�������֡��������������������������ġ��𡱡�"

function x700049_ProcEventEntry(sceneId, selfId, NPCId, MissionId,which)	--����������ִ�д˽ű�
	
	
	x700049_DispatchTalkInfo( sceneId, selfId, NPCId,which )
	
end


--**********************************

--�о��¼�

--**********************************

function x700049_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)
	
	local bCreatMonster2 = GetFubenData_Param(sceneId, x700049_CSP_B_BOSS4 ) ;


	if bCreatMonster2<=0 then
	
		AddQuestNumText(sceneId, x700049_g_ScriptId, x700049_g_TalkTitle,3,1)
	end
			
end



function x700049_DispatchTalkInfo( sceneId, selfId, NPCId, nParam )

	BeginQuestEvent(sceneId)

		--������Ϣ
		AddQuestText(sceneId,"#Y"..x700049_g_TalkTitle)
		AddQuestText(sceneId,x700049_g_TalkContent)
		

	EndQuestEvent()





	DispatchQuestInfo(sceneId, selfId, NPCId, x700049_g_ScriptId, -1);
end


---------------------------------------------------------------------------------------------------
--������븱��
---------------------------------------------------------------------------------------------------
function x700049_ProcAcceptCheck( sceneId, selfId, NPCId )
    return 1
end

----------------------------------------------------------------------------------------------
--��ȷ����
----------------------------------------------------------------------------------------------
function x700049_ProcAccept( sceneId, selfId )

	
	CallScriptFunction( x700049_Fuben_ScriptId, "OnNpcTalk5", sceneId, selfId) ;
	
end

