--���Ӳֿ�ռ�
--MisDescBegin
--�ű���
x561001_g_ScriptId = 561001

--**************************************************************

--�����ı�����
x561001_g_MainName="���Ӳֿ���չ�ռ�˵��"
x561001_g_MissionName="���Ӳֿ���չ�ռ�"
x561001_g_Readme = "\t���Ӳֿ���չ�ռ���Ҫ����һ���Ľ����ӵ�һҳ��չ�ռ���Ҫ����#G200��#W���ӣ����ӵڶ�ҳ��չ�ռ���Ҫ����#G2��#W���ӣ�"
x561001_g_Notice1 = "\t��ȷ��Ҫ��չ��һҳ��չ�ֿ�����Ҫ����#G200��#W���ӣ�"
x561001_g_Notice2 = "\t��ȷ��Ҫ��չ�ڶ�ҳ��չ�ֿ�����Ҫ����#G2��#W���ӣ�"
x561001_g_Notice3 = "\t������չ�ֿ��Ѿ�ȫ��������"
x561001_g_Notice4 = "\t�������Ӳ��㣡�޷����������չ�ֿ������"
x561001_g_Notice5 = "\t�����ɹ����������˲ֿ����չ�ռ䣡"

x561001_g_NeedMoney1 = 200000			--������һҳ���� 200��
x561001_g_NeedMoney2 = 2000000		--�����ڶ�ҳ���� 2��
x561001_g_BasicSize = 36


--MisDescEnd
--**********************************
--������ں���
--**********************************
function x561001_ProcEventEntry( sceneId, selfId, targetId,scriptid,extid )	--����������ִ�д˽ű�

	if extid == 1 then
		BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"#Y"..x561001_g_MainName)
			AddQuestText(sceneId,x561001_g_Readme);
			AddQuestText(sceneId,x561001_g_Notice1);
		EndQuestEvent(sceneId)	
		DispatchQuestInfo(sceneId, selfId, targetId, scriptid, -1)
	elseif extid == 2 then
		BeginQuestEvent(sceneId)	
			AddQuestText(sceneId,"#Y"..x561001_g_MainName)
			AddQuestText(sceneId,x561001_g_Readme);
			AddQuestText(sceneId,x561001_g_Notice2);
		EndQuestEvent(sceneId)	
		DispatchQuestInfo(sceneId, selfId, targetId, scriptid, -1)
	elseif extid == 3 then
		BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"#Y"..x561001_g_MainName)
			AddQuestText(sceneId,x561001_g_Readme);
			AddQuestText(sceneId,x561001_g_Notice3);
		EndQuestEvent(sceneId)	
		DispatchQuestInfo(sceneId, selfId, targetId, scriptid, -1)
	end
	x561001_SetSelected(sceneId, selfId,extid)
		
end

--**********************************
--�о��¼�
--**********************************
function x561001_ProcEnumEvent( sceneId, selfId, targetId, MissionId )

	local storesize = GetBankSize(sceneId,selfId)
	
	if storesize == x561001_g_BasicSize then
		AddQuestNumText(sceneId, x561001_g_ScriptId, x561001_g_MissionName,3,1)
	elseif storesize == x561001_g_BasicSize*2 then
		AddQuestNumText(sceneId, x561001_g_ScriptId, x561001_g_MissionName,3,2)
	elseif storesize == x561001_g_BasicSize*3 then
		AddQuestNumText(sceneId, x561001_g_ScriptId, x561001_g_MissionName,3,3)
	else
		return
	end

end

--**********************************
--����������
--**********************************
function x561001_ProcAcceptCheck( sceneId, selfId, NPCId )
	return 1
end

---------------------------------------------------------------------------------------------------
--�õ���Ҹղ�ѡ��Ľ���ѡ��
---------------------------------------------------------------------------------------------------

function x561001_GetSelected(sceneId, selfId)
	return GetPlayerRuntimeData(sceneId,selfId,RD_CANGKU_EXT)
end

---------------------------------------------------------------------------------------------------
--������Ҹղ�ѡ��Ľ���ѡ��
---------------------------------------------------------------------------------------------------
function x561001_SetSelected(sceneId, selfId, flag)
	SetPlayerRuntimeData(sceneId,selfId,RD_CANGKU_EXT,flag)
end

--**********************************
--����
--**********************************
function x561001_ProcAccept( sceneId, selfId )

	local flag = x561001_GetSelected(sceneId,selfId)

	if flag == 1 then 
		if IsEnoughMoney( sceneId, selfId, x561001_g_NeedMoney1 ) == 0  then
			BeginQuestEvent(sceneId,selfId)
				AddQuestText(sceneId,x561001_g_Notice4)
			EndQuestEvent()
			DispatchQuestTips(sceneId,selfId)
		else 
			SpendMoney( sceneId, selfId, x561001_g_NeedMoney1 )
			--CostMoney( sceneId , selfId , 1 , x561001_g_NeedMoney1 )
			ExpandBankSize(sceneId,selfId,36)
			BeginQuestEvent(sceneId,selfId)
				AddQuestText(sceneId,x561001_g_Notice5)
			EndQuestEvent()
			DispatchQuestTips(sceneId,selfId)
		end
	elseif flag == 2 then 
		if IsEnoughMoney( sceneId, selfId, x561001_g_NeedMoney2 ) == 0  then
			BeginQuestEvent(sceneId,selfId)
				AddQuestText(sceneId,x561001_g_Notice4)
			EndQuestEvent()
			DispatchQuestTips(sceneId,selfId)
		else 
			SpendMoney( sceneId,selfId,x561001_g_NeedMoney2 )
			ExpandBankSize(sceneId,selfId,36)
			BeginQuestEvent(sceneId,selfId)
				AddQuestText(sceneId,x561001_g_Notice5)
			EndQuestEvent()
			DispatchQuestTips(sceneId,selfId)
		end
	elseif flag == 3 then 
		return
	end


end

--**********************************
--����
--**********************************
function x561001_ProcQuestAbandon( sceneId, selfId, MissionId )

end

--**********************************
--����
--**********************************
function x561001_OnContinue( sceneId, selfId, targetId )

end

--**********************************
--����Ƿ�����ύ
--**********************************
function x561001_CheckSubmit( sceneId, selfId )

end

--**********************************
--�ύ
--**********************************
function x561001_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )

end

--**********************************
--ɱ����������
--**********************************
function x561001_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )

end

--**********************************
--���������¼�
--**********************************
function x561001_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

--**********************************
--���߸ı�
--**********************************
function x561001_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end
