--�һ�100������
--MisDescBegin
--�ű���
x570048_g_ScriptId = 570048

--�����Ƕ�̬**************************************************************

--�����ı�����
x570048_g_MissionName="������ʯ���һ�ڤ������"
x570048_g_EXCName = "�һ�ڤ������"		--�һ����� ����������ʾ���������ʹ��
x570048_g_EXCItemName = "ڤ֮����ʯ"		--�һ�����Ҫ�ĵ�������
x570048_g_ItemId = 11050005           --�������ID
x570048_g_ItemNum = 310                 --��������  
x570048_g_ItemBonus	=	{{id=10269500,num=1},{id=10269501,num=1},{id=10269502,num=1},{id=10269503,num=1},{id=10269504,num=1},{id=10269505,num=1},{id=10269506,num=1},{id=10269507,num=1},{id=10269508,num=1},{id=10269509,num=1},{id=10269510,num=1},{id=10269511,num=1}}
x570048_g_MissionInfo = format("\t��ȷ��Ҫʹ��#G%s#W%s��\n\t����Ҫ#R%d��#W#G%s#W��",x570048_g_EXCItemName,x570048_g_EXCName,x570048_g_ItemNum,x570048_g_EXCItemName)	--����˵������
x570048_g_MissionError = format("\t��û���㹻������%s���޷�%s��",x570048_g_EXCItemName,x570048_g_EXCName)	--������Ϣ

--MisDescEnd
--**********************************
--������ں���
--**********************************
function x570048_ProcEventEntry( sceneId, selfId, targetId ,scriptId,seleteId)	--����������ִ�д˽ű�

	local zhiye = GetZhiye(sceneId, selfId)
	local longyannum = GetItemCount(sceneId, selfId, x570048_g_ItemId)
	local strText = format("\t��������#R%d��#W#G%s#W��",longyannum,x570048_g_EXCItemName)
		BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"#Y"..x570048_g_MissionName)
			AddQuestText(sceneId,x570048_g_MissionInfo)
			AddQuestText(sceneId,strText)
			AddQuestItemBonus(sceneId, x570048_g_ItemBonus[zhiye+1].id,x570048_g_ItemBonus[1].num)
		EndQuestEvent()
		DispatchQuestInfo(sceneId, selfId, targetId, x570048_g_ScriptId,-1)

end

--**********************************
--�о��¼�
--**********************************
function x570048_ProcEnumEvent( sceneId, selfId, targetId, MissionId )

	AddQuestNumText(sceneId,x570048_g_ScriptId,x570048_g_MissionName,3);
	
end



--**********************************
--����
--**********************************
function x570048_ProcAccept( sceneId, selfId )
	
	local Num = GetItemCount( sceneId, selfId, x570048_g_ItemId )

	if Num < x570048_g_ItemNum then 
		BeginQuestEvent(sceneId)
			AddQuestText(sceneId,x570048_g_MissionError)
		EndQuestEvent()
		DispatchQuestTips(sceneId, selfId)
	end
	
	if Num >= x570048_g_ItemNum then 

		local zhiye = GetZhiye(sceneId, selfId)
		local weiyi = ItemIsUnique(sceneId,selfId, x570048_g_ItemBonus[zhiye+1].id)
		local have  = HaveItem( sceneId,selfId,x570048_g_ItemBonus[zhiye+1].id)
		
		if weiyi ~= 1  then
			BeginAddItem(sceneId)
				AddItem( sceneId,x570048_g_ItemBonus[zhiye+1].id,x570048_g_ItemBonus[1].num)
			local ret = EndAddItem(sceneId,selfId)
			if ret > 0 then
				AddItemListToPlayer(sceneId,selfId)
				DelItem(sceneId,selfId,x570048_g_ItemId,x570048_g_ItemNum)
			else
			BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"��Ʒ���������޷������Ʒ��")
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)
			end	
		elseif weiyi == 1 then
			if have < 1 then
				BeginAddItem(sceneId)
					AddItem( sceneId,x570048_g_ItemBonus[zhiye+1].id,x570048_g_ItemBonus[1].num)
				local ret = EndAddItem(sceneId,selfId)
				if ret > 0 then
					AddItemListToPlayer(sceneId,selfId)
					DelItem(sceneId,selfId,x570048_g_ItemId,x570048_g_ItemNum)
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
		
function x570048_ProcAcceptCheck( sceneId, selfId, NPCId )
	return 1

end


--**********************************
--����
--**********************************
function x570048_ProcQuestAbandon( sceneId, selfId, MissionId )

end

--**********************************
--����
--**********************************
function x570048_OnContinue( sceneId, selfId, targetId )

end

--**********************************
--����Ƿ�����ύ
--**********************************
function x570048_CheckSubmit( sceneId, selfId )

end

--**********************************
--�ύ
--**********************************
function x570048_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )

end

--**********************************
--ɱ����������
--**********************************
function x570048_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )

end

--**********************************
--���������¼�
--**********************************
function x570048_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

--**********************************
--���߸ı�
--**********************************
function x570048_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end
