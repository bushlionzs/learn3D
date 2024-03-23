
x310050_g_ScritpId  =  310050

x310050_g_UICommandID = 100
x310050_g_MissionName = "������ϳ�"
x310050_g_ItemId1 = 12030022
x310050_g_ItemId2 = 12030023
x310050_g_ItemId3 = 12030024
x310050_g_ItemId4 = 12030025

x310050_g_AwardItemId = 12030108 --������Ʒid

x310050_g_OR_FAIL = -1           --ʧ�ܣ��и���ʧ��
x310050_g_OR_SUCC = 1            --�ɹ�



function x310050_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	AddQuestNumText(sceneId, x310050_g_ScritpId, x310050_g_MissionName,3);
end

function x310050_ProcEventEntry( sceneId, selfId, targetId, MissionId )
	--��֪�ͻ��˴򿪺ϳɽ���
		BeginUICommand(sceneId);
		UICommand_AddInt(sceneId, x310050_g_ScritpId);
		UICommand_AddInt(sceneId, targetId);
		DispatchUICommand(sceneId,selfId, x310050_g_UICommandID );
		EndUICommand(sceneId);

end

function x310050_OnMixture( sceneId, selfId, item1, item2, item3, item4 )


	local itemId = {-1,-1,-1,-1};
	local itemPos = { item1, item2, item3, item4 };

		for i=1, 4 do
			if itemPos[i] ~= -1 then
				itemId[i] = GetItemTableIndexByIndex( sceneId, selfId, itemPos[i] );
			end

		end
		--�Ƿ���Ҫ����Ʒid�����ж�
	  		local sign1 = -1;
	  		local sign2 = -1;
			local sign3 = -1;
			local sign4 = -1;

			local result=x310050_g_OR_SUCC;
	  		for i=1, 4 do  
				if itemId[i] ~= -1 then
					if itemId[i] == x310050_g_ItemId1 then
						sign1 = i;
					elseif itemId[i] == x310050_g_ItemId2 then
						sign2 = i;
					elseif itemId[i] == x310050_g_ItemId3 then
						sign3 = i;
					elseif itemId[i] == x310050_g_ItemId4 then
						sign4 = i;
					else
						result = x310050_g_OR_FAIL;
						break	
					end
				end
			end

			if result == x310050_g_OR_FAIL then
				BeginQuestEvent(sceneId);
				AddQuestText(sceneId, "����ĵ��߲���ȷ���޷��ϳ�");
				EndQuestEvent(sceneId);
				DispatchQuestTips(sceneId,selfId);
				Msg2Player( sceneId, selfId, "����ĵ��߲���ȷ���޷��ϳ�",4,2 );
				QuestMixtureResult( sceneId, selfId, result, itemPos[1], itemPos[2], itemPos[3], itemPos[4] );
				return
			end
			
			if sign1~= -1 and sign2 ~= -1 and sign3 ~= -1 and sign4 ~= -1 then   --���Ժϳ�
	        		BeginAddItem(sceneId)
					AddItem( sceneId, x310050_g_AwardItemId, 1 )
					local ret = EndAddItem(sceneId,selfId)
					if ret > 0 then
						EraseItem(sceneId, selfId, itemPos[sign1]); --ɾ����Ʒ
			       		EraseItem(sceneId, selfId, itemPos[sign2]);
						EraseItem(sceneId, selfId, itemPos[sign3]);
						EraseItem(sceneId, selfId, itemPos[sign4]);
			       		itemPos[sign1] = -1;
			        	itemPos[sign2] = -1;
						itemPos[sign3] = -1;
			        	itemPos[sign4] = -1;

						AddItemListToPlayer(sceneId,selfId)
						BeginQuestEvent(sceneId);
						AddQuestText(sceneId, "��ɹ��غϳɸ��յ������ꡣ");
						EndQuestEvent(sceneId);

						DispatchQuestTips(sceneId,selfId);
						Msg2Player( sceneId, selfId, "��ɹ��غϳɸ��յ������ꡣ",4,2 );
						result = x310050_g_OR_SUCC;
						QuestMixtureResult( sceneId, selfId, result, itemPos[1], itemPos[2], itemPos[3], itemPos[4] );
					else
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"�����������޷����������Ʒ")
						EndQuestEvent(sceneId)
						DispatchQuestTips(sceneId,selfId)
					end
			else
				BeginQuestEvent(sceneId);
				AddQuestText(sceneId, "����ĵ��߲���ȷ���޷��ϳ�");
				EndQuestEvent(sceneId);
				DispatchQuestTips(sceneId,selfId);
				Msg2Player( sceneId, selfId, "����ĵ��߲���ȷ���޷��ϳ�",4,2 );
				result = x310050_g_OR_FAIL;
				QuestMixtureResult( sceneId, selfId, result, itemPos[1], itemPos[2], itemPos[3], itemPos[4] );
			end
end
