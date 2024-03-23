
x920007_g_ScriptId 					= 920007
x920007_g_MissionName				= "【师徒】升级师傅称号"

x920007_g_Title_Cachet_Table 					= {
										{titleID = 9, titleName = "初为人师", cachet = 0, num = 1},
										{titleID = 10, titleName = "为人师表", cachet = 2500, num = 2},
										{titleID = 11, titleName = "诲人不倦", cachet = 10000, num = 3},
										{titleID = 12, titleName = "厚德树人", cachet = 30000 , num = 4},
										{titleID = 13, titleName = "名扬四海", cachet = 80000,num = 5},
								}

x920007_g_Title_Cachet_Table_Count				=	5


function x920007_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
	AddQuestNumText(sceneId,x920007_g_ScriptId,x920007_g_MissionName,3,0);
end

function x920007_ProcEventEntry(sceneId, selfId, targetId)
	local nCurTitle = GetTitleForPrenticeCount(sceneId, selfId)
	local str = nil

	if nCurTitle == 0 then
		str = "\t您还不是师傅，请先收一个徒弟获得师傅称号之后再来升级师傅称号。"
		--Msg2Player(sceneId,selfId,ret,8,2)
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, str);
		EndQuestEvent();
		DispatchQuestEventList( sceneId, selfId, targetId)
		--DispatchQuestInfo(sceneId, selfId, targetId, x920007_g_ScriptId,-1)
		return
	end
	
	local i = 1
	for j,item in x920007_g_Title_Cachet_Table do
		if item.titleID == nCurTitle then
			if i >= x920007_g_Title_Cachet_Table_Count then
				str = "\t您的师徒称号已经为顶级了，无法升级。"
				--Msg2Player(sceneId,selfId,ret,8,2)
				BeginQuestEvent(sceneId);
				AddQuestText(sceneId, str);
				EndQuestEvent();
				DispatchQuestEventList( sceneId, selfId, targetId)
				--DispatchQuestInfo(sceneId, selfId, targetId, x920007_g_ScriptId,-1)
				return
			end

			break
		end
		i = i + 1
		
	end

	str = format("\t是否花费%d威望将师徒称号升级为%s?升级后你可以最多收%d个徒弟。", x920007_g_Title_Cachet_Table[i + 1].cachet, x920007_g_Title_Cachet_Table[i + 1].titleName , x920007_g_Title_Cachet_Table[i + 1].num)
	local value = GetPlayerGoodBadValue(sceneId, selfId)
	BeginQuestEvent(sceneId);
	AddQuestText(sceneId, str);
	AddQuestText(sceneId, "\n\t#Y你当前威望值为："..value);
	EndQuestEvent();
	DispatchQuestInfo(sceneId, selfId, targetId, x920007_g_ScriptId,-1)
	
end

function x920007_ProcAcceptCheck(sceneId, selfId, targetId)

	return 1;

end

function x920007_ProcAccept(sceneId, selfId, targetId)
	
	local nCurTitle = GetTitleForPrenticeCount(sceneId, selfId)
	local ret = nil

	if nCurTitle == 0 then
		--ret = "你未获得过师徒称号，请先收一个徒弟，获得初始化称号"
		--Msg2Player(sceneId,selfId,ret,8,2)
		return
	end
	
	local i = 1
	for j,item in x920007_g_Title_Cachet_Table do
		if item.titleID == nCurTitle then
			if i >= x920007_g_Title_Cachet_Table_Count then
				--ret = "你的称号已经是最高等级"
				--Msg2Player(sceneId,selfId,ret,8,2)
				return
			end

			break
		end
		i = i + 1
		
	end
	
	local value = GetPlayerGoodBadValue(sceneId, selfId)
	if value < x920007_g_Title_Cachet_Table[i + 1].cachet then
		ret = "你的威望值不足！";
		Msg2Player(sceneId,selfId,ret,8,3)
		Msg2Player(sceneId,selfId,ret,8,2)
		return
	end

	value = value - x920007_g_Title_Cachet_Table[i + 1].cachet

	SetPlayerGoodBadValue(sceneId, selfId, value)

	ChangeTitleForPrenticeCount(sceneId, selfId, x920007_g_Title_Cachet_Table[i + 1].titleID)

	Msg2Player(sceneId,selfId,"师傅称号升级成功",8,3)
	Msg2Player(sceneId,selfId,"师傅称号升级成功",8,2)

end