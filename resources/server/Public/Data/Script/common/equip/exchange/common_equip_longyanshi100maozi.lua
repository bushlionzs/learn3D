--�һ�100��ñ��
--MisDescBegin
--�ű���
x570046_g_ScriptId = 570046

--�����Ƕ�̬**************************************************************

--�����ı�����
x570046_g_MissionName = "������ʯ���һ�ڤ��ñ��"
x570046_g_EXCName = "�һ�ڤ��ñ��"		--�һ����� ����������ʾ���������ʹ��
x570046_g_EXCItemName = "ڤ֮����ʯ"		--�һ�����Ҫ�ĵ�������
x570046_g_ItemId = 11050005           --�������ID
x570046_g_ItemNum = 410                 --��������  
x570046_g_ItemBonus = {{id=10209500,num=1},{id=10209501,num=1},{id=10209502,num=1},{id=10209503,num=1},{id=10209504,num=1},{id=10209505,num=1},{id=10209506,num=1},{id=10209507,num=1},{id=10209508,num=1},{id=10209509,num=1},{id=10209510,num=1},{id=10209511,num=1}}
x570046_g_MissionInfo = format("\t��ȷ��Ҫʹ��#G%s#W%s��\n\t����Ҫ#R%d��#W#G%s#W��",x570046_g_EXCItemName,x570046_g_EXCName,x570046_g_ItemNum,x570046_g_EXCItemName)	--����˵������
x570046_g_MissionError = format("\t��û���㹻������%s���޷�%s��",x570046_g_EXCItemName,x570046_g_EXCName)	--������Ϣ

--MisDescEnd
--**********************************
--������ں���
--**********************************
function x570046_ProcEventEntry( sceneId, selfId, targetId ,scriptId,seleteId)	--����������ִ�д˽ű�

	local zhiye = GetZhiye(sceneId, selfId)
	local longyannum = GetItemCount(sceneId, selfId, x570046_g_ItemId)
	local strText = format("\t��������#R%d��#W#G%s#W��",longyannum,x570046_g_EXCItemName)
		BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"#Y"..x570046_g_MissionName)
			AddQuestText(sceneId,x570046_g_MissionInfo)
			AddQuestText(sceneId,strText)
			AddQuestItemBonus(sceneId, x570046_g_ItemBonus[zhiye+1].id,x570046_g_ItemBonus[1].num)
		EndQuestEvent()
		DispatchQuestInfo(sceneId, selfId, targetId, x570046_g_ScriptId,-1)

end

--**********************************
--�о��¼�
--**********************************
function x570046_ProcEnumEvent( sceneId, selfId, targetId, MissionId )

	AddQuestNumText(sceneId,x570046_g_ScriptId,x570046_g_MissionName,3);
	
end



--**********************************
--����
--**********************************
function x570046_ProcAccept( sceneId, selfId )
	
	local Num = GetItemCount( sceneId, selfId, x570046_g_ItemId )

	if Num < x570046_g_ItemNum then 
		BeginQuestEvent(sceneId)
			AddQuestText(sceneId,x570046_g_MissionError)
		EndQuestEvent()
		DispatchQuestTips(sceneId, selfId)
	end
	
	if Num >= x570046_g_ItemNum then 

		local zhiye = GetZhiye(sceneId, selfId)
		local weiyi = ItemIsUnique(sceneId,selfId, x570046_g_ItemBonus[zhiye+1].id)
		local have  = HaveItem( sceneId,selfId,x570046_g_ItemBonus[zhiye+1].id)
		
		if weiyi ~= 1  then
			BeginAddItem(sceneId)
				AddItem( sceneId,x570046_g_ItemBonus[zhiye+1].id,x570046_g_ItemBonus[1].num)
			local ret = EndAddItem(sceneId,selfId)
			if ret > 0 then
				AddItemListToPlayer(sceneId,selfId)
				DelItem(sceneId,selfId,x570046_g_ItemId,x570046_g_ItemNum)
			else
			BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"��Ʒ���������޷������Ʒ��")
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)
			end	
		elseif weiyi == 1 then
			if have < 1 then
				BeginAddItem(sceneId)
					AddItem( sceneId,x570046_g_ItemBonus[zhiye+1].id,x570046_g_ItemBonus[1].num)
				local ret = EndAddItem(sceneId,selfId)
				if ret > 0 then
					AddItemListToPlayer(sceneId,selfId)
					DelItem(sceneId,selfId,x570046_g_ItemId,x570046_g_ItemNum)
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
		
function x570046_ProcAcceptCheck( sceneId, selfId, NPCId )
	return 1

end


--**********************************
--����
--**********************************
function x570046_ProcQuestAbandon( sceneId, selfId, MissionId )

end

--**********************************
--����
--**********************************
function x570046_OnContinue( sceneId, selfId, targetId )

end

--**********************************
--����Ƿ�����ύ
--**********************************
function x570046_CheckSubmit( sceneId, selfId )

end

--**********************************
--�ύ
--**********************************
function x570046_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )

end

--**********************************
--ɱ����������
--**********************************
function x570046_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )

end

--**********************************
--���������¼�
--**********************************
function x570046_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

--**********************************
--���߸ı�
--**********************************
function x570046_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end
