--�һ�30��ñ��
--MisDescBegin
--�ű���
x570050_g_ScriptId = 570050

--�����Ƕ�̬**************************************************************

--�����ı�����
x570050_g_MissionName = "������ʯ���һ�ڤ֮����ʯ"   --�������
x570050_g_EXCName = "�һ�ڤ֮����ʯ"		--�һ����� ����������ʾ���������ʹ��
x570050_g_EXCItemName = "��֮����ʯ"		--�һ�����Ҫ�ĵ�������
x570050_g_CostitemId = 11050004	--�������ID
x570050_g_CostitemNum ={3,15,30,150,300} 				--��������
x570050_g_ItemId = 11050005	--��õ���ID
x570050_g_ItemNum = {1,5,10,50,100}				--�������
x570050_g_MissionError = format("\t��û���㹻������%s���޷�%s��",x570050_g_EXCItemName,x570050_g_EXCName)	--������Ϣ

--MisDescEnd
--**********************************
--������ں���
--**********************************
function x570050_ProcEventEntry( sceneId, selfId, NPCId, MissionId,nExt)	--����������ִ�д˽ű�

	if nExt==nil then
		return
	end

	if nExt==0 then

		BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"#Y"..x570050_g_MissionName)
			AddQuestText(sceneId,"\t�����������Խ���֮����ʯ�һ�Ϊڤ֮����ʯ��3����֮����ʯ���Զһ�1��ڤ֮����ʯ��\n\t#R�һ���ڤ֮����ʯ�ǰ󶨵ģ�")
			
				AddQuestNumText(sceneId, MissionId, "��Ҫ�һ�1��",3,1);
				AddQuestNumText(sceneId, MissionId, "��Ҫ�һ�5��",3,2);
				AddQuestNumText(sceneId, MissionId, "��Ҫ�һ�10��",3,3);
				AddQuestNumText(sceneId, MissionId, "��Ҫ�һ�50��",3,4);
				AddQuestNumText(sceneId, MissionId, "��Ҫ�һ�100��",3,5);

		EndQuestEvent()
		DispatchQuestEventList(sceneId, selfId, NPCId, x570050_g_ScriptId, MissionId);


	end

	if nExt==1 or nExt==2 or nExt==3 or nExt==4 or nExt==5 then
		x570050_DispatchExchangeInfo( sceneId, selfId, NPCId,nExt )
	end
end



function x570050_DispatchExchangeInfo( sceneId, selfId, NPCId, nExt )
        
	--������Ϣ
	if nExt==1 then
		BeginQuestEvent(sceneId)
        AddQuestText(sceneId,"#Y"..x570050_g_MissionName)
		AddQuestText(sceneId,format("\t��Ҫ��%d��#G��֮����ʯ#W��ȡ%d��#Gڤ֮����ʯ#W��\n\t#R�һ���ڤ֮����ʯ�ǰ󶨵ģ�", 3,1))
		AddQuestItemBonus(sceneId, x570050_g_ItemId,1)
		EndQuestEvent()
		DispatchQuestInfo(sceneId, selfId, NPCId, x570050_g_ScriptId, -1);
		x570050_SetSelected(sceneId, selfId, nExt)
	elseif nExt==2 then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"#Y"..x570050_g_MissionName)
		AddQuestText(sceneId,format("\t��Ҫ��%d��#G��֮����ʯ#W��ȡ%d��#Gڤ֮����ʯ#W��\n\t#R�һ���ڤ֮����ʯ�ǰ󶨵ģ�", 15,5))
		AddQuestItemBonus(sceneId, x570050_g_ItemId,5)
		EndQuestEvent()
		DispatchQuestInfo(sceneId, selfId, NPCId, x570050_g_ScriptId, -1);
	    x570050_SetSelected(sceneId, selfId, nExt)
	elseif nExt==3 then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"#Y"..x570050_g_MissionName)
		AddQuestText(sceneId,format("\t��Ҫ��%d��#G��֮����ʯ#W��ȡ%d��#Gڤ֮����ʯ#W��\n\t#R�һ���ڤ֮����ʯ�ǰ󶨵ģ�", 30,10))
		AddQuestItemBonus(sceneId, x570050_g_ItemId,10)
		EndQuestEvent()
		DispatchQuestInfo(sceneId, selfId, NPCId, x570050_g_ScriptId, -1);
	    x570050_SetSelected(sceneId, selfId, nExt)
	elseif nExt==4 then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"#Y"..x570050_g_MissionName)
		AddQuestText(sceneId,format("\t��Ҫ��%d��#G��֮����ʯ#W��ȡ%d��#Gڤ֮����ʯ#W��\n\t#R�һ���ڤ֮����ʯ�ǰ󶨵ģ�", 150,50))
		AddQuestItemBonus(sceneId, x570050_g_ItemId,50)
		EndQuestEvent()
		DispatchQuestInfo(sceneId, selfId, NPCId, x570050_g_ScriptId, -1);
	    x570050_SetSelected(sceneId, selfId, nExt)
	elseif nExt==5 then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"#Y"..x570050_g_MissionName)
		AddQuestText(sceneId,format("\t��Ҫ��%d��#G��֮����ʯ#W��ȡ%d��#Gڤ֮����ʯ#W��\n\t#R�һ���ڤ֮����ʯ�ǰ󶨵ģ�", 300,100))
		AddQuestItemBonus(sceneId, x570050_g_ItemId,100)
		EndQuestEvent()
		DispatchQuestInfo(sceneId, selfId, NPCId, x570050_g_ScriptId, -1);
	    x570050_SetSelected(sceneId, selfId, nExt)

	end	
end

--**********************************
--�о��¼�
--**********************************
function x570050_ProcEnumEvent( sceneId, selfId, targetId, MissionId )

	AddQuestNumText(sceneId,x570050_g_ScriptId,x570050_g_MissionName,3);
	
end


--**********************************
--����
--**********************************
function x570050_ProcAccept( sceneId, selfId ,nExt)

	local nExt = x570050_GetSelected(sceneId, selfId)
	if nExt==1 then
		nIndex = 1;
	elseif nExt==2 then
		nIndex = 2;
	elseif nExt==3 then
		nIndex = 3;
	elseif nExt==4 then
		nIndex = 4;
	elseif nExt==5 then
		nIndex = 5;

	else
		return
	end
	local Num = GetItemCount( sceneId, selfId, x570050_g_CostitemId )
    local weiyi = ItemIsUnique(sceneId,selfId, x570050_g_ItemId)
	local have  = HaveItem( sceneId,selfId,x570050_g_ItemId)
 
	if Num < x570050_g_CostitemNum[nIndex] then 
		BeginQuestEvent(sceneId)
			AddQuestText(sceneId,x570050_g_MissionError)
		EndQuestEvent()
		DispatchQuestTips(sceneId, selfId)
	end
	
	if Num >= x570050_g_CostitemNum[nIndex] then 
		
			BeginAddItem(sceneId)
			AddBindItem( sceneId,x570050_g_ItemId,x570050_g_ItemNum[nIndex])
			local ret = EndAddItem(sceneId,selfId)
			if ret > 0 then
				AddItemListToPlayer(sceneId,selfId)
				DelItem(sceneId,selfId,x570050_g_CostitemId,x570050_g_CostitemNum[nIndex])
				BeginQuestEvent(sceneId)
					AddQuestText(sceneId,"�һ��ɹ���")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
                
			else
				BeginQuestEvent(sceneId)
					AddQuestText(sceneId,"��Ʒ���������޷������Ʒ��")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
			end	
		elseif weiyi == 1 then
			if have < 1 then
				BeginAddItem(sceneId)
				AddBindItem( sceneId,x570050_g_ItemId,x570050_g_ItemNum[nIndex])
				local ret = EndAddItem(sceneId,selfId)
				if ret > 0 then
					AddItemListToPlayer(sceneId,selfId)
					DelItem(sceneId,selfId,x570050_g_CostitemId,x570050_g_CostitemNum[nIndex])
				else
				BeginQuestEvent(sceneId)
					AddQuestText(sceneId,"��Ʒ���������޷������Ʒ��")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				end	
			else
				BeginQuestEvent(sceneId)
					AddQuestText(sceneId,"���޷��һ������ڤ֮����ʯ��")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
			end	
		end
	end
		
function x570050_ProcAcceptCheck( sceneId, selfId, NPCId )
	return 1

end


--**********************************
--����
--**********************************
function x570050_ProcQuestAbandon( sceneId, selfId, MissionId )

end

--**********************************
--����
--**********************************
function x570050_OnContinue( sceneId, selfId, targetId )

end

--**********************************
--����Ƿ�����ύ
--**********************************
function x570050_CheckSubmit( sceneId, selfId )

end

--**********************************
--�ύ
--**********************************
function x570050_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )

end

--**********************************
--ɱ����������
--**********************************
function x570050_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )

end

--**********************************
--���������¼�
--**********************************
function x570050_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

--**********************************
--���߸ı�
--**********************************
function x570050_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end
---------------------------------------------------------------------------------------------------
--�õ���Ҹղ�ѡ��Ľ���ѡ��
---------------------------------------------------------------------------------------------------
function x570050_GetSelected(sceneId, selfId)
	return GetPlayerRuntimeData(sceneId, selfId, RD_COMMON_NPCID )
end


---------------------------------------------------------------------------------------------------
--������Ҹղ�ѡ��Ľ���ѡ��
---------------------------------------------------------------------------------------------------
function x570050_SetSelected(sceneId, selfId, flag)
	SetPlayerRuntimeData(sceneId, selfId, RD_COMMON_NPCID, flag)
end
