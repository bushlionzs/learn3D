 --����
x102000_g_ScriptId	= 102000
x102000_g_MissionId = 486
--**********************************
--�¼��������
--**********************************
function x102000_ProcEventEntry( sceneId, selfId,targetId )
	BeginQuestEvent(sceneId)
	AddQuestText(sceneId,"\t�������ں���ɽ�����ɹŵļ������һ������òҰܣ��ף�����ô��������Ǽ����ò��Щ���ƣ�")
	EndQuestEvent(sceneId)
	DispatchQuestEventList(sceneId,selfId,targetId)
	ShowNpcQuestEventList(sceneId,selfId,targetId)
end

function x102000_OnDie(sceneId, selfId, killerId)
	SetMonsterCamp(sceneId,selfId,20)
	local MissionId = x102000_g_MissionId
	local Index = 0
	local guid = GetMonsterGUID(sceneId, selfId)
	local x,z = GetWorldPos(sceneId,selfId)
	local Num =  GetNearPlayerCount(sceneId, killerId,x,z,20)  
	for i = 0, Num-1 do
		local humanObjId = GetNearPlayerMember(sceneId, killerId,i);
		if humanObjId >= 0 then
			if IsPlayerStateNormal(sceneId, humanObjId) > 0 then
				if IsHaveQuestNM(sceneId, humanObjId, x102000_g_MissionId) == 1 then
	            local misIndex = GetQuestIndexByID( sceneId, humanObjId, MissionId)
		            SetQuestByIndex( sceneId, humanObjId, misIndex, 0, 1)
				        SetQuestByIndex( sceneId, humanObjId, misIndex, 7, 1)
				        Msg2Player( sceneId, humanObjId, "�����ѱ����𣬡��糡�����鲻���������", 8, 3)
				        Msg2Player( sceneId, humanObjId, "�����ѱ����𣬡��糡�����鲻���������", 8, 2)
				        
				        --CallScriptFunction( x102000_g_MissionScriptId[Index], "ProcQuestLogRefresh", sceneId, humanObjId, MissionId)
			    		end
			    end
	        	
			end
		end
end