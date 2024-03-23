
x300746_g_ScriptId = 300746

--��һ�������ID
--g_MissionIdPre =

--��������ID
--x300746_g_MessionIdAfter0	= 300747
--x300746_g_MessionIdAfter1	= 300748
--x300746_g_MessionIdAfter2	= 300749

--�����ı�����
x300746_g_MissionName="�����ս�����ܡ�"
x300746_g_MissionName0="�����ս����"
--x300746_g_MissionName1="ʮ����֮ս"
--x300746_g_MissionName2="��³��֮ս"

--MisDescEnd
--**********************************
--������ں���
--**********************************
function x300746_ProcEventEntry( sceneId, selfId, targetId )	--����������ִ�д˽ű�

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
    if GetBattleSceneToggle( BATTLESCENE_TYPE_GUILDBATTLE ) == 0 then
        return
    end

	local Readme_1 = "#Y�����ս�����ܡ�#W#r"
	
	local Readme_2 = "#Gһ����ս������#W#r��������ÿ�ܶ��������17��00-18��30֮�䱨����ϵͳ����20��00�Զ��������ս����#r"
	
	local Readme_3 = "#G����ʤ���ж���#W#r1���涨ʱ���ڣ��������ȴﵽ100�ֵ�һ����ʤ��#r2���ڹ涨ʱ����δ�ֳ�ʤ��������ָߵ�һ����ʤ��#r3����ս������ǰ�������з�ս�죬����ǰ���ʤ����#r"
	
	local Readme_4 = "#G����ս������#W#r1��ս���е�4�����ֿ���ռ�죬ռ���ÿ������ÿ10�뽫����1����ֺ�1��ս����Դ��#r2��ռ��ȫ��4�����ֽ����˫��������#r3���ڶ�ȡ����ʱ����ʹ�ü��ܣ�ÿ�ύһ�λ��10���֡�#r4����������ڱ����ֿ⽻����Ҳ������ռ���2���ٽ�����������һ��������#r"	
	
	local Readme_5 = "5����ս���У�������������60ս����ԴΪ������Ա�������20���ӵ�����10����������10���Ե�Buff��Ҳ��������20ս����ԴΪ����ս�첹��10%������ֵ��"
	
	local Readme = Readme_1..Readme_2..Readme_3..Readme_4..Readme_5
	
	BeginQuestEvent(sceneId);AddQuestText(sceneId,Readme)
	
	--AddQuestNumText(sceneId,x300746_g_MessionIdAfter0,x300746_g_MissionName0,1)
	
	--AddQuestNumText(sceneId,x300746_g_MessionIdAfter1,x300746_g_MissionName1,1)
	
	--AddQuestNumText(sceneId,x300746_g_MessionIdAfter2,x300746_g_MissionName2,1)
	
	EndQuestEvent(sceneId);DispatchQuestEventList(sceneId,selfId,targetId)
	
end

--**********************************
--�о��¼�
--**********************************
function x300746_ProcEnumEvent( sceneId, selfId, targetId, MissionId )

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
    if GetBattleSceneToggle( BATTLESCENE_TYPE_GUILDBATTLE ) == 0 then
        return
    end
    
	local pos = GetLevel(sceneId, selfId)--�ж��Ƿ����45��
	if pos >= 20 then
		AddQuestNumText(sceneId,x300746_g_ScriptId,x300746_g_MissionName,1);
	end
	
end


--********************
--����������
--**********************************
function x300746_ProcAcceptCheck( sceneId, selfId, NPCId )
		return 1
end

--**********************************
--����
--**********************************
function x300746_ProcAccept( sceneId, selfId )

end

--**********************************
--����
--**********************************
function x300746_ProcQuestAbandon( sceneId, selfId, MissionId )

end

--**********************************
--����
--**********************************
function x300746_OnContinue( sceneId, selfId, targetId )

end

--**********************************
--����Ƿ�����ύ
--**********************************
function x300746_CheckSubmit( sceneId, selfId )

end

--**********************************
--�ύ
--**********************************
function x300746_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )

end

--**********************************
--ɱ����������
--**********************************
function x300746_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )

end

--**********************************
--���������¼�
--**********************************
function x300746_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

--**********************************
--���߸ı�
--**********************************
function x300746_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end
