
--�����NPC��
function x300315_ProcEnumEvent( sceneId, selfId, targetId, MissionId )

	--�Ϸ�����
    if GetMergeDBToggle() == 1 then
        return
    end
    
    --�������ݿ⿪��
		local UpdateDBflag = GetUpdateDBBeforeToggle()
		if UpdateDBflag==1 then
			return
		end
    
    --���Է�����
    --if GetTestServerToggle() == 0 then
    --    return
    --end

    --ս���Լ��Ŀ���
    if GetBattleSceneToggle( BATTLESCENE_TYPE_KINGBATTLE ) == 0 then
        return
    end

	AddQuestNumText(sceneId,300315,"�����ܡ�����ս��",0,1)--���Ӱ�ť:��ȡ���Է�	
end

--�������ť������������ִ�д˽ű�
function x300315_ProcEventEntry( sceneId, selfId, targetId,state,index)

	--�Ϸ�����
    if GetMergeDBToggle() == 1 then
        return
    end
    
    --�������ݿ⿪��
		local UpdateDBflag = GetUpdateDBBeforeToggle()
		if UpdateDBflag==1 then
			return
		end
    
    --���Է�����
    --if GetTestServerToggle() == 0 then
    --    return
    --end

    --ս���Լ��Ŀ���
    if GetBattleSceneToggle( BATTLESCENE_TYPE_KINGBATTLE ) == 0 then
        return
    end

	local Readme_1   = "#Y�����ܡ�����ս��#W#r"
	local Readme_2   = "#Gһ����ս������#W#r"
	local Readme_3   = "  1��ÿ����#G14��00-17��00#W�������ս������#r  2�����ȼ����а��һ�����ڵ���50��ʱ����ĳһ����û�й���ʱ����ÿ�춼�Ὺ������ս��ֱ����������Ϊֹ��#r"
	local Readme_4   = "  3���������ǰ�����#r"
	local Readme_6   = "  4���������������#G15��#W��#r"
	local Readme_7   = "�ڱ���ʱ���ڣ����ʵ���ߵİ��ᶥ����ʵ���͵İ�ᣬ����ʼ����ʾ������17��00�����ʵ����ߵİ��ɹ��������μӵ���Ĺ���ս��������ս�����ڵ���20��00~20��20֮�俪����#r"
	local Readme_8   = "#G����ʤ���ж���#W#r"
	local Readme_9  = "  1��ս������#G2����#W��ſ�#G�ж�ʤ��#W��#r"
	local Readme_10  = "  2��20�����ڽ��Է�ȫ�����ս������ʤ��#r"
	local Readme_11  = "  3��20������δ�ֳ�ʤ�������ж��а�������ʤ��#r"
	local Readme_12  = "  4��˫����������ս��������������ж��������һ����ʤ��#r"
	local Readme_13  = "  5��˫��������ȣ����ж��������������ٵ�һ����ʤ��#r"
	local Readme_14  = "  6��˫����������������ȣ����ж���������ʤ��#r"
	local Readme_15  = "  7��˫�����ް������������ʱ���ж���������ʤ��#r"	
	local Readme_16  = "#G����ս������#W#r"
	local Readme_17  = "  1������ս��ʱ��ֻ����#G2����#W�����ڿ�ս��ץ��ʱ�����ս����#r"
	local Readme_18 = "  2��ÿ��ֻ��#Gһ��#W����ս���Ļ��ᣬ��ս�������߻�ͨ��NPC�����뿪ս���������ٴν��롣#r"
	local Readme_19  = "  3����ս����ÿ����#G5��#W������ᣬ#G��6��#W������ᱻϵͳǿ���뿪ս����#r"	
	local Readme = Readme_1..Readme_2..Readme_3..Readme_4..Readme_6..Readme_7..Readme_8..Readme_9..Readme_10..Readme_11..Readme_12..Readme_13..Readme_14..Readme_15..Readme_16..Readme_17..Readme_18..Readme_19
	BeginQuestEvent(sceneId);AddQuestText(sceneId,Readme);EndQuestEvent(sceneId);DispatchQuestEventList(sceneId,selfId,targetId)
end

--�����ȷ����
function x300315_ProcAcceptCheck( sceneId, selfId, NPCId )

end




--**********************************
--����
--**********************************
function x300315_ProcAccept( sceneId, selfId )
end

--**********************************
--����
--**********************************
function x300315_ProcQuestAbandon( sceneId, selfId, MissionId )

end

--**********************************
--����
--**********************************
function x300315_OnContinue( sceneId, selfId, targetId )

end

--**********************************
--����Ƿ�����ύ
--**********************************
function x300315_CheckSubmit( sceneId, selfId )

end

--**********************************
--�ύ
--**********************************
function x300315_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )

end

--**********************************
--ɱ����������
--**********************************
function x300315_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )

end

--**********************************
--���������¼�
--**********************************
function x300315_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

--**********************************
--���߸ı�
--**********************************
function x300315_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end



