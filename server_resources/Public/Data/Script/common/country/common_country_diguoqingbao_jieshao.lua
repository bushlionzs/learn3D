--**********************************
--������ں���
--**********************************
function x300745_ProcEventEntry( sceneId, selfId, targetId )	--����������ִ�д˽ű�
		BeginQuestEvent(sceneId);
		local localexp = (GetLevel( sceneId, selfId )) *1000*0.6*3	

		local Readme_1 = "#Y�й��鱨#r#W"
		
		local Readme_2 = "\t������ȡ�й��Ļ����鱨����������ɹ��ظ�������#G"..localexp.."#W����˾��顣#r"
		
		local Readme_3 = "\t�����ǵ��й������������Ҫ����С�ģ���������ӻ�����ɱ�����"
		
		local Readme = Readme_1..Readme_2..Readme_3
		
		AddQuestText(sceneId, Readme);EndQuestEvent(sceneId);DispatchQuestEventList(sceneId,selfId,targetId);DispatchQuestInfoNM( sceneId, selfId, targetId, -1, -1,2 );
	
end

--**********************************
--�о��¼�
--**********************************
function x300745_ProcEnumEvent( sceneId, selfId, targetId, MissionId )

end


--********************
--����������
--**********************************
function x300745_ProcAcceptCheck( sceneId, selfId, NPCId )
		return 1
end

--**********************************
--����
--**********************************
function x300745_ProcAccept( sceneId, selfId )

	
end

--**********************************
--����
--**********************************
function x300745_ProcQuestAbandon( sceneId, selfId, MissionId )

end

--**********************************
--����
--**********************************
function x300745_OnContinue( sceneId, selfId, targetId )

end

--**********************************
--����Ƿ�����ύ
--**********************************
function x300745_CheckSubmit( sceneId, selfId )

end

--**********************************
--�ύ
--**********************************
function x300745_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )

end

--**********************************
--ɱ����������
--**********************************
function x300745_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )

end

--**********************************
--���������¼�
--**********************************
function x300745_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

--**********************************
--���߸ı�
--**********************************
function x300745_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end
