x300819_g_ScriptId	= 300819
x300819_g_MissionName = "【国家】改变国籍"
x300819_g_SubMissions = {
						{countryid=0,scriptid=300820,name="前往楼兰王国"},
						{countryid=1,scriptid=300821,name="前往天山王国"},
						{countryid=2,scriptid=300822,name="前往昆仑王国"},
						{countryid=3,scriptid=300823,name="前往敦煌王国"}
						}

function x300819_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	local level = GetLevel(sceneId, selfId)
	if level >= 40 then
		AddQuestNumText(sceneId,300819,x300819_g_MissionName,3)
	end
end

--点击（按钮）点击该任务后执行此脚本
function x300819_ProcEventEntry( sceneId, selfId, targetId)

	BeginQuestEvent(sceneId)

		local Readme_1 = "#Y【国家】改变国籍#r#W #r"
		local Readme_2 = "   您是否想去一个崭新的国度发展呢？#r"
		local Readme_3 = "   我能帮您实现您的愿望，只要花费一些#Y现金#W，我立刻可以把您送到您想要去的国家，并成为他们国家的一员。#r#r"
		local Readme_4 ="    您可以通过选择以下按钮来进行改变国籍。#r"
		local Readme_5= "#G提示：放弃国籍需要扣除您50两现金。"
		local Readme = Readme_1..Readme_2..Readme_3..Readme_4..Readme_5
		AddQuestText( sceneId,Readme)

		local cid = GetCurCountry(sceneId, selfId)
		for i,item in x300819_g_SubMissions do
			if cid ~= item.countryid then
				local nCost = x300819_GetBetrayCost(item.countryid)
				local name = item.name .. "(#c780000现金" .. floor(nCost/1000) .. "两#K)"
				AddQuestNumText( sceneId, item.scriptid, name, 3, item.countryid );
			end
		end

	EndQuestEvent(sceneId)

	DispatchQuestEventList(sceneId,selfId,targetId);

end



--点击（确定）
function x300819_ProcAcceptCheck( sceneId, selfId, NPCId )
end

--**********************************
--接受
--**********************************
function x300819_ProcAccept( sceneId, selfId )
end
--**********************************
--放弃
--**********************************
function x300819_ProcQuestAbandon( sceneId, selfId, MissionId )
end
--**********************************
--继续
--**********************************
function x300819_OnContinue( sceneId, selfId, targetId )
end
--**********************************
--检测是否可以提交
--**********************************
function x300819_CheckSubmit( sceneId, selfId )
end
--**********************************
--提交
--**********************************
function x300819_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )
end
--**********************************
--杀死怪物或玩家
--**********************************
function x300819_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )
end
--**********************************
--进入区域事件
--**********************************
function x300819_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end
--**********************************
--道具改变
--**********************************
function x300819_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end


-- 取得叛国需要的金卡钱数，单位文
function x300819_GetBetrayCost( countryId )

	local nRank = GetCountryRank(countryId)
	local nCost = 0
	
	if nRank == 0 then 
		nCost = 50000		--强国
	elseif nRank == 1 or nRank == 2 then 
		nCost = 50000		--中等国
	elseif nRank == 3 then 
		nCost = 50000		--弱国
	end	
	
	return nCost
	
end