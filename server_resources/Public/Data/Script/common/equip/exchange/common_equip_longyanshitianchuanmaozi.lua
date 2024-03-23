--�һ��촫ñ��
--MisDescBegin
--�ű���
x570029_g_ScriptId = 570029

--�����Ƕ�̬**************************************************************

--�����ı�����
x570029_g_MissionName = "������ʯ���һ��촫ñ��"   --�������
x570029_g_EXCName = "�һ��촫ñ��"		--�һ����� ����������ʾ���������ʹ��
x570029_g_EXCItemName = "��֮����ʯ"		--�һ�����Ҫ�ĵ�������
x570029_g_ItemId = 11050004	--�������ID
x570029_g_ItemNum = 350				--��������
x570029_g_ItemBonus = {{id=10204004,num=1},{id=10204014,num=1},{id=10204024,num=1},{id=10204034,num=1},{id=10204044,num=1},{id=10204054,num=1},{id=10204064,num=1},{id=10204074,num=1},{id=10204084,num=1},{id=10204094,num=1},{id=10204104,num=1},{id=10204114,num=1}}		--������Ʒ
x570029_g_MissionInfo = format("\t��ȷ��Ҫʹ��#G%s#W%s��\n\t����Ҫ#R%d��#W#G%s#W��",x570029_g_EXCItemName,x570029_g_EXCName,x570029_g_ItemNum,x570029_g_EXCItemName)	--����˵������
x570029_g_MissionError = format("\t��û���㹻������%s���޷�%s��",x570029_g_EXCItemName,x570029_g_EXCName)	--������Ϣ

--MisDescEnd
--**********************************
--������ں���
--**********************************
function x570029_ProcEventEntry( sceneId, selfId, targetId ,scriptId,seleteId)	--����������ִ�д˽ű�

	local zhiye = GetZhiye(sceneId, selfId)
	local longyannum = GetItemCount(sceneId, selfId, x570029_g_ItemId)
	local strText = format("\t��������#R%d��#W#G%s#W��",longyannum,x570029_g_EXCItemName)
		BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"#Y"..x570029_g_MissionName)
			AddQuestText(sceneId,x570029_g_MissionInfo)
			AddQuestText(sceneId,strText)
			AddQuestItemBonus(sceneId, x570029_g_ItemBonus[zhiye+1].id,x570029_g_ItemBonus[1].num)
		EndQuestEvent()
		DispatchQuestInfo(sceneId, selfId, targetId, x570029_g_ScriptId,-1)

end

--**********************************
--�о��¼�
--**********************************
function x570029_ProcEnumEvent( sceneId, selfId, targetId, MissionId )

	AddQuestNumText(sceneId,x570029_g_ScriptId,x570029_g_MissionName,3);
	
end



--**********************************
--����
--**********************************
function x570029_ProcAccept( sceneId, selfId )
	
	local Num = GetItemCount( sceneId, selfId, x570029_g_ItemId )

	if Num < x570029_g_ItemNum then 
		BeginQuestEvent(sceneId)
			AddQuestText(sceneId,x570029_g_MissionError)
		EndQuestEvent()
		DispatchQuestTips(sceneId, selfId)
	end
	
	if Num >= x570029_g_ItemNum then 

		local zhiye = GetZhiye(sceneId, selfId)
		local weiyi = ItemIsUnique(sceneId,selfId, x570029_g_ItemBonus[zhiye+1].id)
		local have  = HaveItem( sceneId,selfId,x570029_g_ItemBonus[zhiye+1].id)
		
		if weiyi ~= 1  then
			BeginAddItem(sceneId)
				AddItem( sceneId,x570029_g_ItemBonus[zhiye+1].id,x570029_g_ItemBonus[1].num)
			local ret = EndAddItem(sceneId,selfId)
			if ret > 0 then
				AddItemListToPlayer(sceneId,selfId)
				DelItem(sceneId,selfId,x570029_g_ItemId,x570029_g_ItemNum)
			else
			BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"��Ʒ���������޷������Ʒ��")
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)
			end	
		elseif weiyi == 1 then
			if have < 1 then
				BeginAddItem(sceneId)
					AddItem( sceneId,x570029_g_ItemBonus[zhiye+1].id,x570029_g_ItemBonus[1].num)
				local ret = EndAddItem(sceneId,selfId)
				if ret > 0 then
					AddItemListToPlayer(sceneId,selfId)
					DelItem(sceneId,selfId,x570029_g_ItemId,x570029_g_ItemNum)
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
		
function x570029_ProcAcceptCheck( sceneId, selfId, NPCId )
	return 1

end


--**********************************
--����
--**********************************
function x570029_ProcQuestAbandon( sceneId, selfId, MissionId )

end

--**********************************
--����
--**********************************
function x570029_OnContinue( sceneId, selfId, targetId )

end

--**********************************
--����Ƿ�����ύ
--**********************************
function x570029_CheckSubmit( sceneId, selfId )

end

--**********************************
--�ύ
--**********************************
function x570029_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )

end

--**********************************
--ɱ����������
--**********************************
function x570029_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )

end

--**********************************
--���������¼�
--**********************************
function x570029_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

--**********************************
--���߸ı�
--**********************************
function x570029_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end
