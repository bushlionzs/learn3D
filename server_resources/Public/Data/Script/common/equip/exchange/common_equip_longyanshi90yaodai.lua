--�һ�90������
--MisDescBegin
--�ű���
x570009_g_ScriptId = 570009

--�����Ƕ�̬**************************************************************

--�����ı�����
x570009_g_MissionName="������ʯ���һ�������"
x570009_g_EXCName = "�һ�������"		--�һ����� ����������ʾ���������ʹ��
x570009_g_EXCItemName = "�߼�����ʯ"		--�һ�����Ҫ�ĵ�������
x570009_g_ItemId = 11050003           --�������ID
x570009_g_ItemNum = 210                 --��������  
x570009_g_ItemBonus	=	{{id=10264003,num=1},{id=10264013,num=1},{id=10264023,num=1},{id=10264033,num=1},{id=10264043,num=1},{id=10264053,num=1},{id=10269220,num=1},{id=10269224,num=1},{id=10269228,num=1},{id=10269232,num=1},{id=10269236,num=1},{id=10269240,num=1}}
x570009_g_MissionInfo = format("\t��ȷ��Ҫʹ��#G%s#W%s��\n\t����Ҫ#R%d��#W#G%s#W��",x570009_g_EXCItemName,x570009_g_EXCName,x570009_g_ItemNum,x570009_g_EXCItemName)	--����˵������
x570009_g_MissionError = format("\t��û���㹻������%s���޷�%s��",x570009_g_EXCItemName,x570009_g_EXCName)	--������Ϣ

--MisDescEnd
--**********************************
--������ں���
--**********************************
function x570009_ProcEventEntry( sceneId, selfId, targetId ,scriptId,seleteId)	--����������ִ�д˽ű�

	local zhiye = GetZhiye(sceneId, selfId)
	local longyannum = GetItemCount(sceneId, selfId, x570009_g_ItemId)
	local strText = format("\t��������#R%d��#W#G%s#W��",longyannum,x570009_g_EXCItemName)
		BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"#Y"..x570009_g_MissionName)
			AddQuestText(sceneId,x570009_g_MissionInfo)
			AddQuestText(sceneId,strText)
			AddQuestItemBonus(sceneId, x570009_g_ItemBonus[zhiye+1].id,x570009_g_ItemBonus[1].num)
		EndQuestEvent()
		DispatchQuestInfo(sceneId, selfId, targetId, x570009_g_ScriptId,-1)

end

--**********************************
--�о��¼�
--**********************************
function x570009_ProcEnumEvent( sceneId, selfId, targetId, MissionId )

	AddQuestNumText(sceneId,x570009_g_ScriptId,x570009_g_MissionName,3);
	
end



--**********************************
--����
--**********************************
function x570009_ProcAccept( sceneId, selfId )
	
	local Num = GetItemCount( sceneId, selfId, x570009_g_ItemId )

	if Num < x570009_g_ItemNum then 
		BeginQuestEvent(sceneId)
			AddQuestText(sceneId,x570009_g_MissionError)
		EndQuestEvent()
		DispatchQuestTips(sceneId, selfId)
	end
	
	if Num >= x570009_g_ItemNum then 

		local zhiye = GetZhiye(sceneId, selfId)
		local weiyi = ItemIsUnique(sceneId,selfId, x570009_g_ItemBonus[zhiye+1].id)
		local have  = HaveItem( sceneId,selfId,x570009_g_ItemBonus[zhiye+1].id)
		
		if weiyi ~= 1  then
			BeginAddItem(sceneId)
				AddItem( sceneId,x570009_g_ItemBonus[zhiye+1].id,x570009_g_ItemBonus[1].num)
			local ret = EndAddItem(sceneId,selfId)
			if ret > 0 then
				AddItemListToPlayer(sceneId,selfId)
				DelItem(sceneId,selfId,x570009_g_ItemId,x570009_g_ItemNum)
			else
			BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"��Ʒ���������޷������Ʒ��")
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)
			end	
		elseif weiyi == 1 then
			if have < 1 then
				BeginAddItem(sceneId)
					AddItem( sceneId,x570009_g_ItemBonus[zhiye+1].id,x570009_g_ItemBonus[1].num)
				local ret = EndAddItem(sceneId,selfId)
				if ret > 0 then
					AddItemListToPlayer(sceneId,selfId)
					DelItem(sceneId,selfId,x570009_g_ItemId,x570009_g_ItemNum)
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
		
function x570009_ProcAcceptCheck( sceneId, selfId, NPCId )
	return 1

end


--**********************************
--����
--**********************************
function x570009_ProcQuestAbandon( sceneId, selfId, MissionId )

end

--**********************************
--����
--**********************************
function x570009_OnContinue( sceneId, selfId, targetId )

end

--**********************************
--����Ƿ�����ύ
--**********************************
function x570009_CheckSubmit( sceneId, selfId )

end

--**********************************
--�ύ
--**********************************
function x570009_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )

end

--**********************************
--ɱ����������
--**********************************
function x570009_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )

end

--**********************************
--���������¼�
--**********************************
function x570009_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

--**********************************
--���߸ı�
--**********************************
function x570009_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end
