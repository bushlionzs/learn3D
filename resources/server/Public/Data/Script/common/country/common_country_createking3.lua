--���ܽű�
--����������ͶƱ
--MisDescBegin
x300309_g_ScriptId = 300309
x300309_g_MissionId = 4100
x300309_g_Name	="������" 
x300309_g_MissionName="�������� -��ȫ����룩"

--**********************************


--������ں���

--**********************************

function x300309_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
		BeginQuestEvent(sceneId);AddQuestText(sceneId,"#Y".."���Ƿ�ȷ��Ҫ����������");EndQuestEvent();DispatchQuestInfo(sceneId, selfId, targetId, x300309_g_ScriptId, x300309_g_MissionId);
end



--**********************************

--�о��¼�

--**********************************

function x300309_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
		AddQuestNumText(sceneId, x300309_g_ScriptId, x300309_g_MissionName)	
end



--**********************************

--����������

--**********************************

function x300309_ProcAcceptCheck(sceneId, selfId, targetId)
	CountryDeletaBegin( sceneId, selfId );
	CountryVoteBegin(sceneId, selfId);
	--��Ӵ�������
return 1
end


--**********************************

--���鿴����

--**********************************

function x300309_CheckPushList(sceneId, selfId, targetId)
--	if (sceneId==15) then
--		if IsQuestHaveDone(sceneId, selfId, x300309_g_MissionIdPre) > 0 then
--       	    	return 1
--        	end
--        end
--        return 0
	
end

--**********************************

--����

--**********************************

function x300309_ProcAccept(sceneId, selfId)
	  BeginQuestEvent(sceneId);AddQuestText(sceneId,"�����ɹ�");EndQuestEvent();DispatchQuestTips(sceneId, selfId);   
end



--**********************************

--����

--**********************************

function x300309_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x300309_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--�ύ

--**********************************

function x300309_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)

end



--**********************************

--ɱ����������

--**********************************

function x300309_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x300309_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)
		AddQuestNumText(sceneId, x300309_g_ScriptId, "��������")
end



--**********************************

--���߸ı�

--**********************************

function x300309_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end

