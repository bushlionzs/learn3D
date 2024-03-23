--�һ�90��ñ��
--MisDescBegin
--�ű���
x570007_g_ScriptId = 570007

--�����Ƕ�̬**************************************************************

--�����ı�����
x570007_g_MissionName = "������ʯ���һ���ñ��"
x570007_g_EXCName = "�һ���ñ��"		--�һ����� ����������ʾ���������ʹ��
x570007_g_EXCItemName = "�߼�����ʯ"		--�һ�����Ҫ�ĵ�������
x570007_g_ItemId = 11050003           --�������ID
x570007_g_ItemNum = 350                 --��������  
x570007_g_ItemBonus = {{id=10204003,num=1},{id=10204013,num=1},{id=10204023,num=1},{id=10204033,num=1},{id=10204043,num=1},{id=10204053,num=1},{id=10204063,num=1},{id=10204073,num=1},{id=10204083,num=1},{id=10204093,num=1},{id=10204103,num=1},{id=10204113,num=1}}
x570007_g_MissionInfo = format("\t��ȷ��Ҫʹ��#G%s#W%s��\n\t����Ҫ#R%d��#W#G%s#W��",x570007_g_EXCItemName,x570007_g_EXCName,x570007_g_ItemNum,x570007_g_EXCItemName)	--����˵������
x570007_g_MissionError = format("\t��û���㹻������%s���޷�%s��",x570007_g_EXCItemName,x570007_g_EXCName)	--������Ϣ

--MisDescEnd
--**********************************
--������ں���
--**********************************
function x570007_ProcEventEntry( sceneId, selfId, targetId ,scriptId,seleteId)	--����������ִ�д˽ű�

	local zhiye = GetZhiye(sceneId, selfId)
	local longyannum = GetItemCount(sceneId, selfId, x570007_g_ItemId)
	local strText = format("\t��������#R%d��#W#G%s#W��",longyannum,x570007_g_EXCItemName)
		BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"#Y"..x570007_g_MissionName)
			AddQuestText(sceneId,x570007_g_MissionInfo)
			AddQuestText(sceneId,strText)
			AddQuestItemBonus(sceneId, x570007_g_ItemBonus[zhiye+1].id,x570007_g_ItemBonus[1].num)
		EndQuestEvent()
		DispatchQuestInfo(sceneId, selfId, targetId, x570007_g_ScriptId,-1)

end

--**********************************
--�о��¼�
--**********************************
function x570007_ProcEnumEvent( sceneId, selfId, targetId, MissionId )

	AddQuestNumText(sceneId,x570007_g_ScriptId,x570007_g_MissionName,3);
	
end



--**********************************
--����
--**********************************
function x570007_ProcAccept( sceneId, selfId )
	
	local Num = GetItemCount( sceneId, selfId, x570007_g_ItemId )

	if Num < x570007_g_ItemNum then 
		BeginQuestEvent(sceneId)
			AddQuestText(sceneId,x570007_g_MissionError)
		EndQuestEvent()
		DispatchQuestTips(sceneId, selfId)
	end
	
	if Num >= x570007_g_ItemNum then 

		local zhiye = GetZhiye(sceneId, selfId)
		local weiyi = ItemIsUnique(sceneId,selfId, x570007_g_ItemBonus[zhiye+1].id)
		local have  = HaveItem( sceneId,selfId,x570007_g_ItemBonus[zhiye+1].id)
		
		if weiyi ~= 1  then
			BeginAddItem(sceneId)
				AddItem( sceneId,x570007_g_ItemBonus[zhiye+1].id,x570007_g_ItemBonus[1].num)
			local ret = EndAddItem(sceneId,selfId)
			if ret > 0 then
				AddItemListToPlayer(sceneId,selfId)
				DelItem(sceneId,selfId,x570007_g_ItemId,x570007_g_ItemNum)
			else
			BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"��Ʒ���������޷������Ʒ��")
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)
			end	
		elseif weiyi == 1 then
			if have < 1 then
				BeginAddItem(sceneId)
					AddItem( sceneId,x570007_g_ItemBonus[zhiye+1].id,x570007_g_ItemBonus[1].num)
				local ret = EndAddItem(sceneId,selfId)
				if ret > 0 then
					AddItemListToPlayer(sceneId,selfId)
					DelItem(sceneId,selfId,x570007_g_ItemId,x570007_g_ItemNum)
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
		
function x570007_ProcAcceptCheck( sceneId, selfId, NPCId )
	return 1

end


--**********************************
--����
--**********************************
function x570007_ProcQuestAbandon( sceneId, selfId, MissionId )

end

--**********************************
--����
--**********************************
function x570007_OnContinue( sceneId, selfId, targetId )

end

--**********************************
--����Ƿ�����ύ
--**********************************
function x570007_CheckSubmit( sceneId, selfId )

end

--**********************************
--�ύ
--**********************************
function x570007_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )

end

--**********************************
--ɱ����������
--**********************************
function x570007_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )

end

--**********************************
--���������¼�
--**********************************
function x570007_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

--**********************************
--���߸ı�
--**********************************
function x570007_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end
