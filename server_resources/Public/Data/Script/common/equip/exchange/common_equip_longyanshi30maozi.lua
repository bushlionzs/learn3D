--�һ�30��ñ��
--MisDescBegin
--�ű���
x570001_g_ScriptId = 570001

--�����Ƕ�̬**************************************************************

--�����ı�����
x570001_g_MissionName = "������ʯ���һ�����ñ��"   --�������
x570001_g_EXCName = "�һ�����ñ��"		--�һ����� ����������ʾ���������ʹ��
x570001_g_EXCItemName = "��������ʯ"		--�һ�����Ҫ�ĵ�������
x570001_g_ItemId = 11050001	--�������ID
x570001_g_ItemNum = 65				--��������
x570001_g_ItemBonus = {{id=10204001,num=1},{id=10204011,num=1},{id=10204021,num=1},{id=10204031,num=1},{id=10204041,num=1},{id=10204051,num=1},{id=10204061,num=1},{id=10204071,num=1},{id=10204081,num=1},{id=10204091,num=1},{id=10204101,num=1},{id=10204111,num=1}}		--������Ʒ
x570001_g_MissionInfo = format("\t��ȷ��Ҫʹ��#G%s#W%s��\n\t����Ҫ#R%d��#W#G%s#W��",x570001_g_EXCItemName,x570001_g_EXCName,x570001_g_ItemNum,x570001_g_EXCItemName)	--����˵������
x570001_g_MissionError = format("\t��û���㹻������%s���޷�%s��",x570001_g_EXCItemName,x570001_g_EXCName)	--������Ϣ

--MisDescEnd
--**********************************
--������ں���
--**********************************
function x570001_ProcEventEntry( sceneId, selfId, targetId ,scriptId,seleteId)	--����������ִ�д˽ű�

	local zhiye = GetZhiye(sceneId, selfId)
	local longyannum = GetItemCount(sceneId, selfId, x570001_g_ItemId)
	local strText = format("\t��������#R%d��#W#G%s#W��",longyannum,x570001_g_EXCItemName)
		BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"#Y"..x570001_g_MissionName)
			AddQuestText(sceneId,x570001_g_MissionInfo)
			AddQuestText(sceneId,strText)
			AddQuestItemBonus(sceneId, x570001_g_ItemBonus[zhiye+1].id,x570001_g_ItemBonus[1].num)
		EndQuestEvent()
		DispatchQuestInfo(sceneId, selfId, targetId, x570001_g_ScriptId,-1)

end

--**********************************
--�о��¼�
--**********************************
function x570001_ProcEnumEvent( sceneId, selfId, targetId, MissionId )

	AddQuestNumText(sceneId,x570001_g_ScriptId,x570001_g_MissionName,3);
	
end



--**********************************
--����
--**********************************
function x570001_ProcAccept( sceneId, selfId )
	
	local Num = GetItemCount( sceneId, selfId, x570001_g_ItemId )

	if Num < x570001_g_ItemNum then 
		BeginQuestEvent(sceneId)
			AddQuestText(sceneId,x570001_g_MissionError)
		EndQuestEvent()
		DispatchQuestTips(sceneId, selfId)
	end
	
	if Num >= x570001_g_ItemNum then 

		local zhiye = GetZhiye(sceneId, selfId)
		local weiyi = ItemIsUnique(sceneId,selfId, x570001_g_ItemBonus[zhiye+1].id)
		local have  = HaveItem( sceneId,selfId,x570001_g_ItemBonus[zhiye+1].id)
		
		if weiyi ~= 1  then
			BeginAddItem(sceneId)
				AddItem( sceneId,x570001_g_ItemBonus[zhiye+1].id,x570001_g_ItemBonus[1].num)
			local ret = EndAddItem(sceneId,selfId)
			if ret > 0 then
				AddItemListToPlayer(sceneId,selfId)
				DelItem(sceneId,selfId,x570001_g_ItemId,x570001_g_ItemNum)
			else
			BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"��Ʒ���������޷������Ʒ��")
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)
			end	
		elseif weiyi == 1 then
			if have < 1 then
				BeginAddItem(sceneId)
					AddItem( sceneId,x570001_g_ItemBonus[zhiye+1].id,x570001_g_ItemBonus[1].num)
				local ret = EndAddItem(sceneId,selfId)
				if ret > 0 then
					AddItemListToPlayer(sceneId,selfId)
					DelItem(sceneId,selfId,x570001_g_ItemId,x570001_g_ItemNum)
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
		
function x570001_ProcAcceptCheck( sceneId, selfId, NPCId )
	return 1

end


--**********************************
--����
--**********************************
function x570001_ProcQuestAbandon( sceneId, selfId, MissionId )

end

--**********************************
--����
--**********************************
function x570001_OnContinue( sceneId, selfId, targetId )

end

--**********************************
--����Ƿ�����ύ
--**********************************
function x570001_CheckSubmit( sceneId, selfId )

end

--**********************************
--�ύ
--**********************************
function x570001_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )

end

--**********************************
--ɱ����������
--**********************************
function x570001_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )

end

--**********************************
--���������¼�
--**********************************
function x570001_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

--**********************************
--���߸ı�
--**********************************
function x570001_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end
