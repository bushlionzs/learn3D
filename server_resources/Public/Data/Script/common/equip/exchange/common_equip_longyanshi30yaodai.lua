--�һ�30������
--MisDescBegin
--�ű���
x570003_g_ScriptId = 570003

--�����Ƕ�̬**************************************************************

--�����ı�����
x570003_g_MissionName="������ʯ���һ���������"
x570003_g_EXCName = "�һ���������"		--�һ����� ����������ʾ���������ʹ��
x570003_g_EXCItemName = "��������ʯ"		--�һ�����Ҫ�ĵ�������
x570003_g_ItemId = 11050001        --�������ID
x570003_g_ItemNum = 40              --��������
x570003_g_ItemBonus	=	{{id=10264001,num=1},{id=10264011,num=1},{id=10264021,num=1},{id=10264031,num=1},{id=10264041,num=1},{id=10264051,num=1},{id=10269218,num=1},{id=10269222,num=1},{id=10269226,num=1},{id=10269230,num=1},{id=10269234,num=1},{id=10269238,num=1}}
x570003_g_MissionInfo = format("\t��ȷ��Ҫʹ��#G%s#W%s��\n\t����Ҫ#R%d��#W#G%s#W��",x570003_g_EXCItemName,x570003_g_EXCName,x570003_g_ItemNum,x570003_g_EXCItemName)	--����˵������
x570003_g_MissionError = format("\t��û���㹻������%s���޷�%s��",x570003_g_EXCItemName,x570003_g_EXCName)	--������Ϣ

--MisDescEnd
--**********************************
--������ں���
--**********************************
function x570003_ProcEventEntry( sceneId, selfId, targetId ,scriptId,seleteId)	--����������ִ�д˽ű�

	local zhiye = GetZhiye(sceneId, selfId)
	local longyannum = GetItemCount(sceneId, selfId, x570003_g_ItemId)
	local strText = format("\t��������#R%d��#W#G%s#W��",longyannum,x570003_g_EXCItemName)
		BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"#Y"..x570003_g_MissionName)
			AddQuestText(sceneId,x570003_g_MissionInfo)
			AddQuestText(sceneId,strText)
			AddQuestItemBonus(sceneId, x570003_g_ItemBonus[zhiye+1].id,x570003_g_ItemBonus[1].num)
		EndQuestEvent()
		DispatchQuestInfo(sceneId, selfId, targetId, x570003_g_ScriptId,-1)

end

--**********************************
--�о��¼�
--**********************************
function x570003_ProcEnumEvent( sceneId, selfId, targetId, MissionId )

	AddQuestNumText(sceneId,x570003_g_ScriptId,x570003_g_MissionName,3);
	
end



--**********************************
--����
--**********************************
function x570003_ProcAccept( sceneId, selfId )
	
	local Num = GetItemCount( sceneId, selfId, x570003_g_ItemId )

	if Num < x570003_g_ItemNum then 
		BeginQuestEvent(sceneId)
			AddQuestText(sceneId,x570003_g_MissionError)
		EndQuestEvent()
		DispatchQuestTips(sceneId, selfId)
	end
	
	if Num >= x570003_g_ItemNum then 

		local zhiye = GetZhiye(sceneId, selfId)
		local weiyi = ItemIsUnique(sceneId,selfId, x570003_g_ItemBonus[zhiye+1].id)
		local have  = HaveItem( sceneId,selfId,x570003_g_ItemBonus[zhiye+1].id)
		
		if weiyi ~= 1  then
			BeginAddItem(sceneId)
				AddItem( sceneId,x570003_g_ItemBonus[zhiye+1].id,x570003_g_ItemBonus[1].num)
			local ret = EndAddItem(sceneId,selfId)
			if ret > 0 then
				AddItemListToPlayer(sceneId,selfId)
				DelItem(sceneId,selfId,x570003_g_ItemId,x570003_g_ItemNum)
			else
			BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"��Ʒ���������޷������Ʒ��")
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)
			end	
		elseif weiyi == 1 then
			if have < 1 then
				BeginAddItem(sceneId)
					AddItem( sceneId,x570003_g_ItemBonus[zhiye+1].id,x570003_g_ItemBonus[1].num)
				local ret = EndAddItem(sceneId,selfId)
				if ret > 0 then
					AddItemListToPlayer(sceneId,selfId)
					DelItem(sceneId,selfId,x570003_g_ItemId,x570003_g_ItemNum)
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
		
function x570003_ProcAcceptCheck( sceneId, selfId, NPCId )
	return 1

end


--**********************************
--����
--**********************************
function x570003_ProcQuestAbandon( sceneId, selfId, MissionId )

end

--**********************************
--����
--**********************************
function x570003_OnContinue( sceneId, selfId, targetId )

end

--**********************************
--����Ƿ�����ύ
--**********************************
function x570003_CheckSubmit( sceneId, selfId )

end

--**********************************
--�ύ
--**********************************
function x570003_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )

end

--**********************************
--ɱ����������
--**********************************
function x570003_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )

end

--**********************************
--���������¼�
--**********************************
function x570003_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

--**********************************
--���߸ı�
--**********************************
function x570003_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end
