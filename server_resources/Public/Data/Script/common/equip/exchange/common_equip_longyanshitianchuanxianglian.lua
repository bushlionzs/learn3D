--�һ��촫����
--MisDescBegin
--�ű���
x570030_g_ScriptId = 570030

--�����Ƕ�̬**************************************************************

--�����ı�����
x570030_g_MissionName = "������ʯ���һ��촫����"
x570030_g_EXCName = "�һ��촫����"		--�һ����� ����������ʾ���������ʹ��
x570030_g_EXCItemName = "��֮����ʯ"		--�һ�����Ҫ�ĵ�������
x570030_g_ItemId = 11050004    --�������ID
x570030_g_ItemNum = 200          --��������  
x570030_g_ItemBonus =	{{id=10244004,num=1},{id=10244014,num=1},{id=10244024,num=1},{id=10244034,num=1},{id=10244044,num=1},{id=10244054,num=1},{id=10249221,num=1},{id=10249225,num=1},{id=10249229,num=1},{id=10249233,num=1},{id=10249237,num=1},{id=10249241,num=1}}
x570030_g_MissionInfo = format("\t��ȷ��Ҫʹ��#G%s#W%s��\n\t����Ҫ#R%d��#W#G%s#W��",x570030_g_EXCItemName,x570030_g_EXCName,x570030_g_ItemNum,x570030_g_EXCItemName)	--����˵������
x570030_g_MissionError = format("\t��û���㹻������%s���޷�%s��",x570030_g_EXCItemName,x570030_g_EXCName)	--������Ϣ

--MisDescEnd
--**********************************
--������ں���
--**********************************
function x570030_ProcEventEntry( sceneId, selfId, targetId ,scriptId,seleteId)	--����������ִ�д˽ű�

	local zhiye = GetZhiye(sceneId, selfId)
	local longyannum = GetItemCount(sceneId, selfId, x570030_g_ItemId)
	local strText = format("\t��������#R%d��#W#G%s#W��",longyannum,x570030_g_EXCItemName)
		BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"#Y"..x570030_g_MissionName)
			AddQuestText(sceneId,x570030_g_MissionInfo)
			AddQuestText(sceneId,strText)
			AddQuestItemBonus(sceneId, x570030_g_ItemBonus[zhiye+1].id,x570030_g_ItemBonus[1].num)
		EndQuestEvent()
		DispatchQuestInfo(sceneId, selfId, targetId, x570030_g_ScriptId,-1)

end

--**********************************
--�о��¼�
--**********************************
function x570030_ProcEnumEvent( sceneId, selfId, targetId, MissionId )

	AddQuestNumText(sceneId,x570030_g_ScriptId,x570030_g_MissionName,3);
	
end



--**********************************
--����
--**********************************
function x570030_ProcAccept( sceneId, selfId )
	
	local Num = GetItemCount( sceneId, selfId, x570030_g_ItemId )

	if Num < x570030_g_ItemNum then 
		BeginQuestEvent(sceneId)
			AddQuestText(sceneId,x570030_g_MissionError)
		EndQuestEvent()
		DispatchQuestTips(sceneId, selfId)
	end
	
	if Num >= x570030_g_ItemNum then 

		local zhiye = GetZhiye(sceneId, selfId)
		local weiyi = ItemIsUnique(sceneId,selfId, x570030_g_ItemBonus[zhiye+1].id)
		local have  = HaveItem( sceneId,selfId,x570030_g_ItemBonus[zhiye+1].id)
		
		if weiyi ~= 1  then
			BeginAddItem(sceneId)
				AddItem( sceneId,x570030_g_ItemBonus[zhiye+1].id,x570030_g_ItemBonus[1].num)
			local ret = EndAddItem(sceneId,selfId)
			if ret > 0 then
				AddItemListToPlayer(sceneId,selfId)
				DelItem(sceneId,selfId,x570030_g_ItemId,x570030_g_ItemNum)
			else
			BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"��Ʒ���������޷������Ʒ��")
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)
			end	
		elseif weiyi == 1 then
			if have < 1 then
				BeginAddItem(sceneId)
					AddItem( sceneId,x570030_g_ItemBonus[zhiye+1].id,x570030_g_ItemBonus[1].num)
				local ret = EndAddItem(sceneId,selfId)
				if ret > 0 then
					AddItemListToPlayer(sceneId,selfId)
					DelItem(sceneId,selfId,x570030_g_ItemId,x570030_g_ItemNum)
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
		
function x570030_ProcAcceptCheck( sceneId, selfId, NPCId )
	return 1

end


--**********************************
--����
--**********************************
function x570030_ProcQuestAbandon( sceneId, selfId, MissionId )

end

--**********************************
--����
--**********************************
function x570030_OnContinue( sceneId, selfId, targetId )

end

--**********************************
--����Ƿ�����ύ
--**********************************
function x570030_CheckSubmit( sceneId, selfId )

end

--**********************************
--�ύ
--**********************************
function x570030_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )

end

--**********************************
--ɱ����������
--**********************************
function x570030_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )

end

--**********************************
--���������¼�
--**********************************
function x570030_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

--**********************************
--���߸ı�
--**********************************
function x570030_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end
