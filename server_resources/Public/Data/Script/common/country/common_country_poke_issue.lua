--�й���̽����

x300624_g_MissionName="�����ҡ������ټ�"
x300624_g_CostIncrement = 5			--ÿ���ύ���۽�ҵ�����

--�ű���
x300624_g_ScriptId = 300624
x300624_g_CostMoney = 500*1000             --��3���Ժ����ˣ�ÿ������Ǯ������
x300624_g_CountryID = 0             --¥����

x300624_g_CountryCheck = { 51, 151, 251, 351 }

x300624_g_MissionScript = "�ڵй��Ļ�У��󽫾�����ͨ���ҽ��й�����ټ���ÿ�տ��ټ������������Ǯ���£�"
x300624_g_MissionFreeCount = 1

function x300624_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	--local country = GetCurCountry(sceneId, selfId)
	--if x300624_g_CountryCheck[country+1] == sceneId then
		--return
	--end
	
	--if IsKing(sceneId, selfId) == 1 then
	if( CountryGetOfficial(sceneId, selfId) == 6 ) then
		--����ǹ���
		AddQuestNumText(sceneId,x300624_g_ScriptId,x300624_g_MissionName,3)
    end
end



function x300624_ProcEventEntry( sceneId, selfId, targetId )
 	--DispatchQuestInfo( sceneId, selfId, targetId, x300624_g_ScriptId,-1 )    
 	GetCountryQuestData(sceneId,selfId,CD_INDEX_DESTROY_ISSUE_TIME, x300624_g_ScriptId,-1,"OnReturn1")
end


function x300624_ProcAcceptCheck( sceneId, selfId, NPCId )
  	GetCountryQuestData(sceneId,selfId,CD_INDEX_DESTROY_ISSUE_COUNT, x300624_g_ScriptId,-1,"OnReturn3")
end


function x300624_OnReturn1(sceneId, selfId,MissionData,MissionId)

	local CurDaytime = GetDayTime()
	if MissionData ~= CurDaytime then					--�ϴ�����ʱ�䲻�ǽ���
 		local CountryID = GetCurCountry(sceneId,selfId)
		SetCountryQuestData(sceneId, CountryID, CD_INDEX_DESTROY_ISSUE_TIME, CurDaytime)
		SetCountryQuestData(sceneId, CountryID, CD_INDEX_DESTROY_ISSUE_COUNT,0)
	end
	
	GetCountryQuestData(sceneId,selfId,CD_INDEX_DESTROY_ISSUE_COUNT, x300624_g_ScriptId,-1,"OnReturn2")

	DispatchQuestEventList(sceneId, selfId, -1)
end


--�ж����˴���
function x300624_OnReturn2(sceneId, selfId,MissionData,MissionId)
	
	local nCountry = GetCurCountry(sceneId, selfId)

	local nRank = GetCountryRank(nCountry)

	if MissionData<0 then
		MissionData = 0
	end
	
	local preList = {}

	 for i=1, MissionData do
		preList[i] = "#r#d"
	 end

	 for i=MissionData+1, 7 do
		preList[i] = "#r#W"
	 end

	if nRank == 3 then --����
		 BeginQuestEvent(sceneId)
	 	
	 	 local showtext = x300624_g_MissionScript.."#r    ";


	 	 showtext = showtext .. preList[1].."��1���ټ������"
		 showtext = showtext .. preList[2].."��2���ټ������"
		 showtext = showtext .. preList[3].."��3���ټ������"
	 	 showtext = showtext .. preList[4].."��4���ټ������ҽ�Ǯ250��"
	 	 showtext = showtext .. preList[5].."��5���ټ������ҽ�Ǯ250��"
	 	 showtext = showtext .. preList[6].."��6���ټ������ҽ�Ǯ250��"
	 	 showtext = showtext .. preList[7].."��7���ټ������ҽ�Ǯ250��"
	 	 AddQuestText(sceneId, showtext);
	 	 EndQuestEvent(sceneId)
	 	 DispatchQuestInfo( sceneId, selfId, -1, x300624_g_ScriptId,-1 )

	elseif nRank == 2 then --������
		 BeginQuestEvent(sceneId)
	 	
	 	 local showtext = x300624_g_MissionScript.."#r    ";

	 	 showtext = showtext .. preList[1].."��1���ټ������"
		 showtext = showtext .. preList[2].."��2���ټ������"
	 	 showtext = showtext .. preList[3].."��3���ټ������ҽ�Ǯ375��"
	 	 showtext = showtext .. preList[4].."��4���ټ������ҽ�Ǯ375��"
	 	 showtext = showtext .. preList[5].."��5���ټ������ҽ�Ǯ375��"
	 	 showtext = showtext .. preList[6].."��6���ټ������ҽ�Ǯ375��"
	 	 AddQuestText(sceneId, showtext);
	 	 EndQuestEvent(sceneId)
	 	 DispatchQuestInfo( sceneId, selfId, -1, x300624_g_ScriptId,-1 )
	else
		 BeginQuestEvent(sceneId)
	 	
	 	 local showtext = x300624_g_MissionScript.."#r    ";

	 	 showtext = showtext .. preList[1].."��1���ټ������"
	 	 showtext = showtext .. preList[2].."��2���ټ������ҽ�Ǯ500��"
	 	 showtext = showtext .. preList[3].."��3���ټ������ҽ�Ǯ500��"
	 	 showtext = showtext .. preList[4].."��4���ټ������ҽ�Ǯ500��"
	 	 showtext = showtext .. preList[5].."��5���ټ������ҽ�Ǯ500��"
	 	 AddQuestText(sceneId, showtext);
	 	 EndQuestEvent(sceneId)
	 	 DispatchQuestInfo( sceneId, selfId, -1, x300624_g_ScriptId,-1 )
	end

end
              

--��һ���������ĵ����˴��� 
function x300624_OnReturn3(sceneId, selfId,MissionData,MissionId)
	local nCountry = GetCurCountry(sceneId, selfId)

	local nRank = GetCountryRank(nCountry)
	
	local nDayLimited = 5
	local nFreeCount =1
	local nNeedMoney = 500*1000

	if nRank ==3 then
		nFreeCount = 3
		nNeedMoney = 250*1000
		nDayLimited = 7
	elseif nRank ==2 then
		nFreeCount = 2
		nNeedMoney = 375*1000
		nDayLimited = 6
	end

	if x300624_GetDayCount(sceneId, selfId)>=nDayLimited then
		BeginQuestEvent(sceneId)
			AddQuestText( sceneId, format("�ܱ�Ǹ���󽫾��ټ������ѷ���%d�Σ�",nDayLimited) )
		EndQuestEvent( sceneId )
		DispatchQuestTips( sceneId, selfId )
			
		return
	end

	if( CountryGetOfficial(sceneId, selfId) ~= 6 ) then
		BeginQuestEvent(sceneId)
			AddQuestText( sceneId,"�ܱ�Ǹ��ֻ�д󽫾����ܷ��������ټ���" )
		EndQuestEvent( sceneId )
		DispatchQuestTips( sceneId, selfId )
			
		return
	end

	if (MissionData < nFreeCount) then
		local CountryID = GetCurCountry(sceneId,selfId)
--	PrintStr(tostring(MissionData));
		SetCountryQuestData(sceneId, CountryID, CD_INDEX_DESTROY_ISSUE_COUNT,1,1)
		SetCountryQuestData(sceneId, CountryID, CD_INDEX_DESTROY_ISSUE_SCENE, sceneId)
		KingIssue(sceneId, selfId) 
		--�򱾹��㲥
		local msg = "�󽫾��������ټ���";
		local countryid = GetCurCountry(sceneId,selfId)
		LuaAllScenceM2Country(sceneId,msg,countryid,5,0)		
	else

  	--local cost = (MissionData + 1 - 3) * x300624_g_CostMoney 
  		local cost = nNeedMoney 
	 	if GetCountryResource(sceneId, selfId,2) < cost then
			BeginQuestEvent(sceneId)
			AddQuestText( sceneId, "�ܱ�Ǹ����Ĺ��ҽ�Ǯ���㣬�������ټ���" )
			EndQuestEvent( sceneId )
			DispatchQuestTips( sceneId, selfId )
			Msg2Player(sceneId,selfId,"�ܱ�Ǹ����Ĺ��ҽ�Ǯ���㣬�������ټ���",8,2)
			return
		else
	      	--��Ǯδ�󶨽��  
			SubCountryResource(sceneId, selfId,2,cost,1)
			local CountryID = GetCurCountry(sceneId,selfId)
			SetCountryQuestData(sceneId, CountryID, CD_INDEX_DESTROY_ISSUE_COUNT,1,1)
			SetCountryQuestData(sceneId, CountryID, CD_INDEX_DESTROY_ISSUE_SCENE, sceneId)
			KingIssue(sceneId, selfId) 
			--�򱾹��㲥
			local msg = "�󽫾��������ټ���";
			local countryid = GetCurCountry(sceneId,selfId)
			LuaAllScenceM2Country(sceneId,msg,countryid,5,0)
		end  
 	end


end

---------------------------------------------------------------------------------------------------
--ȡ�õ�ǰ����
---------------------------------------------------------------------------------------------------
function x300624_GetDayCount(sceneId, selfId)
	local nCountry = GetCurCountry(sceneId, selfId)

	local today = GetDayTime()
	local lastday = GetCountryParam(sceneId, nCountry, CD_INDEX_DESTROY_ISSUE_TIME)
	
	
	if lastday ~= today then
		return 0
	end
	
	local daycount = GetCountryParam(sceneId, nCountry, CD_INDEX_DESTROY_ISSUE_COUNT)
	
	return daycount;
end

---------------------------------------------------------------------------------------------------
--���õ������
---------------------------------------------------------------------------------------------------
function x300624_SetDayCount(sceneId, selfId)
	local nCountry = GetCurCountry(sceneId, selfId)

	local today = GetDayTime()

	local lastday = GetCountryParam(sceneId, nCountry, CD_INDEX_DESTROY_ISSUE_TIME)

	if lastday ~= today then
		SetCountryParam(sceneId, nCountry, CD_INDEX_DESTROY_ISSUE_TIME, today)
		SetCountryParam(sceneId, nCountry, CD_INDEX_DESTROY_ISSUE_COUNT, 1)
	else
		local daycount = GetCountryParam(sceneId, nCountry, CD_INDEX_DESTROY_ISSUE_COUNT)
		SetCountryParam(sceneId, nCountry, CD_INDEX_DESTROY_ISSUE_COUNT, daycount+1)
	end
end