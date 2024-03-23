
--�����NPC��
function x300318_ProcEnumEvent( sceneId, selfId, targetId, MissionId )

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

	AddQuestNumText(sceneId,300318,"���ػ�ս��˵����",0,1)--���Ӱ�ť:�����ܡ��ػ�ս��
end

--�������ť������������ִ�д˽ű�
function x300318_ProcEventEntry( sceneId, selfId, targetId,state,index)

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
    if GetBattleSceneToggle( BATTLESCENE_TYPE_ZHUQUEBATTLELITE ) == 0 then
        return
    end

	local Readme_1   = "#Y���ػ�ս��˵����#W#r"
	local Readme_2   = "#Gһ����ս������#W#r"
	local Readme_3   = "  1�����������й���������ÿ#G����20��25~20��40#W�������#G�����ػ�����Ա#W��ս������ȸս��������ս����#r"
	local Readme_4   = "  2���ڱ���û���ػ�ʱ����һ����ᱨ���������ս����ʼʱ�������������ս�򲻻����ս����ֱ�ӳ�Ϊ��Ӧ�ػ���#r"
	local Readme_5   = "  3���ڻ���ػ�ս����ʤ���󣬰������Ϊ#G��ȸ֮��#W��#G����֮��#W������Ա��Ϊ#G��ȸ�ػ�#W��#G�����ػ�#W��#r"
	local Readme_6   = "�ڱ���ʱ���ڣ����ʵ���ߵİ�ᶥ����ʵ���͵İ�ᣬ���������޷��ٴ�������Ӧ�ػ�������20��40�����ʵ���ߵİ��ɹ��������μӵ�����ػ�ս�����ػ�ս�����ڵ���20��40~21��00֮�俪����#r"
	local Readme_7   = "#G����ս������#W#r"
	local Readme_8  = "  1������ս��ʱ��Ϊ2���ӣ�ս����ʼ20�����ڽ��Է�ȫ�����ս������ʤ��ÿ����5�θ�����ᡣ#r"
	local Readme_9  = "  2��20������δ��ʤ�������а�������ʤ��#r"
	local Readme_10  = "  3��˫����������ս��������������������һ����ʤ��#r"
	local Readme_11  = "  4��˫��������ȣ���������������ٵ�һ����ʤ��#r"
	local Readme_12  = "  5��˫����������������ȣ����ػ�����ʤ��#r"
	local Readme_13  = "  6��˫�����ް������������ʱ���ػ�����ʤ��#r"	
	local Readme = Readme_1..Readme_2..Readme_3..Readme_4..Readme_5..Readme_6..Readme_7..Readme_8..Readme_9..Readme_10..Readme_11..Readme_12..Readme_13
	BeginQuestEvent(sceneId);AddQuestText(sceneId,Readme);EndQuestEvent(sceneId);DispatchQuestEventList(sceneId,selfId,targetId)
end

--�����ȷ����
function x300318_ProcAcceptCheck( sceneId, selfId, NPCId )

end




--**********************************
--����
--**********************************
function x300318_ProcAccept( sceneId, selfId )
end

--**********************************
--����
--**********************************
function x300318_ProcQuestAbandon( sceneId, selfId, MissionId )

end

--**********************************
--����
--**********************************
function x300318_OnContinue( sceneId, selfId, targetId )

end

--**********************************
--����Ƿ�����ύ
--**********************************
function x300318_CheckSubmit( sceneId, selfId )

end

--**********************************
--�ύ
--**********************************
function x300318_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )

end

--**********************************
--ɱ����������
--**********************************
function x300318_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )

end

--**********************************
--���������¼�
--**********************************
function x300318_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

--**********************************
--���߸ı�
--**********************************
function x300318_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end



