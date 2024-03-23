
x888893_g_ScriptId =  888893

x888893_g_ItemList = { 	{ missionId=8067, itemId=13011800, beastId=nil, horseId=nil },
												{ missionId=8068, itemId=13011801, beastId=nil, horseId=nil },
												{ missionId=8069, itemId=13011802, beastId=nil, horseId=nil },
												{ missionId=8070, itemId=13011803, beastId=nil, horseId=nil },
												{ missionId=8071, itemId=13011804, beastId=nil, horseId=nil },
												{ missionId=8072, itemId=13011805, beastId=nil, horseId=nil },
												{ missionId=8073, itemId=13011806, beastId=nil, horseId=nil },
												{ missionId=-1, itemId=-1, beastId=1, horseId=41 },
												{ missionId=-1, itemId=-1, beastId=2, horseId=1 },
												{ missionId=-1, itemId=-1, beastId=3, horseId=11 },
												{ missionId=-1, itemId=-1, beastId=4, horseId=51 },
												{ missionId=-1, itemId=-1, beastId=5, horseId=21 },
												{ missionId=-1, itemId=-1, beastId=6, horseId=31 },
												{ missionId=-1, itemId=-1, beastId=7, horseId=41 },
												{ missionId=-1, itemId=-1, beastId=8, horseId=1 },
												{ missionId=-1, itemId=-1, beastId=9, horseId=11 },
												{ missionId=-1, itemId=-1, beastId=10, horseId=51 },
												{ missionId=-1, itemId=-1, beastId=11, horseId=21 },
												{ missionId=-1, itemId=-1, beastId=12, horseId=31 }	,
												{ missionId=-1, itemId=-1, beastId=13, horseId=41 },
												{ missionId=-1, itemId=-1, beastId=14, horseId=1 },
												{ missionId=-1, itemId=-1, beastId=15, horseId=11 },
												{ missionId=-1, itemId=-1, beastId=16, horseId=51 },
												{ missionId=-1, itemId=-1, beastId=17, horseId=21 },
												{ missionId=-1, itemId=-1, beastId=18, horseId=31 }	,
												{ missionId=-1, itemId=-1, beastId=19, horseId=41 },
												{ missionId=-1, itemId=-1, beastId=20, horseId=1 },
												{ missionId=-1, itemId=-1, beastId=21, horseId=11 },
												{ missionId=-1, itemId=-1, beastId=22, horseId=51 },
												{ missionId=-1, itemId=-1, beastId=23, horseId=21 },
												{ missionId=-1, itemId=-1, beastId=24, horseId=31 }		}

function x888893_IfCanCapture(sceneId, selfId, beastieId, beastieDataId)

	local itemId = GetBeastieItem(sceneId, selfId, beastieId, beastieDataId)
	--����������Ʒ�򷵻�
	if itemId > 0 then
	
		if HaveItem( sceneId, selfId, itemId ) > 0 then
			local strText1 = format("#Y���Ѿ���#G#{_ITEM%d}#Y�ˣ������ٲ���", itemId);
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId, strText1);
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)
			return 0
		end
		 
		for i, item in pairs(x888893_g_ItemList) do
			if item.itemId ==  itemId then
				if IsHaveQuestNM(sceneId, selfId, item.missionId) == 1 then
					return 1
				end
			end
		end
		
	else
		
		for i, item in pairs(x888893_g_ItemList) do
			if item.missionId < 0 or IsHaveQuestNM(sceneId, selfId, item.missionId) == 1 then
				if IsHaveHorse(sceneId, selfId, item.horseId) > 0 then
					BeginQuestEvent(sceneId);
						AddQuestText(sceneId, "���Ѿ�ץ�����ˣ������ٲ���");
					EndQuestEvent(sceneId);
					DispatchQuestTips(sceneId, selfId);
					return 0;
				end
			end
		end
			
		for i, item in pairs(x888893_g_ItemList) do
			if item.missionId < 0 or IsHaveQuestNM(sceneId, selfId, item.missionId) == 1 then
				if beastieDataId == item.beastId then
					return 1;
				end
			end
		end
	end
	
	local strText2 = "�㲻�ܽ��в��������"
	BeginQuestEvent(sceneId)
	AddQuestText(sceneId, strText2);
	EndQuestEvent(sceneId)
	DispatchQuestTips(sceneId,selfId)
	
	return 0
end

function x888893_OnAddBeastieItem( sceneId, selfId, beastieId, beastieDataId )

	local itemId = GetBeastieItem(sceneId, selfId, beastieId, beastieDataId)
	
	local ret = 0;
	
	if itemId <= 0 then
		for i, item in pairs(x888893_g_ItemList) do
			if item.missionId < 0 or IsHaveQuestNM(sceneId, selfId, item.missionId) == 1 then
				if beastieDataId == item.beastId then
					ret = CreateHorseToPlayer(sceneId, selfId, item.horseId, -1);
				end
			end
		end
	else
		if IsHaveSpecificImpact( sceneId, selfId, 7517 ) > 0 or IsHaveSpecificImpact( sceneId, selfId, 7516 ) > 0 then
			ret = AddBeastieItem(sceneId, selfId, itemId, beastieId)
			if ret <= 0 then
				BeginQuestEvent(sceneId);
					AddQuestText(sceneId, "��������");
				EndQuestEvent(sceneId);
				DispatchQuestTips(sceneId, selfId);
			end
		end
	end
	
	return ret
	
end


function x888893_OnCaptureBeastieInterrupt(sceneId, selfId, beastieId)
  local strText = "��׽���жϣ�"
	BeginQuestEvent(sceneId)
	AddQuestText(sceneId, strText);
	EndQuestEvent(sceneId)
	DispatchQuestTips(sceneId,selfId)

end

function x888893_OnCaptureBeastieCancel(sceneId, selfId, beastieId)
    local strText = "��׽��ȡ����"
	BeginQuestEvent(sceneId)
	AddQuestText(sceneId, strText);
	EndQuestEvent(sceneId)
	DispatchQuestTips(sceneId,selfId)

end