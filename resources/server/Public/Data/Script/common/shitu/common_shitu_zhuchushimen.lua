--逐出师门任务

--脚本号
x800011_g_ScriptId	= 800011

x800011_g_MissionName	= "【师徒】开除徒弟"

--开除徒弟，扣除金钱
x800011_g_Gold			= 5000
x800011_g_CostMoneyType  		= 2
x800011_g_Item = 11990111
x800011_g_PrenticeCount = 5
--**********************************
--任务入口函数
--**********************************
function x800011_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	AddQuestNumText(sceneId, x800011_g_ScriptId, x800011_g_MissionName,3,0);
end

function x800011_ProcEventEntry(sceneId, selfId, targetId, eventId, index)
	local	key	= index
	local guid
	local PrenticeName
	local	isHavePrentice	= 0
	local	str
	if key == 0 then
		BeginQuestEvent( sceneId )
		for i=0, x800011_g_PrenticeCount - 1 do
			guid = GetPrenticeGUID( sceneId, selfId, i )
			if guid ~= -1 then
				isHavePrentice	= 1
				PrenticeName	= GetFriendName( sceneId, selfId, guid )
				AddQuestText( sceneId, "#Y"..x800011_g_MissionName.."#W")
				AddQuestText( sceneId, "\t开除徒弟后，不会再从此人及其徒弟那里获得威望收益。请慎重考虑后选择与哪位徒弟解除师徒关系。")
				AddQuestNumText( sceneId, x800011_g_ScriptId, "与"..PrenticeName.."解除师徒关系", -1, (i+1)*100 )
			end
		end
		if isHavePrentice == 0 then
			AddQuestText( sceneId, "很抱歉，您还不是师傅，无法开除徒弟。" )
		end
		EndQuestEvent( sceneId )
		DispatchQuestEventList( sceneId, selfId, targetId )
	end
	
	if key >= 100 and key < 10000 then
		key = floor(key/100)-1
		guid	= GetPrenticeGUID( sceneId, selfId, key )
		if guid ~= -1 then
			PrenticeName	= GetFriendName( sceneId, selfId, guid )
		end
		str	= format( "此处说明需要的东西" )
		BeginQuestEvent( sceneId )
			--AddQuestText( sceneId, str )
			AddQuestNumText( sceneId, x800011_g_ScriptId, "是", -1, (key+1)*10000 )
		EndQuestEvent( sceneId )
		DispatchQuestEventList( sceneId, selfId, targetId )
	end
	
	if key >= 10000 then
			key = floor(key/10000)-1
			x800011_ProcAccept( sceneId, selfId, key )
	end
		
	--local Readme_1 = "#Y【师徒】开除徒弟#r"
	--local Readme_2 = "\t#W我可以帮助您解除与徒弟的关系。#r您是否要开除徒弟？"
	--local Readme = Readme_1..Readme_2
	--BeginQuestEvent(sceneId);
	--AddQuestText(sceneId, Readme);
	--EndQuestEvent();
	--DispatchQuestInfo(sceneId, selfId, targetId, x800011_g_ScriptId,-1);

end

-------------------------
--***********************
--ProcAcceptCheck
--***********************
-------------------------

function x800011_ProcAcceptCheck(sceneId, selfId, targetId)

	return 1;

end

--**********************************
--列举事件
--**********************************


--**********************************
--接受
--**********************************
function x800011_ProcAccept( sceneId, selfId, index )
	
	local PrenticeGUID = GetPrenticeGUID( sceneId, selfId, index )
	if PrenticeGUID == -1 then
		Msg2Player(sceneId,selfId,"很抱歉，您还不是师傅，无法开除徒弟。",8,2)
		Msg2Player(sceneId,selfId,"很抱歉，您还不是师傅，无法开除徒弟。",8,3)
		return
	end
	
	--if GetMoney( sceneId, selfId, x800011_g_CostMoneyType ) < x800011_g_Gold then
	--	local str = format("很抱歉，您包裹中的现金不足%d两，无法开除徒弟。", x800011_g_Gold/1000);
	--	Msg2Player(sceneId,selfId,str,8,2)
	--	return
	--end
	
	--if HaveItemInBag(sceneId, selfId, x800011_g_Item) ~= 1 then
	--	local str = format("很抱歉，您包裹中的没有@item_%d，无法开除徒弟。", x800011_g_Item);
	--	Msg2Player(sceneId,selfId,str,8,2)
	--	return
	--end
	
	local PrenticeName	= GetFriendName( sceneId, selfId, PrenticeGUID )
	local selfName	= GetName( sceneId, selfId )

	--扣除身上金钱
	--if CostMoney(sceneId, selfId, x800011_g_CostMoneyType, x800011_g_Gold) == -1 then
	--	Msg2Player(sceneId,selfId,"扣金钱失败！",8,2)
	--	return
	--end
	--if DelItem(sceneId, selfId, x800011_g_Item, 1) ~= 1 then
	--	Msg2Player(sceneId,selfId,"扣物品失败！",8,2)
	--	return
	--end
	
	local Msg = format("很遗憾，您解除了与徒弟%s的师徒关系", PrenticeName);
	Msg2Player(sceneId,selfId,Msg,8,2)
	Msg2Player(sceneId,selfId,Msg,8,3)
	--发普通邮件给徒弟
	SendSystemMail( sceneId, PrenticeName, "很遗憾，您的师傅" .. selfName .. "与您解除了师徒关系。" )
	--发可执行邮件给徒弟
	SendScriptMail( sceneId, PrenticeName, MAIL_EXPELPRENTICE, 1, GetGUID(sceneId, selfId), 0, selfId )
	--最终清理门户
	ExpelPrentice( sceneId, selfId, PrenticeGUID, 2 )
end
