-------------------------------------------------
-- ף��ׯ2 npc�Ի��� ���жԻ�(3)
-------------------------------------------------

x700048_CSP_B_BOSS3		=	37

x700048_g_ScriptId = 700048


x700048_Fuben_ScriptId = 700031

x700048_g_TalkTitle = "ˮԻ����"
x700048_g_TalkContent = "\t ���ﾧӨ��͸���ƺ����������ζ�����֪�򿪻���ʲô�������֡��������������������������ġ�ˮ����"

function x700048_ProcEventEntry(sceneId, selfId, NPCId, MissionId,which)	--����������ִ�д˽ű�
	
	
	x700048_DispatchTalkInfo( sceneId, selfId, NPCId,which )
	
end


--**********************************

--�о��¼�

--**********************************

function x700048_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)
	
	local bCreatMonster2 = GetFubenData_Param(sceneId, x700048_CSP_B_BOSS3 ) ;


	if bCreatMonster2<=0 then
	
		AddQuestNumText(sceneId, x700048_g_ScriptId, x700048_g_TalkTitle,3,1)
	end
			
end



function x700048_DispatchTalkInfo( sceneId, selfId, NPCId, nParam )

	BeginQuestEvent(sceneId)

		--������Ϣ
		AddQuestText(sceneId,"#Y"..x700048_g_TalkTitle)
		AddQuestText(sceneId,x700048_g_TalkContent)
		

	EndQuestEvent()





	DispatchQuestInfo(sceneId, selfId, NPCId, x700048_g_ScriptId, -1);
end


---------------------------------------------------------------------------------------------------
--������븱��
---------------------------------------------------------------------------------------------------
function x700048_ProcAcceptCheck( sceneId, selfId, NPCId )
    return 1
end

----------------------------------------------------------------------------------------------
--��ȷ����
----------------------------------------------------------------------------------------------
function x700048_ProcAccept( sceneId, selfId )

	
	CallScriptFunction( x700048_Fuben_ScriptId, "OnNpcTalk4", sceneId, selfId) ;
	
end

