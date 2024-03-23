x300652_g_ScriptId = 300652
x300652_g_MissionName = "【国家】领取守护坐骑"
-- 领取坐骑经验值
x300652_g_LevelupTable  = {
                            4, 
                            15, 
                            47, 
                            109, 
                            210, 
                            362, 
                            574, 
                            855, 
                            1217, 
                            1669, 
                            2220, 
                            2882, 
                            3664, 
                            4575, 
                            5627, 
                            6829, 
                            8190, 
                            9722, 
                            11434, 
                            22986, 
                            31937, 
                            40000, 
                            50193, 
                            62608, 
                            67064, 
                            74281, 
                            86642, 
                            100864, 
                            103664, 
                            208524, 
                            220109, 
                            231694, 
                            244933, 
                            256518, 
                            269758, 
                            282997, 
                            296237, 
                            309476, 
                            635502, 
                            809312, 
                            847563, 
                            883801, 
                            924065, 
                            964330, 
                            1006607, 
                            1048885, 
                            1093175, 
                            1137466, 
                            2323249, 
                            1907721, 
                            1984677, 
                            2063660, 
                            2146692, 
                            3278768, 
                            2671214, 
                            2774498, 
                            2879807, 
                            2989167, 
                            4560707, 
                            4670725, 
                            5698285, 
                            6950039, 
                            8474564, 
                            10330897, 
                            15738475, 
                            17578666, 
                            19629511, 
                            21914737, 
                            33355519, 
                            33879680, 
                            41236410, 
                            50180645, 
                            61053118, 
                            74267355, 
                            150541935, 
                            167804077, 
                            187013227, 
                            208386168, 
                            232163564, 
                            235975844, 
                            241528216, 
                            247080589, 
                            252632962, 
                            258185335, 
                            263737708, 
                            269290080, 
                            274842453, 
                            280394826, 
                            288666096, 
                            288666096, 
                            288666096, 
                            288666096, 
                            288666096, 
                            288666096, 
                            288666096, 
                            288666096, 
                            288666096, 
                            288666096, 
                            288666096, 
                            743026531, 
                            743026531, 
                            743026531, 
                            743026531, 
                            743026531, 
                            743026531, 
                            743026531, 
                            743026531, 
                            743026531, 
                            743026531, 
                            743026531, 
                            743026531, 
                            743026531, 
                            743026531, 
                            743026531, 
                            743026531, 
                            743026531, 
                            743026531, 
                            743026531, 
                            743026531, 
                            743026531, 
                            743026531, 
                            743026531, 
                            743026531, 
                            743026531, 
                            743026531, 
                            743026531, 
                            743026531, 
                            743026531, 
                            743026531, 
                            743026531, 
                            743026531, 
                            743026531, 
                            743026531, 
                            743026531, 
                            743026531, 
                            743026531, 
                            743026531, 
                            743026531, 
                            743026531, 
                            743026531, 
                            743026531, 
                            743026531, 
                            743026531, 
                            743026531, 
                            743026531, 
                            743026531, 
                            743026531, 
                            743026531, 
                            743026531, 
                            743026531, 
                            743026531, 
                            743026531, 
                            743026531, 
                            743026531, 
                            743026531, 
                            743026531, 
                            743026531, 
                            743026531, 
                            743026531, 
                            743026531
}


function x300652_ProcEnumEvent( sceneId, selfId, targetId, index )
	
	AddQuestNumText(sceneId,x300652_g_ScriptId, x300652_g_MissionName, 8)
	
end

function x300652_ProcEventEntry( sceneId , selfId , targetId , state , index )

	BeginQuestEvent(sceneId)
	local Readme_1 ="#Y【国家】领取守护坐骑#W#r"
	local Readme_2 ="\t我只为本国#G青龙之主#W和#G朱雀之主#W服务，他们可以在我这里领取#G守护专有坐骑#W。#r" 
	local Readme_3 ="\t守护坐骑，会根据守护本人的等级，#G自动成为相应的级别#W。#r"
	local Readme_4 ="\t如果#G误将守护坐骑放生#W，没有必要担心，可以随时在我这里#G重新领取#W。"
		  local Readme = Readme_1..Readme_2.. Readme_3..Readme_4
			AddQuestText(sceneId,Readme)
			EndQuestEvent(sceneId)	
			DispatchQuestInfo(sceneId,selfId,targetId,x300652_g_ScriptId,-1)

	return 
		
end

--********************
--检测接受条件
--**********************************
function x300652_ProcAcceptCheck( sceneId, selfId, NPCId )
		return 1
end

--**********************************
--接受
--**********************************
function x300652_ProcAccept( sceneId, selfId )
	local qinglong = IsQinglongZhuque(sceneId,selfId,0)
	local zhuque = IsQinglongZhuque(sceneId,selfId,1)
	if qinglong ~= 1 and zhuque ~= 1 then 
	BeginQuestEvent(sceneId)
	AddQuestText(sceneId, "很抱歉，您不是青龙之主也不是朱雀之主不能领取。")
	DispatchQuestTips(sceneId, selfId)
	EndQuestEvent(sceneId)
	Msg2Player(sceneId,selfId,"很抱歉，您不是青龙之主也不是朱雀之主不能领取。",8,2)
	return 
	end 

	if  IsHaveHorse(sceneId, selfId, 3011) > 0 or
		IsHaveHorse(sceneId, selfId, 3012) > 0 or
		IsHaveHorse(sceneId, selfId, 3013) > 0 or
		IsHaveHorse(sceneId, selfId, 3014) > 0 or
		IsHaveHorse(sceneId, selfId, 3015) > 0 or
		IsHaveHorse(sceneId, selfId, 3016) > 0 or
		IsHaveHorse(sceneId, selfId, 3017) > 0 or
		IsHaveHorse(sceneId, selfId, 3018) > 0 then
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId, "很抱歉，您已有守护坐骑，不能领取。")
			DispatchQuestTips(sceneId, selfId)
			EndQuestEvent(sceneId)
			Msg2Player(sceneId,selfId,"很抱歉，您已有守护坐骑，不能领取。",8,2)
			return
	end

	local level = GetLevel(sceneId, selfId)
	local horseId = -1;
	if level>=30 and level <40 then
		horseId = 3011
	elseif level>=40 and level <50 then
		horseId = 3012
	elseif level >=50 and level <60 then
		horseId = 3013
	elseif level >=60 and level <70 then
		horseId = 3014
	elseif level >=70 and level <80 then
		horseId = 3015
	elseif level >=80 and level <90 then
		horseId = 3016
	elseif level >=90 and level <100 then
		horseId = 3017
	elseif level >=100 then
		horseId = 3018
	end

	if horseId == -1 then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "很抱歉，您的等级不够。")
		DispatchQuestTips(sceneId, selfId)
		EndQuestEvent(sceneId)
		Msg2Player(sceneId,selfId,"很抱歉，您的等级不够。",8,2)
		return
	end

	if CreateHorseToPlayer(sceneId, selfId, horseId, -1) < 0 then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "很抱歉，您的坐骑栏已满，不能领取。")
		DispatchQuestTips(sceneId, selfId)
		EndQuestEvent(sceneId)
		Msg2Player(sceneId,selfId,"很抱歉，您的坐骑栏已满，不能领取。",8,2)
		return
	end

    local count = GetPetCount( sceneId, selfId)
    local idx = 0
    for i = 0, count - 1 do
        if GetHorseDataID( sceneId, selfId, i) == horseId then
            idx = i
            break
        end
    end

    for i = 1, level - 1 do
        if i == level - 1 then
            AddHorseExp( sceneId, selfId, idx, x300652_g_LevelupTable[ i], 1)
        else
            AddHorseExp( sceneId, selfId, idx, x300652_g_LevelupTable[ i], 0)
        end
    end

end

