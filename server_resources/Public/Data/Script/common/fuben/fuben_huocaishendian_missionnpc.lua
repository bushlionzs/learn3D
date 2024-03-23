x700043_CSP_PAO_STATUS				=	15--x700003_CSP_PAO_STATUS
x700043_CSP_HUMAN_COUNT				=	240--x700003_CSP_HUMAN_COUNT
x700043_CSP_OBJID_START             =   241--x700003_CSP_OBJID_START
x700043_CSP_B_GETBONUS_START		=	230--x700003_CSP_B_GETBONUS_START
x700043_CSP_GUID_START              =   248

x700043_g_ScriptId = 700043


x700043_Fuben_ScriptId = 700003

function x700043_ProcEventEntry(sceneId, selfId, NPCId, MissionId,which)	--����������ִ�д˽ű�
	
	
	x700043_DispatchGetBonusInfo( sceneId, selfId, NPCId,which )
	
	
end


--**********************************

--�о��¼�

--**********************************

function x700043_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)
	


	local myGuid = GetPlayerGUID( sceneId,selfId )
	myGuid = format("%u", myGuid)
	local bFind = 0;

	for i=0, 5 do
        local paramidx = x700043_CSP_GUID_START + i
        local nGUID = GetFubenData_Param(sceneId, paramidx  )
				nGUID = format("%u", nGUID)
        if nGUID == myGuid then

			local bGetBonus = GetFubenData_Param(sceneId,x700043_CSP_B_GETBONUS_START+i)
			
			if bGetBonus>0 then
				return
			end

			bFind = 1;
			break;
           
        end
    end

	
	if bFind<=0 then
		return
	end

	 
	
	AddQuestNumText(sceneId, x700043_g_ScriptId, "��ȡ����",0,-1)
		
end





function x700043_DispatchGetBonusInfo( sceneId, selfId, NPCId, nParam )

	BeginQuestEvent(sceneId)

		--������Ϣ
		AddQuestText(sceneId,"#Y".."\t��������Ľ���")
		AddQuestText(sceneId,"ȷ����ȡ������")
		--AddQuestText(sceneId," ")

		


	EndQuestEvent()


	



	DispatchQuestInfo(sceneId, selfId, NPCId, x700043_g_ScriptId, -1);
end


---------------------------------------------------------------------------------------------------
--������븱��
---------------------------------------------------------------------------------------------------
function x700043_ProcAcceptCheck( sceneId, selfId, NPCId )
    return 1
end

----------------------------------------------------------------------------------------------
--��ȷ����
----------------------------------------------------------------------------------------------
function x700043_ProcAccept( sceneId, selfId )

	
	x700043_OnRequestGetBonus(sceneId, selfId )
	
end

function x700043_OnRequestGetBonus(sceneId, selfId )
	
	local myGuid = GetPlayerGUID( sceneId,selfId )
	myGuid = format("%u", myGuid)
	local bFind = 0;

	for i=0, 5 do
        local paramidx = x700043_CSP_GUID_START + i
        local nGUID = GetFubenData_Param(sceneId, paramidx  )
				nGUID = format("%u", nGUID)	
        if nGUID == myGuid then

			local bGetBonus = GetFubenData_Param(sceneId,x700043_CSP_B_GETBONUS_START+i)
			if bGetBonus>0 then
				BeginQuestEvent(sceneId);
				AddQuestText(sceneId, "���Ѿ���ȡ������");
				EndQuestEvent(sceneId);
				DispatchQuestTips(sceneId, selfId);
				return
			end

			SetFubenData_Param(sceneId,x700043_CSP_B_GETBONUS_START+i, 1)

			bFind = 1;
			break;
           
        end
    end
	
	

	if bFind<=0 then
		return
	end

	x700043_GiveBonusToHuman(sceneId, selfId )
end

function x700043_GiveBonusToHuman(sceneId, selfId )
	local nStatus = GetFubenData_Param(sceneId, x700043_CSP_PAO_STATUS )
	local level = GetLevel(sceneId, selfId)
	
	local nMoney =0
	if nStatus==1 then
		nMoney = level*50
	elseif nStatus==2 then
		nMoney = level*100+level*50
	else
		return
	end
	

	local strMoney = x700043_GetMoneyName(sceneId,nMoney)
	local str = format("���%s����������",strMoney)

	AddMoney(sceneId, selfId, 1, nMoney)

	
	
	BeginQuestEvent(sceneId);
	AddQuestText(sceneId, str);
	EndQuestEvent(sceneId);
	DispatchQuestTips(sceneId, selfId);
end


function x700043_GetMoneyName(sceneId,nMoney)
	local ding = floor(nMoney/(1000*1000))
	local liang = floor((nMoney-ding*1000*1000)/1000)
	local wen = nMoney-(ding*1000*1000+liang*1000)

	local str=""
	if ding>0 then
		str = str..format("%d��",ding)
	end

	if liang>0 then
		str = str..format("%d��",liang)
	end

	
	str = str..format("%d��",wen)

	return str;
	
end






