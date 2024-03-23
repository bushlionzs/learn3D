
x300648_g_ScritpId  =  300648
--x300648_g_MissionId = 7200
x300648_g_UICommandID = 100
x300648_g_MissionName = "Ѱ�Һ����ϳ�"
x300648_g_ItemId1 = 13011010
x300648_g_ItemId2 = 13011011
x300648_g_MixtureMissionId = 7019
x300648_g_AwardItemId = 13011012 --������Ʒid

x300648_g_OR_MIXTURE_FAIL = -2   --���ʧ�ܣ���Ʒ����
x300648_g_OR_FAIL = -1           --ʧ�ܣ��и���ʧ��
x300648_g_OR_SUCC = 1            --�ɹ�



function x300648_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	--AddQuestTextNM( sceneId, selfId, targetId, x300648_g_MissionId, 3, -1 ); -- ��ʾ������Ϣ
	AddQuestNumText(sceneId, x300648_g_ScritpId, x300648_g_MissionName,3);
end

function x300648_ProcEventEntry( sceneId, selfId, targetId, MissionId )
	--��֪�ͻ��˴򿪺ϳɽ���
	--if IsHaveQuestNM( sceneId, selfId, x300648_g_MissionId  ) > 0 then
		BeginUICommand(sceneId);
		UICommand_AddInt(sceneId, x300648_g_ScritpId);
		UICommand_AddInt(sceneId, targetId);
		DispatchUICommand(sceneId,selfId, x300648_g_UICommandID );
		EndUICommand(sceneId);
	--else
	    --BeginQuestEvent(sceneId);
		--AddQuestText( sceneId, "��û�кϳɺ�������" );
		--EndQuestEvent();
		--DispatchQuestEventList(sceneId, selfId, targetId)
	--end
end

function x300648_OnMixture( sceneId, selfId, item1, item2, item3, item4 )

	local itemId = {-1,-1,-1,-1};
	local itemPos = { item1, item2, item3, item4 };

		for i=1, 4 do
			if itemPos[i] ~= -1 then
				itemId[i] = GetItemTableIndexByIndex( sceneId, selfId, itemPos[i] );
			end

		end
		--�Ƿ���Ҫ����Ʒid�����ж�

	  if IsHaveQuestNM( sceneId, selfId, x300648_g_MixtureMissionId ) > 0  then
	  		local sign1 = -1;
	  		local sign2 = -1;

			local result=x300648_g_OR_SUCC;
	  		for i=1, 4 do  
				if itemId[i] ~= -1 then
					if itemId[i] == x300648_g_ItemId1 then
						sign1 = i;
					elseif itemId[i] == x300648_g_ItemId2 then
						sign2 = i;
					else
						result = x300648_g_OR_FAIL;
						break	
					end
				end
			end

			if result == x300648_g_OR_FAIL then
				BeginQuestEvent(sceneId);
				AddQuestText(sceneId, "�������Ӧ����Ʒ");
				EndQuestEvent(sceneId);
				DispatchQuestTips(sceneId,selfId);
				Msg2Player( sceneId, selfId, "�������Ӧ����Ʒ",4,2 );
				QuestMixtureResult( sceneId, selfId, result, itemPos[1], itemPos[2], itemPos[3], itemPos[4] );
				return
			end
			
			if sign1~= -1 and sign2 ~= -1 then   --���Ժϳ�

			    if  x300648_Rand() == 1 then
	        		BeginAddItem(sceneId)
					AddItem( sceneId, x300648_g_AwardItemId, 1 )
					local ret = EndAddItem(sceneId,selfId)
					if ret > 0 then
					
						AddItemListToPlayer(sceneId,selfId)
						BeginQuestEvent(sceneId);
						AddQuestText(sceneId, "��ɹ��غϳ��˺�����������ҽ���Ե�������ˡ�");
						EndQuestEvent(sceneId);
						DispatchQuestTips(sceneId,selfId);
						Msg2Player( sceneId, selfId, "��ɹ��غϳ��˺�����������ҽ���Ե�������ˡ�",4,2 );
						result = x300648_g_OR_SUCC;
						DelQuest(sceneId, selfId, x300648_g_MixtureMissionId)
						EraseItem(sceneId, selfId, itemPos[sign1]); --ɾ����Ʒ
			       		EraseItem(sceneId, selfId, itemPos[sign2]);
						itemPos[sign1] = -1;
			        	itemPos[sign2] = -1;
						QuestMixtureResult( sceneId, selfId, result, itemPos[1], itemPos[2], itemPos[3], itemPos[4] );
					else
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"��Ʒ���������޷��õ�������Ʒ��")
						EndQuestEvent(sceneId)
						DispatchQuestTips(sceneId,selfId)
					end
				else   
						BeginQuestEvent(sceneId);
						AddQuestText(sceneId, "�ϳɺ���ʧ��");
						EndQuestEvent(sceneId);
						DispatchQuestTips(sceneId,selfId);
						Msg2Player( sceneId, selfId, "�ϳɺ���ʧ��",4,2 );

						DelQuestNM(sceneId, selfId, x300648_g_MixtureMissionId)
						result = x300648_g_OR_FAIL;
						QuestMixtureResult( sceneId, selfId, result, itemPos[1], itemPos[2], itemPos[3], itemPos[4] );
				end

			else
				--Msg2Player( sceneId, selfId, "#R���Ѿ����["..MissionName.."]����", MSG2PLAYER_PARA );
				BeginQuestEvent(sceneId);
				AddQuestText(sceneId, "�������Ӧ����Ʒ");
				EndQuestEvent(sceneId);
				DispatchQuestTips(sceneId,selfId);
				Msg2Player( sceneId, selfId, "�������Ӧ����Ʒ",4,2 );
				result = x300648_g_OR_FAIL;
				QuestMixtureResult( sceneId, selfId, result, itemPos[1], itemPos[2], itemPos[3], itemPos[4] );
			end
	  else
			BeginQuestEvent(sceneId);
			AddQuestText(sceneId, "����û�к������񣬲��ܺϳ�");
			EndQuestEvent(sceneId);
			DispatchQuestTips(sceneId,selfId);
			Msg2Player( sceneId, selfId, "����û�к������񣬲��ܺϳ�",4,2 );
			QuestMixtureResult( sceneId, selfId, x300648_g_OR_FAIL, itemPos[1], itemPos[2], itemPos[3], itemPos[4] );
			return
	  end

end


function x300648_Rand()
	--local ret = random(0, 99);
	--if ret<5 then
	    --return -1;
	--end

	return 1;
end