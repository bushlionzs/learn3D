
x310153_g_ScriptId 					= 	310153  
 
function x310153_ProcEnumEvent( sceneId, selfId, targetId, MissionId )

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
    if GetBattleSceneToggle( BATTLESCENE_TYPE_COUNTRYBATTLELITE ) == 0 then
        return
    end

	AddQuestNumText(sceneId,310153,"�����ܡ�����ս",1)
end



--�������ť������������ִ�д˽ű�
function x310153_ProcEventEntry( sceneId, selfId, targetId)

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
    if GetBattleSceneToggle( BATTLESCENE_TYPE_COUNTRYBATTLELITE ) == 0 then
        return
    end
    		
		-- local MissionName = x300767_g_MissionName;
		BeginQuestEvent(sceneId)
			local Readme_1 = "#Y�����ܡ�����ս#r#W #r"			
			
			local Readme_2 = "\t���ȼ����а��һ������70��ʱ������ս��ÿ���ܿ���һ�Σ�����ʱ��Ϊ������20��00-21��00 ʱ������Ĺ�֮���ս�������Ĺ��ҽ�����#G����#W��#G����#W֮�������һ����#r"
			
			local Readme_3 = "\t����ս��ʼʱ�����ڷ��ط�����ǣ��ŵ��ͱ߾�����10������#R���Ҿ���#W��NPC��#r"
			
			local Readme_4 ="\t#G40������#W����#R����#W��#R���#W��#R�ŵ�#W��#R�߾�#W��#R�Թ�#W��#R���˸�#W�Ĺ�����յ�#Rϵͳ��ʾ#W��#G���ȷ��#W����#R�ɹ��μ�����ս#W��#Rѡ�����#W���򲻻�#G�������ս����#W������������20:00-20:20֮�䣬������������ť#Y�����ҡ�����ս#W���μ�����ս��#r"
			
			local Readme_5="\t������#G���ҹ���Ա#W�ͱ߾�#G�ص�#Wѡ��#Y������ս����ѯ#W���ɽ��в�ѯ��#r"
			
			local Readme_6="\t����ս�У��������#G���ڽ�����#W����Ҫ�����ܵĴݻٸ���й��Ĺ��Ҿ�����#r"
			
			local Readme_7= "\t�������#G���ڷ��ط�#W��Ҫȫ�������Լ����ҵĹ��Ҿ����İ�ȫ��#r"
			
			local Readme_8 ="\t����ս������#G21��00-21:20#W֮�䣬��������������ȡ#G�����#W�������Ķ���ȡ���������ڹ���#G�ݻٻ�#G����ס#K���Ҿ�����������#r"
			
			local Readme_9 ="\t�μ�����ս����ֻ����#R�Ĺ������ǣ���ǣ��ŵ����߾������˸�#K�ȳ�����������ǰ��#R��������#K�������񽫱�#R���#K���������ٴβμ�����ս���"
			
			local Readme = Readme_1..Readme_2..Readme_3..Readme_4..Readme_5..Readme_6..Readme_7..Readme_8..Readme_9
		AddQuestText( sceneId,Readme)
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId);
		
		
end



--�����ȷ����
function x310153_ProcAcceptCheck( sceneId, selfId, NPCId )

end



--**********************************
--����
--**********************************
function x310153_ProcAccept( sceneId, selfId )
end
--**********************************
--����
--**********************************
function x310153_ProcQuestAbandon( sceneId, selfId, MissionId )
end
--**********************************
--����
--**********************************
function x310153_OnContinue( sceneId, selfId, targetId )
end
--**********************************
--����Ƿ�����ύ
--**********************************
function x310153_CheckSubmit( sceneId, selfId )
end
--**********************************
--�ύ
--**********************************
function x310153_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )
end
--**********************************
--ɱ����������
--**********************************
function x310153_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )
end
--**********************************
--���������¼�
--**********************************
function x310153_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end
--**********************************
--���߸ı�
--**********************************
function x310153_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end