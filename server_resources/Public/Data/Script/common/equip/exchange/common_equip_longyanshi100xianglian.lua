--�һ�100������
--MisDescBegin
--�ű���
x570047_g_ScriptId = 570047

--�����Ƕ�̬**************************************************************

--�����ı�����
x570047_g_MissionName = "������ʯ���һ�ڤ������"
x570047_g_EXCName = "�һ�ڤ������"		--�һ����� ����������ʾ���������ʹ��
x570047_g_EXCItemName = "ڤ֮����ʯ"		--�һ�����Ҫ�ĵ�������
x570047_g_ItemId = 11050005           --�������ID
x570047_g_ItemNum = 280                 --��������  
x570047_g_ItemBonus =	{{id=10249500,num=1},{id=10249501,num=1},{id=10249502,num=1},{id=10249503,num=1},{id=10249504,num=1},{id=10249505,num=1},{id=10249506,num=1},{id=10249507,num=1},{id=10249508,num=1},{id=10249509,num=1},{id=10249510,num=1},{id=10249511,num=1}}
x570047_g_MissionInfo = format("\t��ȷ��Ҫʹ��#G%s#W%s��\n\t����Ҫ#R%d��#W#G%s#W��",x570047_g_EXCItemName,x570047_g_EXCName,x570047_g_ItemNum,x570047_g_EXCItemName)	--����˵������
x570047_g_MissionError = format("\t��û���㹻������%s���޷�%s��",x570047_g_EXCItemName,x570047_g_EXCName)	--������Ϣ

--MisDescEnd
--**********************************
--������ں���
--**********************************
function x570047_ProcEventEntry( sceneId, selfId, targetId ,scriptId,seleteId)	--����������ִ�д˽ű�

	local zhiye = GetZhiye(sceneId, selfId)
	local longyannum = GetItemCount(sceneId, selfId, x570047_g_ItemId)
	local strText = format("\t��������#R%d��#W#G%s#W��",longyannum,x570047_g_EXCItemName)
		BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"#Y"..x570047_g_MissionName)
			AddQuestText(sceneId,x570047_g_MissionInfo)
			AddQuestText(sceneId,strText)
			AddQuestItemBonus(sceneId, x570047_g_ItemBonus[zhiye+1].id,x570047_g_ItemBonus[1].num)
		EndQuestEvent()
		DispatchQuestInfo(sceneId, selfId, targetId, x570047_g_ScriptId,-1)

end

--**********************************
--�о��¼�
--**********************************
function x570047_ProcEnumEvent( sceneId, selfId, targetId, MissionId )

	AddQuestNumText(sceneId,x570047_g_ScriptId,x570047_g_MissionName,3);
	
end



--**********************************
--����
--**********************************
function x570047_ProcAccept( sceneId, selfId )
	
	local Num = GetItemCount( sceneId, selfId, x570047_g_ItemId )

	if Num < x570047_g_ItemNum then 
		BeginQuestEvent(sceneId)
			AddQuestText(sceneId,x570047_g_MissionError)
		EndQuestEvent()
		DispatchQuestTips(sceneId, selfId)
	end
	
	if Num >= x570047_g_ItemNum then 

		local zhiye = GetZhiye(sceneId, selfId)
		local weiyi = ItemIsUnique(sceneId,selfId, x570047_g_ItemBonus[zhiye+1].id)
		local have  = HaveItem( sceneId,selfId,x570047_g_ItemBonus[zhiye+1].id)
		
		if weiyi ~= 1  then
			BeginAddItem(sceneId)
				AddItem( sceneId,x570047_g_ItemBonus[zhiye+1].id,x570047_g_ItemBonus[1].num)
			local ret = EndAddItem(sceneId,selfId)
			if ret > 0 then
				AddItemListToPlayer(sceneId,selfId)
				DelItem(sceneId,selfId,x570047_g_ItemId,x570047_g_ItemNum)
			else
			BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"��Ʒ���������޷������Ʒ��")
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)
			end	
		elseif weiyi == 1 then
			if have < 1 then
				BeginAddItem(sceneId)
					AddItem( sceneId,x570047_g_ItemBonus[zhiye+1].id,x570047_g_ItemBonus[1].num)
				local ret = EndAddItem(sceneId,selfId)
				if ret > 0 then
					AddItemListToPlayer(sceneId,selfId)
					DelItem(sceneId,selfId,x570047_g_ItemId,x570047_g_ItemNum)
				else
				BeginQuestEvent(sceneId)
					AddQuestText(sceneId,"��Ʒ���������޷������Ʒ��")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				end	
			else
				BeginQuestEvent(sceneId)
					AddQuestText(sceneId,"���޷��һ������װ����")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
			end	
		end
	end
end
		
function x570047_ProcAcceptCheck( sceneId, selfId, NPCId )
	return 1

end


--**********************************
--����
--**********************************
function x570047_ProcQuestAbandon( sceneId, selfId, MissionId )

end

--**********************************
--����
--**********************************
function x570047_OnContinue( sceneId, selfId, targetId )

end

--**********************************
--����Ƿ�����ύ
--**********************************
function x570047_CheckSubmit( sceneId, selfId )

end

--**********************************
--�ύ
--**********************************
function x570047_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )

end

--**********************************
--ɱ����������
--**********************************
function x570047_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )

end

--**********************************
--���������¼�
--**********************************
function x570047_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

--**********************************
--���߸ı�
--**********************************
function x570047_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end
