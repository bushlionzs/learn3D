--����֮�Ƕһ�������
--MisDescBegin
--�ű���
x300359_g_ScriptId = 300359

--�����Ƕ�̬**************************************************************

--�����ı�����
x300359_g_MissionName = "����֮�Ƕһ�������"   --�������
x300359_g_EXCName = "�һ�������"		--�һ����� ����������ʾ���������ʹ��
x300359_g_EXCItemName = "����֮��"		--�һ�����Ҫ�ĵ�������
x300359_g_ItemId = 12030210	--�������ID
x300359_g_ItemNum = 1				--��������
x300359_g_ItemBonus = {id=11990011,num=1}		--������Ʒ
x300359_g_MissionInfo = format("\t������дӳɼ�˼��1�б�������������֮�ǣ��������������ｫ��һ��������\n\t��ȷ��Ҫʹ��#G%s#W%s��\n\t����Ҫ#R%d��#W#G%s#W��",x300359_g_EXCItemName,x300359_g_EXCName,x300359_g_ItemNum,x300359_g_EXCItemName)	--����˵������
x300359_g_MissionError = format("\t��û���㹻������%s���޷�%s��",x300359_g_EXCItemName,x300359_g_EXCName)	--������Ϣ

--MisDescEnd
--**********************************
--������ں���
--**********************************
function x300359_ProcEventEntry( sceneId, selfId, targetId ,scriptId,seleteId)	--����������ִ�д˽ű�

	local zhiye = GetZhiye(sceneId, selfId)
	local longyannum = GetItemCount(sceneId, selfId, x300359_g_ItemId)
	local strText = format("\t��������#R%d��#W#G%s#W��",longyannum,x300359_g_EXCItemName)
		BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"#Y"..x300359_g_MissionName)
			AddQuestText(sceneId,x300359_g_MissionInfo)
			AddQuestText(sceneId,strText)
			AddQuestItemBonus(sceneId, x300359_g_ItemBonus.id,x300359_g_ItemBonus.num)
		EndQuestEvent()
		DispatchQuestInfo(sceneId, selfId, targetId, x300359_g_ScriptId,-1)

end

--**********************************
--�о��¼�
--**********************************
function x300359_ProcEnumEvent( sceneId, selfId, targetId, MissionId )

	AddQuestNumText(sceneId,x300359_g_ScriptId,x300359_g_MissionName,3);
	
end



--**********************************
--����
--**********************************
function x300359_ProcAccept( sceneId, selfId )
	
	local Num = GetItemCount( sceneId, selfId, x300359_g_ItemId )

	if Num < x300359_g_ItemNum then 
		BeginQuestEvent(sceneId)
			AddQuestText(sceneId,x300359_g_MissionError)
		EndQuestEvent()
		DispatchQuestTips(sceneId, selfId)
	end
	
	if Num >= x300359_g_ItemNum then 

		--local zhiye = GetZhiye(sceneId, selfId)
		--local weiyi = ItemIsUnique(sceneId,selfId, x300359_g_ItemBonus.id)
		--local have  = HaveItem( sceneId,selfId,x300359_g_ItemBonus.id)
		
		
			BeginAddItem(sceneId)
				AddBindItem( sceneId,x300359_g_ItemBonus.id,x300359_g_ItemBonus.num)
			local ret = EndAddItem(sceneId,selfId)
			if ret > 0 then
				AddItemListToPlayer(sceneId,selfId)
				DelItem(sceneId,selfId,x300359_g_ItemId,x300359_g_ItemNum)
			else
			BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"��Ʒ���������޷������Ʒ��")
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)
			end	
		
	end
end
		
function x300359_ProcAcceptCheck( sceneId, selfId, NPCId )
	return 1

end


--**********************************
--����
--**********************************
function x300359_ProcQuestAbandon( sceneId, selfId, MissionId )

end

--**********************************
--����
--**********************************
function x300359_OnContinue( sceneId, selfId, targetId )

end

--**********************************
--����Ƿ�����ύ
--**********************************
function x300359_CheckSubmit( sceneId, selfId )

end

--**********************************
--�ύ
--**********************************
function x300359_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )

end

--**********************************
--ɱ����������
--**********************************
function x300359_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )

end

--**********************************
--���������¼�
--**********************************
function x300359_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

--**********************************
--���߸ı�
--**********************************
function x300359_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end
