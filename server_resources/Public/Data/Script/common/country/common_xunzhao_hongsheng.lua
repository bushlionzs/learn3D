--Ѱ�Һ�������ű�
x300617_g_ScritpId = 300617
x300617_g_MissionId = 7019
x300617_g_NeedLevel = 40
x300617_g_NeedGold = 10000
x300617_g_KillMissionId =  7012
x300617_g_Material_Thread = 13011010 
x300617_g_Material_Color =  13011011

x300617_g_AwardItemId = 13011012 --������Ʒid


function x300617_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	if GetLevel(sceneId, selfId) < 40 then
		return
	end

	local haveAccept = IsHaveQuestNM( sceneId, selfId, MissionId ) 
	if  haveAccept== 0 then	-- ���û���������
		 AddQuestTextNM( sceneId, selfId, targetId, MissionId, 8, -1 ) -- ��ʾ������Ϣ
	end
end


function x300617_ProcEventEntry( sceneId, selfId, targetId, MissionId )
    if IsHaveQuestNM( sceneId, selfId, MissionId ) == 0 then	-- ���û���������    

		AddDispatchQuestInfoNM( sceneId, selfId, targetId, MissionId ) -- ��ʾ����������Ϣ
	  
    else--����ǲ��ǿ����ύ    
		local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId )
		if QuestCheckSubmitNM( sceneId, selfId, targetId, MissionId, misIndex ) > 0 then -- �������������
			QuestComplateInfoNM( sceneId, selfId, targetId, MissionId ) -- ��ʾ�����Ϣ
		else
			QuestNotComplateInfoNM( sceneId, selfId, targetId, MissionId ) -- ��ʾ����δ�����Ϣ
		end
    end
end


function x300617_ProcQuestAccept(sceneId, selfId, targetId, MissionId)
    if IsHaveQuestNM( sceneId, selfId, MissionId ) == 0 then	-- ���û���������
		local ItemNumOnPlayer = GetItemCount( sceneId, selfId, x300617_g_AwardItemId )
		if ItemNumOnPlayer > 0 then
			BeginQuestEvent(sceneId);
			AddQuestText(sceneId, " �ܱ�Ǹ���������к����ˣ������ٽ������ˣ�");
			EndQuestEvent(sceneId);
			DispatchQuestTips(sceneId,selfId);
			Msg2Player(sceneId,selfId,"�ܱ�Ǹ���������к����ˣ������ٽ������ˣ�",8,2)
			return
		end

		if GetSex(sceneId, selfId) ~= 1 then
			BeginQuestEvent(sceneId);
			AddQuestText(sceneId, "���������ǵ���ʿ����ȡ������");
			EndQuestEvent(sceneId);
			DispatchQuestTips(sceneId,selfId);
			Msg2Player(sceneId,selfId,"���������ǵ���ʿ����ȡ������",8,2)
			return
		end

        if  IsMarried(sceneId, selfId) == 0  then --�Ƿ��ѻ�
            if GetLevel(sceneId, selfId) >= x300617_g_NeedLevel then			
				local money = GetMoney( sceneId, selfId, 0 )				
				if money >= x300617_g_NeedGold then
                    x300617_Accept( sceneId, selfId, MissionId )
				else-- ��Ǯ����
					BeginQuestEvent(sceneId);
					AddQuestText(sceneId, "�ܱ�Ǹ���������е���������10�����޷���ȡ����");
					EndQuestEvent(sceneId);
					DispatchQuestTips(sceneId,selfId);
					Msg2Player(sceneId,selfId,"�ܱ�Ǹ���������е���������10�����޷���ȡ����",8,2)
				end
            else
				BeginQuestEvent(sceneId);
				AddQuestText(sceneId, "�ܱ�Ǹ�����ĵȼ�����40�����޷���ȡ������");
				EndQuestEvent(sceneId);
				DispatchQuestTips(sceneId,selfId);Msg2Player(sceneId,selfId,"�ܱ�Ǹ�����ĵȼ�����40�����޷���ȡ������",8,2)
				--AddDispatchQuestInfoNM( sceneId, selfId, targetId, MissionId ) -- ��ʾ����������Ϣ
            end
        else--�Ѿ����           
				BeginQuestEvent(sceneId);
				AddQuestText(sceneId, "���Ѿ������,�޷���ȡ����");
				EndQuestEvent(sceneId);
				DispatchQuestTips(sceneId,selfId);
				Msg2Player(sceneId,selfId,"�ܱ�Ǹ���������ѻ�����޷���ȡ������",8,2)
        end
    end
end


function x300617_Accept( sceneId, selfId, MissionId )

	--���ǰ������
	local FrontMissiontId1, FrontMissiontId2, FrontMissiontId3 = GetFrontQuestIdNM( sceneId, selfId, MissionId )
	if FrontMissiontId1 ~= -1 then
		if IsQuestHaveDoneNM( sceneId, selfId, FrontMissiontId1 ) == 0 then
			return -1
		end
	end
	if FrontMissiontId2 ~= -1 then
		if IsQuestHaveDoneNM( sceneId, selfId, FrontMissiontId2 ) == 0 then
			return -1
		end
	end
	if FrontMissiontId3 ~= -1 then
		if IsQuestHaveDoneNM( sceneId, selfId, FrontMissiontId3 ) == 0 then
			return -1
		end
	end

	local	ret = AddQuestNM( sceneId, selfId, MissionId ) -- ������������
	local strText = GetQuestNameNM( sceneId, selfId, MissionId )
	
	strText = "������������" .. strText
	if ret == 0 then
		strText = "�������ʧ��"
	elseif ret == -1 then
		strText = "��������,�����������������"
	elseif ret == -2 then
		strText = "�����Ѵﵽ���ޣ��޷����µ�����"
	elseif ret == -3 then
		strText = "�ܱ�Ǹ���������еĽ�Ǯ�������޷���ȡ����"
	else
		strText = "�����������񣺡�������Ѱ�Һ�����"
	end

	BeginQuestEvent(sceneId);
	AddQuestText(sceneId, strText);
	EndQuestEvent(sceneId);
	DispatchQuestTips(sceneId,selfId);
	Msg2Player(sceneId,selfId,strText,4,2)

	return -1
end


--ɱ������
function x300617_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )
--����ID, �Լ���ID, �����λ�ú�, ����objId, ����ID

	local ItemCount=0;
	local ItemID=0;
	local ItemRand=0;
	local ItemDropNum=0;
	--����ID, �Լ���ID, �����λ�ú�, ����objId, ����ID
	local NeedKilledNum, InstIndex, ObjName = GetQuestNeedKillObjInfoNM( sceneId, selfId, MissionId, objdataId, objId )
		if NeedKilledNum >= 0 then
			local KilledNum = GetMonsterOwnerCount( sceneId, objId ) --ȡ�������������ӵ�з���Ȩ������
			for i = 0, KilledNum-1 do
				local humanObjId = GetMonsterOwnerID( sceneId, objId, i ) --ȡ��ӵ�з���Ȩ���˵�objId
				if humanObjId ~= -1 then
					if IsPlayerStateNormal(sceneId, humanObjId) > 0 then
						if GetHp(sceneId, humanObjId) > 0 then
							if IsHaveQuestNM( sceneId, humanObjId, MissionId ) > 0 then	--��������ӵ������
								if InstIndex >= 0 then
									
									ItemCount, ItemID, ItemRand, ItemDropNum = GetQuestItemNM( sceneId, humanObjId, MissionId, InstIndex )
							
											--Ҫ�ռ��ĸ�������ƷID�������ʣ�һ��������
									if HaveItem( sceneId, humanObjId, ItemID ) ~= 1 then --���û�������Ʒ 
										BeginAddItem(sceneId)
										AddItem( sceneId, ItemID, ItemDropNum )
										local ret = EndAddItem(sceneId,humanObjId)
										if ret > 0 then
											--AddItemListToPlayer(sceneId,selfId)
											AddItemListToPlayer(sceneId,humanObjId)
										else
											BeginQuestEvent(sceneId)
											AddQuestText(sceneId,"��Ʒ���������޷��õ�������Ʒ��")
											EndQuestEvent(sceneId)
											DispatchQuestTips(sceneId,humanObjId)
										end
											--end
									  end
										
									
								end
							end

						end--end
					end
				end
			end
		end


end



--��Ʒ�ı�
function x300617_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )--Ѱ�Ҳ��ϵ�������ɺ�����Ӻϳ�����
	
	
	if MissionId == nil or MissionId < 0 then
        return
    end
    
	if IsHaveQuestNM( sceneId, selfId, MissionId ) <= 0 then
		return
	end

	if IsPlayerStateNormal(sceneId, selfId) == 0 then
		return 
	end

	if GetHp(sceneId, selfId) <= 0 then
		return
	end

	local NeedNum, ObjIndex = GetQuestNeedItemNumNM( sceneId, selfId, MissionId, itemdataId )
	--
	local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId )

	if NeedNum > 0 then
		local Num = GetItemCount( sceneId, selfId, itemdataId )
		if Num < NeedNum then --��û���������
			BeginQuestEvent(sceneId)
			local strText = format("�ѵõ���@itemid_%d: %d/%d", itemdataId, Num, NeedNum )
			if strText == nil then
				strText = "";
			end
			AddQuestText( sceneId, strText )
			EndQuestEvent( sceneId )
			DispatchQuestTips( sceneId, selfId )
   			SetQuestByIndex( sceneId, selfId, misIndex, ObjIndex, Num )         --by zheng
		elseif Num == NeedNum then
			--�Ѿ��������
			BeginQuestEvent(sceneId)
			local strText = format( "�ѵõ���@itemid_%d: %d/%d", itemdataId, Num, NeedNum )
			if strText == nil then
				strText = "";
			end
			AddQuestText( sceneId, strText )
			EndQuestEvent( sceneId )
			DispatchQuestTips( sceneId, selfId )
			SetQuestByIndex( sceneId, selfId, misIndex, ObjIndex, Num )         --by zheng
			--local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId )
			--if QuestCheckSubmitNM( sceneId, selfId, targetId, MissionId, misIndex ) > 0 then
				--local MisCareNPC = QuestCareNPCNM( sceneId, selfId, misIndex )
				--if MisCareNPC == 0 then --�����Զ����
				    --if  IsHaveQuestNM( sceneId, selfId, MissionId ) > 0 then
	                    --x300617_MissionComplate( sceneId, selfId, MissionId )
					--end

				--end
			--end
		end
	end
	return 0
end


function x300617_MissionComplate( sceneId, selfId, MissionId )
	local ret = DelQuest( sceneId, selfId, MissionId )

	if ret > 0 then
		local strText = GetQuestNameNM( sceneId, selfId, MissionId )
		strText = "�����������" .. strText
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, strText);
		EndQuestEvent(sceneId);
		DispatchQuestTips(sceneId,selfId);
		Msg2Player( sceneId, selfId, strText, 4,2 )
	end
end



function x300617_ProcQuestAbandon( sceneId, selfId, MissionId )
	local ret = 0
	local MissionName = GetQuestNameNM( sceneId, selfId, MissionId )
	ret = DelQuest( sceneId, selfId, MissionId )
	if ret == 1 then
	--ɾ��ԭ���� 
		   if HaveItem(sceneId, selfId, x300617_g_Material_Thread) > 0 then
		   		DelItem(sceneId, selfId, x300617_g_Material_Thread, 1);	
		   end
		   
		   if HaveItem(sceneId, selfId, x300617_g_Material_Color) > 0 then
		   		DelItem(sceneId, selfId, x300617_g_Material_Color, 1);	
		   end

		local strText = GetQuestNameNM( sceneId, selfId, MissionId )
		strText = "������������" .. strText
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, strText);
		EndQuestEvent(sceneId);
		DispatchQuestTips(sceneId,selfId);
		Msg2Player( sceneId, selfId, strText, 4,2 )
	else
		--ret = -1
		--�۳�������Ʒʧ�ܴ���
	end
end

function x300617_ProcQuestSubmit( sceneId, selfId, targetId, selectId, MissionId )
	if IsHaveQuestNM( sceneId, selfId, MissionId ) > 0 then	-- ���û�������ֱ���˳�
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, "��ȥ���ҵ�����ų�˫ȥ���������ɣ�");
		EndQuestEvent(sceneId);
		DispatchQuestTips(sceneId,selfId);
		Msg2Player( sceneId, selfId, "��ȥ���ҵ�����ų�˫ȥ���������ɣ�", 4,2 )
	end
end

function x300617_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )
	if IsHaveQuestNM( sceneId, selfId, MissionId ) == 0 then	-- ���û���������
		return
	end
	

	local npcName = GetName( sceneId, npcId )
	if npcName == "" then	--NPC���ֻ��ǿյ�ô
		return
	end

	local guid = GetQuestSubmitNPCGUIDNM( sceneId, selfId, misIndex )
	local  missionState = GetQuestStateNM(sceneId, selfId, npcId, MissionId)
	if guid ~= -1 then --�����������ɵ�NPC
		if guid == npcGuid then	--�����NPC�����ֺ�������NPC��������ͬ������Ҳ�жϹ���
			AddQuestTextNM( sceneId, selfId, npcId, MissionId, missionState, -1 ) -- ��ʾ������Ϣ
		end
	else
		AddQuestTextNM( sceneId, selfId, npcId, MissionId, missionState, -1 ) -- ��ʾ������Ϣ
	end
end
