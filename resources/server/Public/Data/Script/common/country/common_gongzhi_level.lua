
--�����NPC��
function x300656_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	AddQuestNumText(sceneId,300656,"�������ȡ���Է�",3,1)--���Ӱ�ť:��ȡ���Է�	
end

--�������ť������������ִ�д˽ű�
function x300656_ProcEventEntry( sceneId, selfId, targetId,state,index)
	local x300656Readme = ""
	local Readme_0 = "#Y�������ȡ���Է�#W#r"
	local Readme_3 = "#W\t�����ĵȼ�Ϊ20��~69��֮��ʱ��������ͨ������ȡ��Ӧ�Ĳ��Էѣ��ȼ�����20����������ȡ���Էѣ��������������ȡ����������Ӧ�ĵȼ����һ�һ���Բ���������Ĳ��Էѡ�#r#Rע�����ԷѵĻ�������Ϊ���𿨣� #r"
	local Readme_4  = "#G\t �ȼ�	         ���Է�#W"
	local Readme_6  = "#r\t20~29��		    2��"
	local Readme_7  = "#r\t30~39��		    4��"
	local Readme_8  = "#r\t40~49��		    8��"
	local Readme_9  = "#r\t50~59��		   18��"
	local Readme_10 = "#r\t60~69��		   36��"
	local Readme_6_1  = "#r#d\t20~29��   ����ȡ   2��#W"
	local Readme_7_1  = "#r#d\t30~39��   ����ȡ   4��#W"
	local Readme_8_1  = "#r#d\t40~49��   ����ȡ   8��#W"
	local Readme_9_1  = "#r#d\t50~59��   ����ȡ  18��#W"
	local Readme_10_1 = "#r#d\t60~69��   ����ȡ  36��#W"
	local level_1 = GetQuestData(sceneId, selfId, MD_LEVELUP_LEVEL[1], MD_LEVELUP_LEVEL[2], MD_LEVELUP_LEVEL[3])
	if level_1 < 2 then
		x300656Readme = Readme_0..Readme_3..Readme_4..Readme_6..Readme_7..Readme_8..Readme_9..Readme_10
	elseif level_1 == 2 then
		x300656Readme = Readme_0..Readme_3..Readme_4..Readme_6_1..Readme_7..Readme_8..Readme_9..Readme_10
	elseif level_1 == 3 then
		x300656Readme = Readme_0..Readme_3..Readme_4..Readme_6_1..Readme_7_1..Readme_8..Readme_9..Readme_10
	elseif level_1 == 4 then
		x300656Readme = Readme_0..Readme_3..Readme_4..Readme_6_1..Readme_7_1..Readme_8_1..Readme_9..Readme_10
	elseif level_1 == 5 then
		x300656Readme = Readme_0..Readme_3..Readme_4..Readme_6_1..Readme_7_1..Readme_8_1..Readme_9_1..Readme_10
	elseif level_1 == 6 then
		x300656Readme = Readme_0..Readme_3..Readme_4..Readme_6_1..Readme_7_1..Readme_8_1..Readme_9_1..Readme_10_1
	elseif level_1 > 6 then
		x300656Readme = Readme_0..Readme_3..Readme_4..Readme_6_1..Readme_7_1..Readme_8_1..Readme_9_1..Readme_10_1
	end						
	BeginQuestEvent(sceneId);AddQuestText(sceneId,x300656Readme);EndQuestEvent(sceneId);DispatchQuestInfo(sceneId, selfId, targetId, 300656, -1)

end

--�����ȷ����
function x300656_ProcAcceptCheck( sceneId, selfId, NPCId )
	--081217(����)����PKģʽ��PKֵ����0������ȡ���Է�
	local pkMode = GetPlayerPKMode( sceneId, selfId)
	local pkValue = GetPKValue( sceneId, selfId)
	if pkMode == 2 then
		BeginQuestEvent( sceneId);AddQuestText( sceneId, "�ܱ�Ǹ�����ѿ�����PKģʽ������PKֵ���ߣ��޷�ʹ�ô˹���" );EndQuestEvent();DispatchQuestTips( sceneId, selfId)
		return
	end

	--��ȡ���Է�����
		local x300656gongzhi2 = 0
		local level = GetLevel(sceneId,selfId)
		local level_3 = GetQuestData(sceneId, selfId, MD_LEVELUP_LEVEL[1], MD_LEVELUP_LEVEL[2], MD_LEVELUP_LEVEL[3])
		
		if level < 20 then		
			BeginQuestEvent(sceneId);AddQuestText(sceneId,"���Է���ȡʧ��");EndQuestEvent(sceneId);DispatchQuestTips(sceneId,selfId);Msg2Player(sceneId,selfId,"�ܱ�Ǹ�����ĵȼ�С��20�����޷���ȡ���Էѣ�",8,2)
			return			
		else
			if level_3 == 0 then--��δ��ȡ��
				if level >= 20 and level <= 29 then
					x300656gongzhi2 = 2	
				elseif level >= 30 and level <= 39 then
					x300656gongzhi2 = 2 + 4
				elseif level >= 40 and level <= 49 then
					x300656gongzhi2 = 2 + 4 + 8
				elseif level >= 50 and level <= 59 then
					x300656gongzhi2 = 2 + 4 + 8 + 18
				elseif level >= 60 then
					x300656gongzhi2 = 2 + 4 + 8 + 18 + 36
				end
			elseif level_3 == 2 then--20~29����ȡ��
				if level >= 20 and level <= 29 then
					Msg2Player(sceneId,selfId,"�ܱ�Ǹ�����Ѿ���ȡ����ǰ�ȼ��Ĳ��Էѣ�",8,2)
					return
				elseif level >= 30 and level <= 39 then
					x300656gongzhi2 = 4
				elseif level >= 40 and level <= 49 then
					x300656gongzhi2 = 4 + 8
				elseif level >= 50 and level <= 59 then
					x300656gongzhi2 = 4 + 8 + 18
				elseif level >= 60 then
					x300656gongzhi2 = 4 + 8 + 18 + 36
				end		
			elseif level_3 == 3 then--30~39����ȡ��
				if level >= 20 and level <= 39 then
					Msg2Player(sceneId,selfId,"�ܱ�Ǹ�����Ѿ���ȡ����ǰ�ȼ��Ĳ��Էѣ�",8,2)
					return
				elseif level >= 40 and level <= 49 then
					x300656gongzhi2 = 8
				elseif level >= 50 and level <= 59 then
					x300656gongzhi2 = 8 + 18
				elseif level >= 60 then
					x300656gongzhi2 = 8 + 18 + 36
				end
			elseif level_3 == 4 then--40~49����ȡ��
				if level >= 20 and level <= 49 then
					Msg2Player(sceneId,selfId,"�ܱ�Ǹ�����Ѿ���ȡ����ǰ�ȼ��Ĳ��Էѣ�",8,2)	
					return
				elseif level >= 50 and level <= 59 then
					x300656gongzhi2 = 18
				elseif level >= 60 then
					x300656gongzhi2 = 18 + 36
				end									
			elseif level_3 == 5 then--50~59����ȡ��
				if level >= 20 and level <= 59 then
					Msg2Player(sceneId,selfId,"�ܱ�Ǹ�����Ѿ���ȡ����ǰ�ȼ��Ĳ��Էѣ�",8,2)
					return	
				elseif level >= 60 then
					x300656gongzhi2 = 36
				end
			elseif level_3 >= 6 then
					Msg2Player(sceneId,selfId,"���Ѿ���ȡ��ȫ���ȼ��Ĳ��Էѣ�",8,2)
					return
			end
			
			AddMoney(sceneId,selfId,3,x300656gongzhi2*1000, 100)--��Ǯ
			local level_2 = floor ( ( GetLevel ( sceneId , selfId ) ) / 10 )
			SetQuestData(sceneId,selfId,MD_LEVELUP_LEVEL[1],MD_LEVELUP_LEVEL[2], MD_LEVELUP_LEVEL[3], level_2)--��¼�ɹ���ȡ���Էѵĵȼ���
			Msg2Player(sceneId,selfId,"��ϲ����������˲��Էѣ�#r�𿨣�#R"..x300656gongzhi2.."����",8,2)--������ʾ
		end			

end




--**********************************
--����
--**********************************
function x300656_ProcAccept( sceneId, selfId )
end

--**********************************
--����
--**********************************
function x300656_ProcQuestAbandon( sceneId, selfId, MissionId )

end

--**********************************
--����
--**********************************
function x300656_OnContinue( sceneId, selfId, targetId )

end

--**********************************
--����Ƿ�����ύ
--**********************************
function x300656_CheckSubmit( sceneId, selfId )

end

--**********************************
--�ύ
--**********************************
function x300656_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )

end

--**********************************
--ɱ����������
--**********************************
function x300656_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )

end

--**********************************
--���������¼�
--**********************************
function x300656_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

--**********************************
--���߸ı�
--**********************************
function x300656_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end



