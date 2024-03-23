--�һ�60��ñ��
--MisDescBegin
--�ű���
x570004_g_ScriptId = 570004

--�����Ƕ�̬**************************************************************

--�����ı�����
x570004_g_MissionName = "������ʯ���һ�����ñ��"
x570004_g_EXCName = "�һ�����ñ��"		--�һ����� ����������ʾ���������ʹ��
x570004_g_EXCItemName = "�м�����ʯ"		--�һ�����Ҫ�ĵ�������
x570004_g_ItemId = 11050002      --�������ID
x570004_g_ItemNum = 130            --��������  
x570004_g_ItemBonus = {{id=10204002,num=1},{id=10204012,num=1},{id=10204022,num=1},{id=10204032,num=1},{id=10204042,num=1},{id=10204052,num=1},{id=10204062,num=1},{id=10204072,num=1},{id=10204082,num=1},{id=10204092,num=1},{id=10204102,num=1},{id=10204112,num=1}}
x570004_g_MissionInfo = format("\t��ȷ��Ҫʹ��#G%s#W%s��\n\t����Ҫ#R%d��#W#G%s#W��",x570004_g_EXCItemName,x570004_g_EXCName,x570004_g_ItemNum,x570004_g_EXCItemName)	--����˵������
x570004_g_MissionError = format("\t��û���㹻������%s���޷�%s��",x570004_g_EXCItemName,x570004_g_EXCName)	--������Ϣ

--MisDescEnd
--**********************************
--������ں���
--**********************************
function x570004_ProcEventEntry( sceneId, selfId, targetId ,scriptId,seleteId)	--����������ִ�д˽ű�

	local zhiye = GetZhiye(sceneId, selfId)
	local longyannum = GetItemCount(sceneId, selfId, x570004_g_ItemId)
	local strText = format("\t��������#R%d��#W#G%s#W��",longyannum,x570004_g_EXCItemName)
		BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"#Y"..x570004_g_MissionName)
			AddQuestText(sceneId,x570004_g_MissionInfo)
			AddQuestText(sceneId,strText)
			AddQuestItemBonus(sceneId, x570004_g_ItemBonus[zhiye+1].id,x570004_g_ItemBonus[1].num)
		EndQuestEvent()
		DispatchQuestInfo(sceneId, selfId, targetId, x570004_g_ScriptId,-1)

end

--**********************************
--�о��¼�
--**********************************
function x570004_ProcEnumEvent( sceneId, selfId, targetId, MissionId )

	AddQuestNumText(sceneId,x570004_g_ScriptId,x570004_g_MissionName,3);
	
end



--**********************************
--����
--**********************************
function x570004_ProcAccept( sceneId, selfId )
	
	local Num = GetItemCount( sceneId, selfId, x570004_g_ItemId )

	if Num < x570004_g_ItemNum then 
		BeginQuestEvent(sceneId)
			AddQuestText(sceneId,x570004_g_MissionError)
		EndQuestEvent()
		DispatchQuestTips(sceneId, selfId)
	end
	
	if Num >= x570004_g_ItemNum then 

		local zhiye = GetZhiye(sceneId, selfId)
		local weiyi = ItemIsUnique(sceneId,selfId, x570004_g_ItemBonus[zhiye+1].id)
		local have  = HaveItem( sceneId,selfId,x570004_g_ItemBonus[zhiye+1].id)
		
		if weiyi ~= 1  then
			BeginAddItem(sceneId)
				AddItem( sceneId,x570004_g_ItemBonus[zhiye+1].id,x570004_g_ItemBonus[1].num)
			local ret = EndAddItem(sceneId,selfId)
			if ret > 0 then
				AddItemListToPlayer(sceneId,selfId)
				DelItem(sceneId,selfId,x570004_g_ItemId,x570004_g_ItemNum)
			else
			BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"��Ʒ���������޷������Ʒ��")
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)
			end	
		elseif weiyi == 1 then
			if have < 1 then
				BeginAddItem(sceneId)
					AddItem( sceneId,x570004_g_ItemBonus[zhiye+1].id,x570004_g_ItemBonus[1].num)
				local ret = EndAddItem(sceneId,selfId)
				if ret > 0 then
					AddItemListToPlayer(sceneId,selfId)
					DelItem(sceneId,selfId,x570004_g_ItemId,x570004_g_ItemNum)
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
		
function x570004_ProcAcceptCheck( sceneId, selfId, NPCId )
	return 1

end


--**********************************
--����
--**********************************
function x570004_ProcQuestAbandon( sceneId, selfId, MissionId )

end

--**********************************
--����
--**********************************
function x570004_OnContinue( sceneId, selfId, targetId )

end

--**********************************
--����Ƿ�����ύ
--**********************************
function x570004_CheckSubmit( sceneId, selfId )

end

--**********************************
--�ύ
--**********************************
function x570004_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )

end

--**********************************
--ɱ����������
--**********************************
function x570004_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )

end

--**********************************
--���������¼�
--**********************************
function x570004_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

--**********************************
--���߸ı�
--**********************************
function x570004_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end
