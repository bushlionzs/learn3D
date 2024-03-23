-------------------------------------------------
-- fututa_4: 
-------------------------------------------------
x700044_CSP_CURRENTSTEP		=	23--x700022_CSP_CURRENTSTEP	
x700044_CSP_FUBENLEVEL	=	9--x700022_CSP_FUBENLEVEL
x700044_CSP_FUBENLEVEL_DUP	=	27--x700044_CSP_FUBENLEVEL_DUP


x700044_CSP_HUMAN_TALKPARAM_START	=	230--x700022_CSP_HUMAN_TALKPARAM_START
x700044_CSP_GUID_START              =   248


x700044_g_LevelMin					=   20                      --������͵ȼ�
x700044_g_LevelMax					=   100                     --������ߵȼ�

x700044_g_ScriptId = 700044


x700044_Fuben_ScriptId = 700022

function x700044_ProcEventEntry(sceneId, selfId, NPCId, MissionId,which)	--����������ִ�д˽ű�
	
	if which==1 then	
		x700044_DispatchUpgrade( sceneId, selfId, NPCId,which ) --�����Ѷ�
	elseif which==2 then
		x700044_DispatchDegrade( sceneId, selfId, NPCId,which )	--�����Ѷ�
	end
	
end


--**********************************

--�о��¼�

--**********************************

function x700044_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)

	local nCurrentLevel = GetFubenData_Param(sceneId,x700044_CSP_FUBENLEVEL)
	local nStdLevel = GetFubenData_Param(sceneId,x700044_CSP_FUBENLEVEL_DUP)

	
	if nCurrentLevel< (nStdLevel+5) then
		AddQuestNumText(sceneId, x700044_g_ScriptId, "�����Ѷ�",0,1)
	end

	if nCurrentLevel> (nStdLevel-5) then
		AddQuestNumText(sceneId, x700044_g_ScriptId, "�����Ѷ�",0,2)
	end


	
	
	
		
end


---------------------------------------------------------------------------------------------------
--���븱��������ʾ
---------------------------------------------------------------------------------------------------
function x700044_DispatchUpgrade( sceneId, selfId, NPCId, nParam )

	BeginQuestEvent(sceneId)

		--������Ϣ
		AddQuestText(sceneId,"#Y�����Ѷ�")
		AddQuestText(sceneId,"����ȼ�����5")
		--AddQuestText(sceneId," ")

		


	EndQuestEvent()


	
	local myGuid = GetPlayerGUID( sceneId,selfId )
	myGuid = format("%u", myGuid)

	for i=0, 5 do
        local paramidx = x700044_CSP_GUID_START + i
        local nGUID = GetFubenData_Param(sceneId, paramidx  )
				nGUID = format("%u", nGUID)
        if nGUID == myGuid then

			SetFubenData_Param(sceneId,x700044_CSP_HUMAN_TALKPARAM_START+i, nParam)
            break
        end
    end

	


	DispatchQuestInfo(sceneId, selfId, NPCId, x700044_g_ScriptId, -1);
end



function x700044_DispatchDegrade( sceneId, selfId, NPCId, nParam )

	BeginQuestEvent(sceneId)

		--������Ϣ
		AddQuestText(sceneId,"#Y�����Ѷ�")
		AddQuestText(sceneId,"����ȼ�����5")
		--AddQuestText(sceneId," ")

		


	EndQuestEvent()


	local myGuid = GetPlayerGUID( sceneId,selfId )
	myGuid = format("%u", myGuid)

	for i=0, 5 do
        local paramidx = x700044_CSP_GUID_START + i
        local nGUID = GetFubenData_Param(sceneId, paramidx  )
				nGUID = format("%u", nGUID)
        if nGUID == myGuid then

			SetFubenData_Param(sceneId,x700044_CSP_HUMAN_TALKPARAM_START+i, nParam)
            break
        end
    end
	
	


	DispatchQuestInfo(sceneId, selfId, NPCId, x700044_g_ScriptId, -1);
end


---------------------------------------------------------------------------------------------------
--������븱��
---------------------------------------------------------------------------------------------------
function x700044_ProcAcceptCheck( sceneId, selfId, NPCId )
    return 1
end

----------------------------------------------------------------------------------------------
--��ȷ����
----------------------------------------------------------------------------------------------
function x700044_ProcAccept( sceneId, selfId )

	local nParam = 0;
	
	local myGuid = GetPlayerGUID( sceneId,selfId )
	myGuid = format("%u", myGuid)

	for i=0, 5 do
        local paramidx = x700044_CSP_GUID_START + i
        local nGUID = GetFubenData_Param(sceneId, paramidx  )
				nGUID = format("%u", nGUID)
        if nGUID == myGuid then

			nParam = GetFubenData_Param(sceneId,x700044_CSP_HUMAN_TALKPARAM_START+i)
            break
        end
    end
	
	
	
	if nParam==1 then
		x700044_OnRequestUpgrade(sceneId,selfId)
	elseif nParam==2 then
		x700044_OnRequestDegrade(sceneId,selfId)
	end
end

function x700044_OnRequestUpgrade(sceneId,selfId)
	local nCurrentLevel = GetFubenData_Param(sceneId,x700044_CSP_FUBENLEVEL)
	local nStdLevel = GetFubenData_Param(sceneId,x700044_CSP_FUBENLEVEL_DUP)

	if nCurrentLevel< (nStdLevel+5) then
		if x700044_g_LevelMax >= (nCurrentLevel+5) then
			SetFubenData_Param(sceneId,x700044_CSP_FUBENLEVEL, nCurrentLevel+5)

			x700044_ShowTipsToAll(sceneId, format("����ȼ�����5", nCurrentLevel+5))
		else
			
			BeginQuestEvent(sceneId);
			AddQuestText(sceneId, "�������ȼ����ƣ������Ѷ�ʧ��");
			EndQuestEvent(sceneId);

			DispatchQuestTips(sceneId, selfId);
			
		end
	else
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, "�Ѷ��Ѿ�����ˣ������Ѷ�ʧ��");
		EndQuestEvent(sceneId);

		DispatchQuestTips(sceneId, selfId);
	end

	
end

function x700044_OnRequestDegrade(sceneId,selfId)
	local nCurrentLevel = GetFubenData_Param(sceneId,x700044_CSP_FUBENLEVEL)
	local nStdLevel = GetFubenData_Param(sceneId,x700044_CSP_FUBENLEVEL_DUP)

	
	if nCurrentLevel> (nStdLevel-5) then
		if x700044_g_LevelMin <= (nCurrentLevel-5) then
			SetFubenData_Param(sceneId,x700044_CSP_FUBENLEVEL, nCurrentLevel-5)

			x700044_ShowTipsToAll(sceneId, format("����ȼ�����5", nCurrentLevel-5))
		else
			
			BeginQuestEvent(sceneId);
			AddQuestText(sceneId, "������С�ȼ����ƣ������Ѷ�ʧ��");
			EndQuestEvent(sceneId);

			DispatchQuestTips(sceneId, selfId);
			
		end
	else
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, "�Ѷ��Ѿ�����ˣ������Ѷ�ʧ��");
		EndQuestEvent(sceneId);

		DispatchQuestTips(sceneId, selfId);
	end
end


function x700044_ShowTipsToAll(sceneId, str)
	local humancount = GetFuben_PlayerCount(sceneId);
	for	i = 0, humancount - 1 do
		local humanId = GetFuben_PlayerObjId(sceneId, i);
		
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, str);
		EndQuestEvent(sceneId);

		DispatchQuestTips(sceneId, humanId);
	end
end