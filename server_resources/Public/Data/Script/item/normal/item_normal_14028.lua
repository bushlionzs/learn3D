--�巬��һ��ر���
--MisDescBegin
--�ű���
x414028_g_ScriptId = 414028

--�����Ƕ�̬**************************************************************

--�����ı�����
x414028_g_MissionName = "�巬��һ��ر���"   --�������
x414028_g_EXCName = "�巬��һ��ر���"		--�һ����� ����������ʾ���������ʹ��
x414028_g_EXCItemName = "�巬��"		--�һ�����Ҫ�ĵ�������
x414028_g_ItemId = 11990012	--�������ID
x414028_g_ItemNum = 1				--��������
x414028_g_ItemBonus = {{id=11990015,num=4},{id=11990015,num=4},{id=11990015,num=4},{id=11990015,num=4},{id=11990015,num=4},{id=11990015,num=4},{id=11990015,num=4},{id=11990015,num=4},{id=11990015,num=4},{id=11990015,num=4},{id=11990015,num=4},{id=11990015,num=4}}		--������Ʒ
x414028_g_MissionInfo = format("\n\t�������ж����#G�巬��#W������������Խ�#R%d��#W#G�巬��#W�һ�Ϊ#R4��#W#G�ر���#W��",x414028_g_ItemNum)	--����˵������
x414028_g_MissionError = format("\t��û��%s���޷���%s��",x414028_g_EXCItemName,x414028_g_EXCName)	--������Ϣ

--MisDescEnd
--**********************************
--������ں���
--**********************************
function x414028_ProcEventEntry( sceneId, selfId, targetId ,scriptId,seleteId)	--����������ִ�д˽ű�

	local zhiye = GetZhiye(sceneId, selfId)
	local longyannum = GetItemCount(sceneId, selfId, x414028_g_ItemId)
	local strText = format("\n\t��ȷ��Ҫʹ��#G�巬��#W�һ�#G�ر���#W��")
		BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"#Y"..x414028_g_MissionName)
			AddQuestText(sceneId,x414028_g_MissionInfo)
			AddQuestText(sceneId,strText)
			AddQuestItemBonus(sceneId, x414028_g_ItemBonus[zhiye+1].id,x414028_g_ItemBonus[1].num)
		EndQuestEvent()
		DispatchQuestInfo(sceneId, selfId, targetId, x414028_g_ScriptId,-1)

end

--**********************************
--�о��¼�
--**********************************
function x414028_ProcEnumEvent( sceneId, selfId, targetId, MissionId )

	AddQuestNumText(sceneId,x414028_g_ScriptId,x414028_g_MissionName,3);
	
end



--**********************************
--����
--**********************************
function x414028_ProcAccept( sceneId, selfId )
	
	local Num = GetItemCount( sceneId, selfId, x414028_g_ItemId )

	if Num < x414028_g_ItemNum then 
		BeginQuestEvent(sceneId)
			AddQuestText(sceneId,x414028_g_MissionError)
		EndQuestEvent()
		DispatchQuestTips(sceneId, selfId)
	end
	
	if Num >= x414028_g_ItemNum then 

		local zhiye = GetZhiye(sceneId, selfId)
		local weiyi = ItemIsUnique(sceneId,selfId, x414028_g_ItemBonus[zhiye+1].id)
		local have  = HaveItem( sceneId,selfId,x414028_g_ItemBonus[zhiye+1].id)
		
		if weiyi ~= 1  then
			BeginAddItem(sceneId)
				AddItem( sceneId,x414028_g_ItemBonus[zhiye+1].id,x414028_g_ItemBonus[1].num)
			local ret = EndAddItem(sceneId,selfId)
			if ret > 0 then
				AddItemListToPlayer(sceneId,selfId)
				DelItem(sceneId,selfId,x414028_g_ItemId,x414028_g_ItemNum)
			else
			BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"��Ʒ���������޷������Ʒ��")
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)
			end	
		elseif weiyi == 1 then
			if have < 1 then
				BeginAddItem(sceneId)
					AddItem( sceneId,x414028_g_ItemBonus[zhiye+1].id,x414028_g_ItemBonus[1].num)
				local ret = EndAddItem(sceneId,selfId)
				if ret > 0 then
					AddItemListToPlayer(sceneId,selfId)
					DelItem(sceneId,selfId,x414028_g_ItemId,x414028_g_ItemNum)
				else
				BeginQuestEvent(sceneId)
					AddQuestText(sceneId,"��Ʒ���������޷������Ʒ��")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				end	
			else
				BeginQuestEvent(sceneId)
					AddQuestText(sceneId,"���޷��һ�����Ĳر��")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
			end	
		end
	end
end
		
function x414028_ProcAcceptCheck( sceneId, selfId, NPCId )
	return 1

end


--**********************************
--����
--**********************************
function x414028_ProcQuestAbandon( sceneId, selfId, MissionId )

end

--**********************************
--����
--**********************************
function x414028_OnContinue( sceneId, selfId, targetId )

end

--**********************************
--����Ƿ�����ύ
--**********************************
function x414028_CheckSubmit( sceneId, selfId )

end

--**********************************
--�ύ
--**********************************
function x414028_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )

end

--**********************************
--ɱ����������
--**********************************
function x414028_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )

end

--**********************************
--���������¼�
--**********************************
function x414028_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

--**********************************
--���߸ı�
--**********************************
function x414028_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end
