--�һ�60������
--MisDescBegin
--�ű���
x570005_g_ScriptId = 570005

--�����Ƕ�̬**************************************************************

--�����ı�����
x570005_g_MissionName = "������ʯ���һ���������"
x570005_g_EXCName = "�һ���������"		--�һ����� ����������ʾ���������ʹ��
x570005_g_EXCItemName = "�м�����ʯ"		--�һ�����Ҫ�ĵ�������
x570005_g_ItemId = 11050002      --�������ID
x570005_g_ItemNum = 50            --��������  
x570005_g_ItemBonus =	{{id=10244002,num=1},{id=10244012,num=1},{id=10244022,num=1},{id=10244032,num=1},{id=10244042,num=1},{id=10244052,num=1},{id=10249219,num=1},{id=10249223,num=1},{id=10249227,num=1},{id=10249231,num=1},{id=10249235,num=1},{id=10249239,num=1}}
x570005_g_MissionInfo = format("\t��ȷ��Ҫʹ��#G%s#W%s��\n\t����Ҫ#R%d��#W#G%s#W��",x570005_g_EXCItemName,x570005_g_EXCName,x570005_g_ItemNum,x570005_g_EXCItemName)	--����˵������
x570005_g_MissionError = format("\t��û���㹻������%s���޷�%s��",x570005_g_EXCItemName,x570005_g_EXCName)	--������Ϣ

--MisDescEnd
--**********************************
--������ں���
--**********************************
function x570005_ProcEventEntry( sceneId, selfId, targetId ,scriptId,seleteId)	--����������ִ�д˽ű�

	local zhiye = GetZhiye(sceneId, selfId)
	local longyannum = GetItemCount(sceneId, selfId, x570005_g_ItemId)
	local strText = format("\t��������#R%d��#W#G%s#W��",longyannum,x570005_g_EXCItemName)
		BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"#Y"..x570005_g_MissionName)
			AddQuestText(sceneId,x570005_g_MissionInfo)
			AddQuestText(sceneId,strText)
			AddQuestItemBonus(sceneId, x570005_g_ItemBonus[zhiye+1].id,x570005_g_ItemBonus[1].num)
		EndQuestEvent()
		DispatchQuestInfo(sceneId, selfId, targetId, x570005_g_ScriptId,-1)

end

--**********************************
--�о��¼�
--**********************************
function x570005_ProcEnumEvent( sceneId, selfId, targetId, MissionId )

	AddQuestNumText(sceneId,x570005_g_ScriptId,x570005_g_MissionName,3);
	
end



--**********************************
--����
--**********************************
function x570005_ProcAccept( sceneId, selfId )
	
	local Num = GetItemCount( sceneId, selfId, x570005_g_ItemId )

	if Num < x570005_g_ItemNum then 
		BeginQuestEvent(sceneId)
			AddQuestText(sceneId,x570005_g_MissionError)
		EndQuestEvent()
		DispatchQuestTips(sceneId, selfId)
	end
	
	if Num >= x570005_g_ItemNum then 

		local zhiye = GetZhiye(sceneId, selfId)
		local weiyi = ItemIsUnique(sceneId,selfId, x570005_g_ItemBonus[zhiye+1].id)
		local have  = HaveItem( sceneId,selfId,x570005_g_ItemBonus[zhiye+1].id)
		
		if weiyi ~= 1  then
			BeginAddItem(sceneId)
				AddItem( sceneId,x570005_g_ItemBonus[zhiye+1].id,x570005_g_ItemBonus[1].num)
			local ret = EndAddItem(sceneId,selfId)
			if ret > 0 then
				AddItemListToPlayer(sceneId,selfId)
				DelItem(sceneId,selfId,x570005_g_ItemId,x570005_g_ItemNum)
			else
			BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"��Ʒ���������޷������Ʒ��")
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)
			end	
		elseif weiyi == 1 then
			if have < 1 then
				BeginAddItem(sceneId)
					AddItem( sceneId,x570005_g_ItemBonus[zhiye+1].id,x570005_g_ItemBonus[1].num)
				local ret = EndAddItem(sceneId,selfId)
				if ret > 0 then
					AddItemListToPlayer(sceneId,selfId)
					DelItem(sceneId,selfId,x570005_g_ItemId,x570005_g_ItemNum)
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
		
function x570005_ProcAcceptCheck( sceneId, selfId, NPCId )
	return 1

end


--**********************************
--����
--**********************************
function x570005_ProcQuestAbandon( sceneId, selfId, MissionId )

end

--**********************************
--����
--**********************************
function x570005_OnContinue( sceneId, selfId, targetId )

end

--**********************************
--����Ƿ�����ύ
--**********************************
function x570005_CheckSubmit( sceneId, selfId )

end

--**********************************
--�ύ
--**********************************
function x570005_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )

end

--**********************************
--ɱ����������
--**********************************
function x570005_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )

end

--**********************************
--���������¼�
--**********************************
function x570005_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

--**********************************
--���߸ı�
--**********************************
function x570005_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end
