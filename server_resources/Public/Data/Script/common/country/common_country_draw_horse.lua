x300649_g_ScriptId = 300649
x300649_g_MissionName = "�����ҡ���ȡ��������"
-- ��ȡ���ﾭ��ֵ
x300649_g_LevelupTable  = {
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

function x300649_ProcEnumEvent( sceneId, selfId, targetId, index )
	
	AddQuestNumText(sceneId,x300649_g_ScriptId, x300649_g_MissionName, 8)
	
end

function x300649_ProcEventEntry( sceneId , selfId , targetId , state , index )

	BeginQuestEvent(sceneId)
	local Readme_1 ="#Y�����ҡ���ȡ��������#W#r"
	local Readme_2 ="\t��ֻΪ����#G����#W��#G����#W�������ǿ�������������ȡ#G����ר������#W��#r" 
	local Readme_3 ="\t�����������ݹ��������󣩱��˵ĵȼ���#G�Զ���Ϊ��Ӧ�ļ���#W��#r"
	local Readme_4 ="\t���#G�󽫹����������#W��û�б�Ҫ���ģ����������󣩿�����ʱ��������#G������ȡ#W��"
		  local Readme = Readme_1..Readme_2.. Readme_3..Readme_4
			AddQuestText(sceneId,Readme)
			EndQuestEvent(sceneId)	
		DispatchQuestInfo(sceneId,selfId,targetId,x300649_g_ScriptId,-1)

	return 
		
end

--********************
--����������
--**********************************
function x300649_ProcAcceptCheck( sceneId, selfId, NPCId )
		return 1
end

--**********************************
--����
--**********************************
function x300649_ProcAccept( sceneId, selfId )
	
	local pos = CountryGetOfficial(sceneId, selfId)

	if pos ~= 8 and pos ~= 7 then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "�ܱ�Ǹ�������ǹ���Ҳ������������ȡ��")
		DispatchQuestTips(sceneId, selfId)
		EndQuestEvent(sceneId)
		Msg2Player(sceneId,selfId,"�ܱ�Ǹ�������ǹ���Ҳ������������ȡ��",8,2)
		return
	end 

	if IsHaveHorse(sceneId, selfId, 3001) > 0 or
		IsHaveHorse(sceneId, selfId, 3002) > 0 or
		IsHaveHorse(sceneId, selfId, 3003) > 0 or
		IsHaveHorse(sceneId, selfId, 3004) > 0 or
		IsHaveHorse(sceneId, selfId, 3005) > 0 or
		IsHaveHorse(sceneId, selfId, 3006) > 0 or
		IsHaveHorse(sceneId, selfId, 3007) > 0 or
		IsHaveHorse(sceneId, selfId, 3008) > 0 then
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId, "�ܱ�Ǹ��������˲�����ȡ��")
			DispatchQuestTips(sceneId, selfId)
			EndQuestEvent(sceneId)
			Msg2Player(sceneId,selfId,"�ܱ�Ǹ��������˲�����ȡ��",8,2)
			return
	end

	local level = GetLevel(sceneId, selfId)
	local horseId = -1;
	if level>=30 and level <40 then
		horseId = 3001
	elseif level>=40 and level <50 then
		horseId = 3002
	elseif level >=50 and level <60 then
		horseId = 3003
	elseif level >=60 and level <70 then
		horseId = 3004
	elseif level >=70 and level <80 then
		horseId = 3005
	elseif level >=80 and level <90 then
		horseId = 3006
	elseif level >=90 and level <100 then
		horseId = 3007
	elseif level >=100 then
		horseId = 3008
	end

	if horseId == -1 then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "�ܱ�Ǹ�����ĵȼ�������")
		DispatchQuestTips(sceneId, selfId)
		EndQuestEvent(sceneId)
		Msg2Player(sceneId,selfId,"�ܱ�Ǹ�����ĵȼ�������",8,2)
		return
	end

	if CreateHorseToPlayer(sceneId, selfId, horseId, -1) < 0 then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "�ܱ�Ǹ������������������������ȡ��")
		DispatchQuestTips(sceneId, selfId)
		EndQuestEvent(sceneId)
		Msg2Player(sceneId,selfId,"�ܱ�Ǹ������������������������ȡ��",8,2)
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
            AddHorseExp( sceneId, selfId, idx, x300649_g_LevelupTable[ i], 1)
        else
            AddHorseExp( sceneId, selfId, idx, x300649_g_LevelupTable[ i], 0)
        end
    end

end

