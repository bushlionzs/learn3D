--敌国刺探拉人

x300624_g_MissionName="【国家】国民召集"
x300624_g_CostIncrement = 5			--每次提交所扣金币的增量

--脚本号
x300624_g_ScriptId = 300624
x300624_g_CostMoney = 500*1000             --第3次以后拉人，每次所扣钱的增量
x300624_g_CountryID = 0             --楼兰国

x300624_g_CountryCheck = { 51, 151, 251, 351 }

x300624_g_MissionScript = "在敌国的活动中，大将军可以通过我进行国民的召集，每日可召集次数及所需金钱如下："
x300624_g_MissionFreeCount = 1

function x300624_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	--local country = GetCurCountry(sceneId, selfId)
	--if x300624_g_CountryCheck[country+1] == sceneId then
		--return
	--end
	
	--if IsKing(sceneId, selfId) == 1 then
	if( CountryGetOfficial(sceneId, selfId) == 6 ) then
		--如果是国王
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
	if MissionData ~= CurDaytime then					--上次拉人时间不是今天
 		local CountryID = GetCurCountry(sceneId,selfId)
		SetCountryQuestData(sceneId, CountryID, CD_INDEX_DESTROY_ISSUE_TIME, CurDaytime)
		SetCountryQuestData(sceneId, CountryID, CD_INDEX_DESTROY_ISSUE_COUNT,0)
	end
	
	GetCountryQuestData(sceneId,selfId,CD_INDEX_DESTROY_ISSUE_COUNT, x300624_g_ScriptId,-1,"OnReturn2")

	DispatchQuestEventList(sceneId, selfId, -1)
end


--判断拉人次数
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

	if nRank == 3 then --弱国
		 BeginQuestEvent(sceneId)
	 	
	 	 local showtext = x300624_g_MissionScript.."#r    ";


	 	 showtext = showtext .. preList[1].."第1次召集：免费"
		 showtext = showtext .. preList[2].."第2次召集：免费"
		 showtext = showtext .. preList[3].."第3次召集：免费"
	 	 showtext = showtext .. preList[4].."第4次召集：国家金钱250两"
	 	 showtext = showtext .. preList[5].."第5次召集：国家金钱250两"
	 	 showtext = showtext .. preList[6].."第6次召集：国家金钱250两"
	 	 showtext = showtext .. preList[7].."第7次召集：国家金钱250两"
	 	 AddQuestText(sceneId, showtext);
	 	 EndQuestEvent(sceneId)
	 	 DispatchQuestInfo( sceneId, selfId, -1, x300624_g_ScriptId,-1 )

	elseif nRank == 2 then --次弱国
		 BeginQuestEvent(sceneId)
	 	
	 	 local showtext = x300624_g_MissionScript.."#r    ";

	 	 showtext = showtext .. preList[1].."第1次召集：免费"
		 showtext = showtext .. preList[2].."第2次召集：免费"
	 	 showtext = showtext .. preList[3].."第3次召集：国家金钱375两"
	 	 showtext = showtext .. preList[4].."第4次召集：国家金钱375两"
	 	 showtext = showtext .. preList[5].."第5次召集：国家金钱375两"
	 	 showtext = showtext .. preList[6].."第6次召集：国家金钱375两"
	 	 AddQuestText(sceneId, showtext);
	 	 EndQuestEvent(sceneId)
	 	 DispatchQuestInfo( sceneId, selfId, -1, x300624_g_ScriptId,-1 )
	else
		 BeginQuestEvent(sceneId)
	 	
	 	 local showtext = x300624_g_MissionScript.."#r    ";

	 	 showtext = showtext .. preList[1].."第1次召集：免费"
	 	 showtext = showtext .. preList[2].."第2次召集：国家金钱500两"
	 	 showtext = showtext .. preList[3].."第3次召集：国家金钱500两"
	 	 showtext = showtext .. preList[4].."第4次召集：国家金钱500两"
	 	 showtext = showtext .. preList[5].."第5次召集：国家金钱500两"
	 	 AddQuestText(sceneId, showtext);
	 	 EndQuestEvent(sceneId)
	 	 DispatchQuestInfo( sceneId, selfId, -1, x300624_g_ScriptId,-1 )
	end

end
              

--第一次免费拉后的的拉人处理 
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
			AddQuestText( sceneId, format("很抱歉，大将军召集今天已发布%d次！",nDayLimited) )
		EndQuestEvent( sceneId )
		DispatchQuestTips( sceneId, selfId )
			
		return
	end

	if( CountryGetOfficial(sceneId, selfId) ~= 6 ) then
		BeginQuestEvent(sceneId)
			AddQuestText( sceneId,"很抱歉，只有大将军才能发布国民召集！" )
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
		--向本国广播
		local msg = "大将军发布了召集令";
		local countryid = GetCurCountry(sceneId,selfId)
		LuaAllScenceM2Country(sceneId,msg,countryid,5,0)		
	else

  	--local cost = (MissionData + 1 - 3) * x300624_g_CostMoney 
  		local cost = nNeedMoney 
	 	if GetCountryResource(sceneId, selfId,2) < cost then
			BeginQuestEvent(sceneId)
			AddQuestText( sceneId, "很抱歉，你的国家金钱不足，不可以召集！" )
			EndQuestEvent( sceneId )
			DispatchQuestTips( sceneId, selfId )
			Msg2Player(sceneId,selfId,"很抱歉，你的国家金钱不足，不可以召集！",8,2)
			return
		else
	      	--扣钱未绑定金币  
			SubCountryResource(sceneId, selfId,2,cost,1)
			local CountryID = GetCurCountry(sceneId,selfId)
			SetCountryQuestData(sceneId, CountryID, CD_INDEX_DESTROY_ISSUE_COUNT,1,1)
			SetCountryQuestData(sceneId, CountryID, CD_INDEX_DESTROY_ISSUE_SCENE, sceneId)
			KingIssue(sceneId, selfId) 
			--向本国广播
			local msg = "大将军发布了召集令";
			local countryid = GetCurCountry(sceneId,selfId)
			LuaAllScenceM2Country(sceneId,msg,countryid,5,0)
		end  
 	end


end

---------------------------------------------------------------------------------------------------
--取得当前次数
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
--设置当天次数
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