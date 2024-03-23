--�һ�60������
--MisDescBegin
--�ű���
x570006_g_ScriptId = 570006

--�����Ƕ�̬**************************************************************

--�����ı�����
x570006_g_MissionName="������ʯ���һ���������"
x570006_g_EXCName = "�һ���������"		--�һ����� ����������ʾ���������ʹ��
x570006_g_EXCItemName = "�м�����ʯ"		--�һ�����Ҫ�ĵ�������
x570006_g_ItemId = 11050002         --�������ID
x570006_g_ItemNum = 80  							--��������
x570006_g_ItemBonus	=	{{id=10264002,num=1},{id=10264012,num=1},{id=10264022,num=1},{id=10264032,num=1},{id=10264042,num=1},{id=10264052,num=1},{id=10269219,num=1},{id=10269223,num=1},{id=10269227,num=1},{id=10269231,num=1},{id=10269235,num=1},{id=10269239,num=1}}
x570006_g_MissionInfo = format("\t��ȷ��Ҫʹ��#G%s#W%s��\n\t����Ҫ#R%d��#W#G%s#W��",x570006_g_EXCItemName,x570006_g_EXCName,x570006_g_ItemNum,x570006_g_EXCItemName)	--����˵������
x570006_g_MissionError = format("\t��û���㹻������%s���޷�%s��",x570006_g_EXCItemName,x570006_g_EXCName)	--������Ϣ

--MisDescEnd
--**********************************
--������ں���
--**********************************
function x570006_ProcEventEntry( sceneId, selfId, targetId ,scriptId,seleteId)	--����������ִ�д˽ű�

	local zhiye = GetZhiye(sceneId, selfId)
	local longyannum = GetItemCount(sceneId, selfId, x570006_g_ItemId)
	local strText = format("\t��������#R%d��#W#G%s#W��",longyannum,x570006_g_EXCItemName)
		BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"#Y"..x570006_g_MissionName)
			AddQuestText(sceneId,x570006_g_MissionInfo)
			AddQuestText(sceneId,strText)
			AddQuestItemBonus(sceneId, x570006_g_ItemBonus[zhiye+1].id,x570006_g_ItemBonus[1].num)
		EndQuestEvent()
		DispatchQuestInfo(sceneId, selfId, targetId, x570006_g_ScriptId,-1)

end

--**********************************
--�о��¼�
--**********************************
function x570006_ProcEnumEvent( sceneId, selfId, targetId, MissionId )

	AddQuestNumText(sceneId,x570006_g_ScriptId,x570006_g_MissionName,3);
	
end



--**********************************
--����
--**********************************
function x570006_ProcAccept( sceneId, selfId )
	
	local Num = GetItemCount( sceneId, selfId, x570006_g_ItemId )

	if Num < x570006_g_ItemNum then 
		BeginQuestEvent(sceneId)
			AddQuestText(sceneId,x570006_g_MissionError)
		EndQuestEvent()
		DispatchQuestTips(sceneId, selfId)
	end
	
	if Num >= x570006_g_ItemNum then 

		local zhiye = GetZhiye(sceneId, selfId)
		local weiyi = ItemIsUnique(sceneId,selfId, x570006_g_ItemBonus[zhiye+1].id)
		local have  = HaveItem( sceneId,selfId,x570006_g_ItemBonus[zhiye+1].id)
		
		if weiyi ~= 1  then
			BeginAddItem(sceneId)
				AddItem( sceneId,x570006_g_ItemBonus[zhiye+1].id,x570006_g_ItemBonus[1].num)
			local ret = EndAddItem(sceneId,selfId)
			if ret > 0 then
				AddItemListToPlayer(sceneId,selfId)
				DelItem(sceneId,selfId,x570006_g_ItemId,x570006_g_ItemNum)
			else
			BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"��Ʒ���������޷������Ʒ��")
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)
			end	
		elseif weiyi == 1 then
			if have < 1 then
				BeginAddItem(sceneId)
					AddItem( sceneId,x570006_g_ItemBonus[zhiye+1].id,x570006_g_ItemBonus[1].num)
				local ret = EndAddItem(sceneId,selfId)
				if ret > 0 then
					AddItemListToPlayer(sceneId,selfId)
					DelItem(sceneId,selfId,x570006_g_ItemId,x570006_g_ItemNum)
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
		
function x570006_ProcAcceptCheck( sceneId, selfId, NPCId )
	return 1

end


--**********************************
--����
--**********************************
function x570006_ProcQuestAbandon( sceneId, selfId, MissionId )

end

--**********************************
--����
--**********************************
function x570006_OnContinue( sceneId, selfId, targetId )

end

--**********************************
--����Ƿ�����ύ
--**********************************
function x570006_CheckSubmit( sceneId, selfId )

end

--**********************************
--�ύ
--**********************************
function x570006_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )

end

--**********************************
--ɱ����������
--**********************************
function x570006_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )

end

--**********************************
--���������¼�
--**********************************
function x570006_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

--**********************************
--���߸ı�
--**********************************
function x570006_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end
