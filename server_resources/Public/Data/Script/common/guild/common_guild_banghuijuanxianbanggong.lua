
x300633_g_ScriptId = 300633

--�����ı�����
x300633_g_MissionName="����᡿�ﹱ����"

--MisDescEnd
--**********************************
--������ں���
--**********************************
function x300633_ProcEventEntry( sceneId, selfId, targetId )	--����������ִ�д˽ű�

	if GetGuildOfficial(sceneId, selfId) ~= -1 then--�ж��Ƿ������
	
		local localexp = floor( (GetLevel( sceneId, selfId ))  * 200 )

		local Readme_1 = "#Y����᡿�ﹱ����#r#W"
		
		local Readme_2 = "\t������ͨ��#G25��ﹱ#W������#G1���ᾭ��#W��ͬʱ��Ҳ�����#G"..localexp.."����˾���#W��"
		
		local Readme_3 = "#W#r#Y���Ƿ�Ҫ�����᣿"
		
		local Readme = Readme_1..Readme_2..Readme_3
		
		BeginQuestEvent(sceneId);AddQuestText(sceneId, Readme);EndQuestEvent(sceneId);DispatchQuestEventList(sceneId,selfId,targetId);DispatchQuestInfo( sceneId, selfId, targetId, x300633_g_ScriptId, -1 );

	end
	
end

--**********************************
--�о��¼�
--**********************************
function x300633_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	--AddQuestNumText(sceneId,x300633_g_ScriptId,x300633_g_MissionName);
end


--********************
--����������
--**********************************
function x300633_ProcAcceptCheck( sceneId, selfId, NPCId )
		return 1
end

--**********************************
--����
--**********************************
function x300633_ProcAccept( sceneId, selfId )

	if GetGuildOfficial(sceneId, selfId) == -1 then
		BeginQuestEvent(sceneId);AddQuestText(sceneId, "������ʧ�ܡ�");EndQuestEvent(sceneId);DispatchQuestTips(sceneId,selfId)
		Msg2Player(sceneId,selfId,"�ܱ�Ǹ�������ǰ���Ա���޷����а�Ὠ�衣",8,2)
		return
	end
	
	if GetGuildUserPoint(sceneId, selfId) < 25 then
		BeginQuestEvent(sceneId);AddQuestText(sceneId, "������ʧ�ܡ�");EndQuestEvent(sceneId);DispatchQuestTips(sceneId,selfId)
		Msg2Player(sceneId,selfId,"�ܱ�Ǹ������ӵ�еİﹱ�����ﹱ�������󣬽�����ʧ�ܣ�",8,2)
		return
	end
	
	-- �жϰ��İﹱ��������Ƿ�����
	GuildCanExpBuild(sceneId, selfId, x300633_g_ScriptId, "OnGuildScript_Callback" )
	
end

-- �ص�����
function x300633_OnGuildScript_Callback( sceneId, selfId, param1, param2, param3, param4 )

	if param1==1 then	-- �ɹ�
				
		local localexp = floor ((GetLevel( sceneId, selfId ))  * 200)
					
		SubGuildUserPoint(sceneId, selfId, 25)				--�۳����˰ﹱ
		Msg2Player(sceneId,selfId,"����᡿�ﹱ����:�۳��ﹱ25��",8,2)
		
		AddExp(sceneId, selfId, localexp)					--���˾���
		Msg2Player(sceneId,selfId,"����᡿�ﹱ����:���#R����"..localexp.."��#o�Ľ���",8,2)
		Msg2Player(sceneId,selfId,"���#R����"..localexp.."��#o�Ľ���",8,3)		
		AddGuildExp(sceneId, selfId, 1)				--��ᾭ��
		
		--AddGuildMerit(sceneId, selfId, 1)         --��Ṧ��
		--Msg2Player(sceneId,selfId,"����᡿�ﹱ����:��ð�Ṧ��1��",8,2)
		Msg2Player( sceneId, selfId, (GetName(sceneId, selfId)).."����������25��ﹱ��ʹ��ᾭ�������1�㡣", 6 )		--���㲥
		
	else	--ʧ��
		BeginQuestEvent(sceneId);AddQuestText(sceneId, "������ʧ�ܡ�");EndQuestEvent(sceneId);DispatchQuestTips(sceneId,selfId)
		Msg2Player(sceneId,selfId,"�ܱ�Ǹ�������ڵİ��ÿ��ֻ�ܽ���" .. param2 .. "�ΰﹱ���裬������������",8,2)	
	end
end

--**********************************
--����
--**********************************
function x300633_ProcQuestAbandon( sceneId, selfId, MissionId )

end

--**********************************
--����
--**********************************
function x300633_OnContinue( sceneId, selfId, targetId )

end

--**********************************
--����Ƿ�����ύ
--**********************************
function x300633_CheckSubmit( sceneId, selfId )

end

--**********************************
--�ύ
--**********************************
function x300633_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )

end

--**********************************
--ɱ����������
--**********************************
function x300633_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )

end

--**********************************
--���������¼�
--**********************************
function x300633_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

--**********************************
--���߸ı�
--**********************************
function x300633_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end
