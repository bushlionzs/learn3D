x310337_g_ScriptId 		= 310337
-- ����ȯ��ѯ
x310337_g_ScriptName	= "��ѯ������͸�󽱺���"

x310337_g_TitleInfo		= "#Y��͸�󽱿�������\n\t#W�����һ���������ĵ����֣��������ž޶�ĲƸ���������͸�󽱵��н������ǣ�\n"
x310337_g_TitleInfo1		= "#W\n\t�װ������ѣ����н����������εĺ��������Ե�����ڴ��´εĿ�����"
x310337_g_TitleInfo2		= "#W\t�װ������ѣ���͸����10��30�Ż���е�һ�ο�����"

						
function x310337_ProcEventEntry(sceneId, selfId, NPCId, MissionId,idExt)	--����������ִ�д˽ű�
	local index = GetCountryParam( sceneId, 0, CD_YOULECHANG_CAIPIAO1)
	if index <= 0 then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"#Y"..x310337_g_TitleInfo2)
		EndQuestEvent()
		DispatchQuestEventList(sceneId, selfId, NPCId)      
	end	
	if index > 0 then
	BeginQuestEvent(sceneId)
		--������Ϣ
		AddQuestText(sceneId,"#Y"..x310337_g_TitleInfo)
		
		index = GetCountryParam( sceneId, 1, CD_YOULECHANG_CAIPIAO1)
		if index > 0 then
			AddQuestText(sceneId,"\t\t\t#Y"..index)
			
		end
		index = GetCountryParam( sceneId, 2, CD_YOULECHANG_CAIPIAO1)
		if index > 0 then
			AddQuestText(sceneId,"\n\t\t\t#Y"..index)
			
		end
		index = GetCountryParam( sceneId, 3, CD_YOULECHANG_CAIPIAO1)
		if index > 0 then
			AddQuestText(sceneId,"\n\t\t\t#Y"..index)
			
		end
		index = GetCountryParam( sceneId, 0, CD_YOULECHANG_CAIPIAO2)
		if index > 0 then
			AddQuestText(sceneId,"\n\t\t\t#Y"..index)
			
		end
		index = GetCountryParam( sceneId, 1, CD_YOULECHANG_CAIPIAO2)
		if index > 0 then
			AddQuestText(sceneId,"\n\t\t\t#Y"..index)
			
		end
		index = GetCountryParam( sceneId, 2, CD_YOULECHANG_CAIPIAO2)
		if index > 0 then
			AddQuestText(sceneId,"\n\t\t\t#Y"..index)
			
		end
		index = GetCountryParam( sceneId, 3, CD_YOULECHANG_CAIPIAO2)
		if index > 0 then
			AddQuestText(sceneId,"\n\t\t\t#Y"..index)
			
		end
		AddQuestText(sceneId,"#Y"..x310337_g_TitleInfo1)
	EndQuestEvent()
	DispatchQuestEventList(sceneId, selfId, NPCId)  
	end
end

--�о��¼�
function x310337_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)
	--local state = GetQuestStateNM( sceneId, selfId, NPCId, x310337_g_MissionId)
	AddQuestNumText(sceneId,x310337_g_ScriptId,x310337_g_ScriptName,3,0)
end

function x310337_ProcAcceptCheck( sceneId, selfId, NPCId )
    return 1
end

--��ȷ����
function x310337_ProcAccept( sceneId, selfId )
end