--�����NPC��
function x300360_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	AddQuestNumText(sceneId,300360,"��ʦͽϵͳ˵����",0,0)	
end



--�������ť������������ִ�д˽ű�
function x300360_ProcEventEntry( sceneId, selfId, targetId,state,index)	
		local Readme_1 = "#Y��ʦͽϵͳ˵����#r"
		local Readme_2 = "#W\t�ɼ�˼����#G�Ҹ�ʦ��#W��#G�ո�ͽ��#W���ܸ����������벻���ĺô���#r"
		local Readme_3 = "#W#r\t������ͨ��#G����ʦ��#W��#G����ͽ��#W��Ѱ��ϣ����Ϊʦ��/ͽ�ܵ����,Ҳ����ͨ��#G��������#W��ʦ������ͽ��������������Ϣ������к��ʵ���ѡ��Ҳ������ʦ�����ӣ�ֱ�����������Ϊʦͽ��#r"
		local Readme_4 = "#W#r\t20������û��ʦ������ҿ��Գ�Ϊͽ�ܣ�50�����ϵ���ҿ��Գ�Ϊʦ������ͽʱ#Gʦͽ�ȼ������10������#W����10������#r"
		local Readme_5 = "#W#r\t��ͽ��ÿ����һ��ʱ��#Gʦ��#W��#Gʦ����ʦ��#W������#G�����Ľ���#W����ͽ�ܵĵȼ���ȼ����а����һ����ҵĵȼ����10������ʱ����õĴ�־�����ԭ������#G����50%#W������ʦ����ͬһ����������ͽ�ܵĵȼ���ȼ����а����һ����ҵĵȼ����10������ʱ����õĴ�־�����ԭ������#G����100%#W��#r"
		local Readme_6 = "#W#r\tʦ������Ϊ�ӳ�����ͽ������ʱ��������ϻ�������Ĺ���ʦ�������#G�������������#W��#r"
		local Readme_7 = "#W#r\tÿ��ʦ��������ȡ����ͽ�ܣ��������޷��ٴ���ȡ��һ��ͽ�ܡ�Ҫ��ȡ�����ͽ�ܣ���Ҫ����#G��������#W����ȡ���߼���ʦ���ƺš�#r"
		local Readme_8 = "#W#r\t��Ϊʦ�������ȡһ��ͽ�ܣ�ʦ����������ͽ�ܳ�ʦʱ������ȡ����ͽ�ܣ�ʦ����������ͽ�ܳ�ʦʱ������ȡ����ͽ�ܣ�ʦ������ʮ��ͽ�ܳ�ʦʱ������ȡ����ͽ�ܣ�ʦ��������ʮ��ͽ�ܳ�ʦʱ������ȡ����ͽ�ܡ����ݿ�����ȡ��ͬ������ͽ�ܣ�ʦ���ĳƺ�Ҳ����֮�仯��#r"
		local Readme = Readme_1..Readme_2..Readme_3..Readme_4..Readme_5..Readme_7
		--BeginQuestEvent(sceneId);AddQuestText(sceneId,"��ťA��Ӧ����������");EndQuestEvent(sceneId);DispatchQuestInfo(sceneId, selfId, targetId, 300360, -1)--˫��ť
		BeginQuestEvent(sceneId);AddQuestText(sceneId, Readme);EndQuestEvent(sceneId);DispatchQuestEventList(sceneId,selfId,targetId);DispatchQuestInfoNM( sceneId, selfId, targetId, -1, -1,2 )--����ť
end



--�����ȷ����
function x300360_ProcAcceptCheck( sceneId, selfId, NPCId )
	
			BeginQuestEvent(sceneId);AddQuestText(sceneId,"��ťA��Ӧ����������");EndQuestEvent(sceneId);DispatchQuestTips(sceneId,selfId)
			
			Msg2Player(sceneId,selfId,"��ťA��Ӧ����������",8,2)

end



--**********************************
--����
--**********************************
function x300360_ProcAccept( sceneId, selfId )
end
--**********************************
--����
--**********************************
function x300360_ProcQuestAbandon( sceneId, selfId, MissionId )
end
--**********************************
--����
--**********************************
function x300360_OnContinue( sceneId, selfId, targetId )
end
--**********************************
--����Ƿ�����ύ
--**********************************
function x300360_CheckSubmit( sceneId, selfId )
end
--**********************************
--�ύ
--**********************************
function x300360_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )
end
--**********************************
--ɱ����������
--**********************************
function x300360_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )
end
--**********************************
--���������¼�
--**********************************
function x300360_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end
--**********************************
--���߸ı�
--**********************************
function x300360_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end