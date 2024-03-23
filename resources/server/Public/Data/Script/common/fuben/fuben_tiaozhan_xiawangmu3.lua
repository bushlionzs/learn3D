
--MisDescBegin

x701106_g_ScriptId 					= 	701106                  --�ű�ID

x701106_g_MissionIdList					=   {5205,5226,5247,5268}

x701106_g_LevelLess					= 	65                      --�������ŵȼ�  <=0 ��ʾ������


x701106_g_MissionName				= 	"�����ˡ���ս����Ĺ������"

x701106_g_MissionTarget				= 	"target1"
x701106_g_MissionInfo				= 	"info1"
x701106_g_ContinueInfo				= 	"continue1"
x701106_g_MissionCompleted			= 	"complete1"
x701106_g_MissionHelp				=	"help1"          --������ʾ��Ϣ


--MisDescEnd


x701106_g_MissionStart				= 5200
x701106_g_MissionEnd				= 5283

-- ��Щ����Ҫ���õ�
x701106_g_GamePlayId				=  1065
x701106_g_KillCount = 3
x701106_g_KillType = {{name="mosnter1", type=35512},{name="mosnter2", type=35511},{name="mosnter3", type=35510}}
x701106_g_ReplyNpc = 123744

function  x701106_GetMissionId(sceneId, selfId)
	local nCountry = GetCurCountry( sceneId, selfId )

	return x701106_g_MissionIdList[nCountry+1]
end

function  x701106_GetMyHaveMissionId( sceneId, selfId)


	for i=x701106_g_MissionStart, x701106_g_MissionEnd do
		if IsHaveQuestNM( sceneId, selfId, i ) > 0 then
			return i
		end
	end

	return 0
end

function x701106_CheckAvaliableFuben(sceneId, selfId)
	if x701106_GetMyHaveMissionId( sceneId, selfId) == 0 then
		return 0;
	end

	if GetSceneType(sceneId)~=1 then --���Ǹ���
		return 0;
	end

	if GetFubenData_Param(sceneId, 254 ) ~=2 then --����Ӣ�۸���
		return 0;
	end
	return 1
end

function x701106_ShowTips(sceneId, selfId, str)
	BeginQuestEvent(sceneId);
		AddQuestText(sceneId,str);
	EndQuestEvent();
	DispatchQuestTips(sceneId, selfId);
end

function x701106_ProcEnumEvent( sceneId, selfId, targetId, MissionId )


	if IsQuestHaveDone(sceneId, selfId, MissionId) > 0 then
		return 0
	end

	local nLevel = GetLevel(sceneId, selfId)

	if nLevel<x701106_g_LevelLess then
		return
	end
	
	if IsHaveQuestNM( sceneId, selfId, MissionId ) == 0 then
		local  missionState = GetQuestStateNM(sceneId, selfId, targetId, MissionId)
		AddQuestTextNM(sceneId, selfId, targetId, MissionId, missionState,missionState);
	else
		
		local  missionState = GetQuestStateNM(sceneId, selfId, targetId, MissionId)
		
		AddQuestTextNM(sceneId, selfId, targetId, MissionId, missionState,missionState);

	end
	
end

--ѡ������
function x701106_ProcEventEntry( sceneId, selfId, targetId, MissionId, nExt )
	
	if IsHaveQuestNM( sceneId, selfId, MissionId ) == 0 then	-- ���û���������

		x701106_DispatchMissionInfo( sceneId, selfId, targetId, MissionId )
	
	else --������������
		
		if nExt == 7 then
			x701106_DispatchCompletedInfo( sceneId, selfId, targetId,MissionId )
		
		else
			x701106_DispatchContinueInfo( sceneId, selfId, targetId,MissionId )
			
		end
	end
end


--��������
function x701106_ProcQuestAccept( sceneId, selfId, targetId, MissionId )
	if IsHaveQuestNM( sceneId, selfId, MissionId ) > 0 then	-- ������������ֱ���˳�
		return 0
	end

	if x701106_GetMyHaveMissionId( sceneId, selfId)>0 then
		x701106_ShowTips(sceneId, selfId, "����������ս�������񣬲�����ȡ")
		return 0
	end

	if IsQuestHaveDone(sceneId, selfId, MissionId) > 0 then
		return 0
	end


	if GetLevel(sceneId, selfId) < x701106_g_LevelLess then
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, "��ȼ����ͣ�������ȡ����");
		EndQuestEvent();
		DispatchQuestTips(sceneId, selfId);
		Msg2Player(sceneId,selfId,"��ȼ����ͣ�������ȡ����",8,2)
		return 0
	end

	--���ǰ������
	local FrontMissiontId1, FrontMissiontId2, FrontMissiontId3 = GetFrontQuestIdNM( sceneId, selfId,MissionId  )
	if FrontMissiontId1 ~= -1 then
		if IsQuestHaveDoneNM( sceneId, selfId, FrontMissiontId1 ) == 0 then
			return 0
		end
	end
	if FrontMissiontId2 ~= -1 then
		if IsQuestHaveDoneNM( sceneId, selfId, FrontMissiontId2 ) == 0 then
			return 0
		end
	end
	if FrontMissiontId3 ~= -1 then
		if IsQuestHaveDoneNM( sceneId, selfId, FrontMissiontId3 ) == 0 then
			return 0
		end
	end

	local ret = QuestCheckAcceptNM( sceneId, selfId, targetId, MissionId ) -- ��ȡ������������Ϣ
	if ret <=0 then -- ��������Խ��������
		return 0
	end

	--------------------------- add for Mission full check --------------
	local bFullMission = IsQuestFullNM(sceneId,selfId)
	
	if bFullMission>0 then
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, "�����������޷���������");
		EndQuestEvent();
		DispatchQuestTips(sceneId, selfId);
		return 0
	end
	---------------------------- add end -------------------------------
	
	ret = AddQuestNM( sceneId, selfId, MissionId ) -- ������������		
	
	if ret > 0 then
		
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, "������������:"..x701106_g_MissionName);
		EndQuestEvent();
		DispatchQuestTips(sceneId, selfId);
		Msg2Player(sceneId,selfId,"������������:"..x701106_g_MissionName,8,2)

		return 1
	else
		
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, "�����������");
		EndQuestEvent();
		DispatchQuestTips(sceneId, selfId);
	
	
	end
	
	return 0
end


function x701106_ProcQuestSubmit( sceneId, selfId, targetId, selectId, MissionId )
	if IsHaveQuestNM( sceneId, selfId, MissionId ) <= 0 then
		return 0
	end


	local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId )

	local nIndex = GetQuestParam( sceneId, selfId, misIndex, 5 )

	if x701106_CheckSubmit( sceneId, selfId, MissionId )>0 then
		
		local ret = DelQuestNM( sceneId, selfId, MissionId )

		if ret>0 then
			QuestCom(sceneId, selfId, MissionId)   --���ñ����������
			local str = "�����������:"..x701106_g_MissionName;
			x701106_ShowTips(sceneId, selfId, str)
			Msg2Player(sceneId,selfId,str,8,2)

			x701106_GiveReward(sceneId,selfId)

			GamePlayScriptLog(sceneId, selfId, x701106_g_GamePlayId)
			
		else
			x701106_ShowTips(sceneId, selfId, "������ʧ��")
		end
		
	end

	return 0
end

function x701106_CheckSubmit( sceneId, selfId, MissionId )
	if IsHaveQuestNM( sceneId, selfId, MissionId ) <= 0 then
		return 0
	end

	return 1;


end

--********************************************************************
--����
--********************************************************************
function x701106_ProcQuestAbandon( sceneId, selfId,MissionId )
	
	if IsHaveQuestNM( sceneId, selfId, MissionId ) <= 0 then
		return 0
	end

	if x701106_GetMyHaveMissionId( sceneId, selfId ) <= 0 then	-- ������������ֱ���˳�
		return 0
	end
	
	
	
	DelQuestNM( sceneId, selfId, MissionId )
	BeginQuestEvent(sceneId);
		AddQuestText(sceneId, "������������:"..x701106_g_MissionName);
	EndQuestEvent();
	DispatchQuestTips(sceneId, selfId);
	Msg2Player(sceneId,selfId,"������������:"..x701106_g_MissionName,8,2)


end

function x701106_GiveReward(sceneId,selfId)

	local nExpBonus = x701106_GetExp( sceneId, selfId )
	
	AddExp(sceneId, selfId, nExpBonus)
	BeginQuestEvent(sceneId);
		AddQuestText(sceneId, "#o���#R����"..nExpBonus.."��#o�Ľ���");
		EndQuestEvent();
		DispatchQuestTips(sceneId, selfId);
	Msg2Player(sceneId,selfId,"#o���#R����"..nExpBonus.."��#o�Ľ���",4,2)
end


function x701106_ProcQuestAttach( sceneId, selfId, npcId, npcGuid,misIndex, MissionId )
	if IsHaveQuestNM( sceneId, selfId, MissionId) == 0 then	-- ���û���������
		return
	end
end



--ɱ������
function x701106_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )
	
end

--��Ʒ�ı�
function x701106_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
	return 0
end
---------------------------------------------------------------------------------------------------
--���������ܽ��
---------------------------------------------------------------------------------------------------
function x701106_ProcAcceptCheck(sceneId, selfId, NPCId)
	return 1
end

---------------------------------------------------------------------------------------------------
--��ͻ��˷���������Ϣ
---------------------------------------------------------------------------------------------------
function x701106_DispatchMissionInfo( sceneId, selfId, NPCId, MissionId)
	--local awardexp = x701106_GetExp( sceneId, selfId )
	
	BeginQuestEvent(sceneId)

	AddQuestText(sceneId,"#Y"..x701106_g_MissionName)
	--������Ϣ
	
	AddQuestText(sceneId,x701106_g_MissionInfo)
	AddQuestText(sceneId," ")
	AddQuestText(sceneId,x701106_g_MissionTarget)
	AddQuestText(sceneId," ")
	AddQuestText(sceneId,x701106_g_MissionHelp)

	
	--AddQuestExpBonus(sceneId,  awardexp);
			
	EndQuestEvent()
	DispatchQuestInfoNM(sceneId, selfId, NPCId, x701106_g_ScriptId, MissionId,0);
end


---------------------------------------------------------------------------------------------------
--��ͻ��˷�������δ���
---------------------------------------------------------------------------------------------------
function x701106_DispatchContinueInfo( sceneId, selfId, NPCId,MissionId )

	
	BeginQuestEvent(sceneId)

	AddQuestText(sceneId,"#Y"..x701106_g_MissionName)
	--������Ϣ
	
	AddQuestText(sceneId, x701106_g_ContinueInfo)
	AddQuestText(sceneId," ")


			
	EndQuestEvent()
	DispatchQuestDemandInfo(sceneId, selfId, NPCId, x701106_g_ScriptId, MissionId,0);
end

---------------------------------------------------------------------------------------------------
--��ͻ��˷������������Ϣ
---------------------------------------------------------------------------------------------------
function x701106_DispatchCompletedInfo( sceneId, selfId, NPCId,MissionId )
	local awardexp = x701106_GetExp( sceneId, selfId )
	
	BeginQuestEvent(sceneId)

	AddQuestText(sceneId,"#Y"..x701106_g_MissionName)
	--������Ϣ
	
	AddQuestText(sceneId, x701106_g_MissionCompleted)
	AddQuestText(sceneId," ")

	AddQuestExpBonus(sceneId,  awardexp);
			
	EndQuestEvent()
	DispatchQuestContinueInfoNM(sceneId, selfId, NPCId, x701106_g_ScriptId, MissionId);

end



function x701106_ProcQuestLogRefresh( sceneId, selfId, MissionId)

	if IsHaveQuestNM( sceneId, selfId, MissionId ) <= 0 then
		return
	end

	local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId )

	local bCompleted = GetQuestParam( sceneId, selfId, misIndex, 7 )
	
	local str=""

	if bCompleted>0 then
		str = "#G��սӢ�۸����������а�(1/1)"
	else
		str = "#W��սӢ�۸����������а�(0/1)"
	end
	
	BeginQuestEvent(sceneId)	
		--local awardexp = x701106_GetExp( sceneId, selfId )

		--AddQuestExpBonus(sceneId,  awardexp);
			
	AddQuestLogCustomText( sceneId,
							"",						-- ����
							x701106_g_MissionName,        -- ��������
							str,		--����Ŀ��
							"@npc_"..x701106_g_ReplyNpc,			--����NPC
							x701106_g_MissionTarget,
							x701106_g_MissionInfo,	--��������
							x701106_g_MissionHelp					--����С��ʾ
							)
	EndQuestEvent()
	DispatchQuestLogUpdate(sceneId, selfId, MissionId);
		
	
end


function x701106_GetExp( sceneId, selfId )
	local level = GetLevel(sceneId, selfId)
	local maxlevel = GetTopListInfo_MaxLevel(GetWorldID(sceneId, selfId))
	local awardexp = 0
	if maxlevel > 0 then
			if level < 75 then
				awardexp = maxlevel*108000
			elseif level >=75 then
				awardexp = maxlevel*194400
		end
	end
	return awardexp
end


function x700028_ShowTipsToAll(sceneId, str)

	local humancount = GetFuben_PlayerCount(sceneId);

	--֪ͨ���
	for i = 0, humancount - 1 do
		local humanId = GetFuben_PlayerObjId(sceneId, i);
		
		BeginQuestEvent(sceneId);
			AddQuestText(sceneId,str);
		EndQuestEvent();
		DispatchQuestTips(sceneId, humanId);
	end
end

----------------------------------------------
-- fuben�ص�
----------------------------------------------
function x701106_OnFubuenCompleted(sceneId)
	
	
	if GetSceneType(sceneId)~=1 then --���Ǹ���
		return 0;
	end

	if GetFubenData_Param(sceneId, 254 ) ~=2 then --����Ӣ�۸���
		return 0;
	end


	local humancount = GetFuben_PlayerCount(sceneId);

	--֪ͨ���
	for i = 0, humancount - 1 do
		local humanId = GetFuben_PlayerObjId(sceneId, i);
		
		x701106_OnPlayerCompleteFuben(sceneId, humanId)
	end
end


function x701106_OnPlayerCompleteFuben(sceneId, selfId)
	
	local missionId = x701106_GetMissionId(sceneId, selfId)
	if x701106_CheckAvaliableFuben(sceneId, selfId)<=0 then
		return
	end

	if IsHaveQuestNM( sceneId, selfId, missionId ) <= 0 then
		return
	end

	if GetFubenData_Param(sceneId, 15 ) >0 then --������������
		return
	end

	local misIndex = GetQuestIndexByID( sceneId, selfId, missionId )

	
	SetQuestByIndex( sceneId, selfId, misIndex, 7, 1 )
	
	x701106_ProcQuestLogRefresh( sceneId, selfId, missionId)
end