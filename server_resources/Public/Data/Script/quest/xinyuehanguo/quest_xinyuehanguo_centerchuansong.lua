--���ܣ����Ĵ���
--NPC�����Ĵ���ʹ��

x211022_g_ScriptId = 211022
x211022_g_MissionName="������"
--**********************************

--������ں���

--**********************************

function x211022_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
	CallScriptFunction(COMMON_CHUANSONG_NORMAL, "TransferFunc",sceneId, selfId, 1,86,130)
end

--�û�ͨ��UI�����л�����
--��CGMapInfoHandler�б�����
function x211022_OnChangeSceneEvent(sceneId, selfId, index, Backhaul)	
				
	--�õ�����ó�����Ҫ����С�ȼ�������ID��λ����Ϣ
	local MinUserLevel, targetSceneId, PosX,PosZ = GetNewSceneInfoByIndex(sceneId,index)
	
	local level = GetLevel(sceneId, selfId)
	
	if level >= MinUserLevel then
		if IsInStall(sceneId, selfId) == 0 then
			NewWorld(sceneId,selfId,targetSceneId,PosX,PosZ,211022)	
		end
	end

end

--**********************************

--�о��¼�

--**********************************

function x211022_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
		AddQuestNumText(sceneId, x211022_g_ScriptId, x211022_g_MissionName)
end



--**********************************

--����������

--**********************************

function x211022_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--����

--**********************************

function x211022_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--����

--**********************************

function x211022_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x211022_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--�ύ

--**********************************

function x211022_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--ɱ����������

--**********************************

function x211022_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x211022_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x211022_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end