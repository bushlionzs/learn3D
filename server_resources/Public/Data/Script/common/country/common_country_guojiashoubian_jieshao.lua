--**********************************
--������ں���
--**********************************
function x300743_ProcEventEntry( sceneId, selfId, targetId )	--����������ִ�д˽ű�
		BeginQuestEvent(sceneId);
		local localexp = (GetLevel( sceneId, selfId )) * 1000*0.5*5		
		
		local Readme_1 = "#Y�����ر�#W#r"
		
		local Readme_2 = "\t�������߾��رߣ���ֹ�������֣��ڹ涨ʱ������ɣ��ɹ��ظ���������ر߽���#G"..localexp.."#W����˾��顣#r"
		
		local Readme_3 = "\t���ر��ڼ䣬������ɱ���ַ��ҷ��ĵ��ˡ�"
		
		local Readme = Readme_1 .. Readme_2 .. Readme_3
				
		AddQuestText(sceneId, Readme);EndQuestEvent(sceneId);DispatchQuestEventList(sceneId,selfId,targetId);DispatchQuestInfoNM( sceneId, selfId, targetId, -1, -1,2 );
	
	
end

--**********************************
--�о��¼�
--**********************************
function x300743_ProcEnumEvent( sceneId, selfId, targetId, MissionId )

end


--********************
--����������
--**********************************
function x300743_ProcAcceptCheck( sceneId, selfId, NPCId )
		return 1
end

--**********************************
--����
--**********************************
function x300743_ProcAccept( sceneId, selfId )

	
end

--**********************************
--����
--**********************************
function x300743_ProcQuestAbandon( sceneId, selfId, MissionId )

end

--**********************************
--����
--**********************************
function x300743_OnContinue( sceneId, selfId, targetId )

end

--**********************************
--����Ƿ�����ύ
--**********************************
function x300743_CheckSubmit( sceneId, selfId )

end

--**********************************
--�ύ
--**********************************
function x300743_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )

end

--**********************************
--ɱ����������
--**********************************
function x300743_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )

end

--**********************************
--���������¼�
--**********************************
function x300743_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

--**********************************
--���߸ı�
--**********************************
function x300743_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end
