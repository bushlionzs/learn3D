-------------------------------------------------
-- ף��ׯ2 npc�Ի��� ���жԻ�(2)
-------------------------------------------------

x700047_CSP_B_BOSS2		=	36

x700047_g_ScriptId = 700047


x700047_Fuben_ScriptId = 700031

x700047_g_TalkTitle = "ľԻ��ֱ"
x700047_g_TalkContent = "\t ��ľ�����жȣ��ƺ����������ζ�����֪�򿪻���ʲô�������֡��������������������������ġ�ľ����"

function x700047_ProcEventEntry(sceneId, selfId, NPCId, MissionId,which)	--����������ִ�д˽ű�
	
	
	x700047_DispatchTalkInfo( sceneId, selfId, NPCId,which )
	
end


--**********************************

--�о��¼�

--**********************************

function x700047_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)
	
	local bCreatMonster2 = GetFubenData_Param(sceneId, x700047_CSP_B_BOSS2 ) ;


	if bCreatMonster2<=0 then
	
		AddQuestNumText(sceneId, x700047_g_ScriptId, x700047_g_TalkTitle,3,1)
	end
			
end



function x700047_DispatchTalkInfo( sceneId, selfId, NPCId, nParam )

	BeginQuestEvent(sceneId)

		--������Ϣ
		AddQuestText(sceneId,"#Y"..x700047_g_TalkTitle)
		AddQuestText(sceneId,x700047_g_TalkContent)
		

	EndQuestEvent()





	DispatchQuestInfo(sceneId, selfId, NPCId, x700047_g_ScriptId, -1);
end


---------------------------------------------------------------------------------------------------
--������븱��
---------------------------------------------------------------------------------------------------
function x700047_ProcAcceptCheck( sceneId, selfId, NPCId )
    return 1
end

----------------------------------------------------------------------------------------------
--��ȷ����
----------------------------------------------------------------------------------------------
function x700047_ProcAccept( sceneId, selfId )

	
	CallScriptFunction( x700047_Fuben_ScriptId, "OnNpcTalk3", sceneId, selfId) ;
	
end

