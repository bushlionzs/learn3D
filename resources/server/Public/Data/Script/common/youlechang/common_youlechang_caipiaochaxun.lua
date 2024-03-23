x310337_g_ScriptId 		= 310337
-- 幸运券查询
x310337_g_ScriptName	= "查询本次乐透大奖号码"

x310337_g_TitleInfo		= "#Y乐透大奖开奖号码\n\t#W这可是一个激动人心的数字，它代表着巨额的财富！本次乐透大奖的中奖号码是：\n"
x310337_g_TitleInfo1		= "#W\n\t亲爱的朋友，你中奖了吗？如果这次的号码和你无缘，请期待下次的开奖！"
x310337_g_TitleInfo2		= "#W\t亲爱的朋友，乐透大奖在10：30才会进行第一次开奖。"

						
function x310337_ProcEventEntry(sceneId, selfId, NPCId, MissionId,idExt)	--点击该任务后执行此脚本
	local index = GetCountryParam( sceneId, 0, CD_YOULECHANG_CAIPIAO1)
	if index <= 0 then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"#Y"..x310337_g_TitleInfo2)
		EndQuestEvent()
		DispatchQuestEventList(sceneId, selfId, NPCId)      
	end	
	if index > 0 then
	BeginQuestEvent(sceneId)
		--任务信息
		AddQuestText(sceneId,"#Y"..x310337_g_TitleInfo)
		
		index = GetCountryParam( sceneId, 1, CD_YOULECHANG_CAIPIAO1)
		if index > 0 then
			AddQuestText(sceneId,"\t\t\t#Y"..index)
			
		end
		index = GetCountryParam( sceneId, 2, CD_YOULECHANG_CAIPIAO1)
		if index > 0 then
			AddQuestText(sceneId,"\n\t\t\t#Y"..index)
			
		end
		index = GetCountryParam( sceneId, 3, CD_YOULECHANG_CAIPIAO1)
		if index > 0 then
			AddQuestText(sceneId,"\n\t\t\t#Y"..index)
			
		end
		index = GetCountryParam( sceneId, 0, CD_YOULECHANG_CAIPIAO2)
		if index > 0 then
			AddQuestText(sceneId,"\n\t\t\t#Y"..index)
			
		end
		index = GetCountryParam( sceneId, 1, CD_YOULECHANG_CAIPIAO2)
		if index > 0 then
			AddQuestText(sceneId,"\n\t\t\t#Y"..index)
			
		end
		index = GetCountryParam( sceneId, 2, CD_YOULECHANG_CAIPIAO2)
		if index > 0 then
			AddQuestText(sceneId,"\n\t\t\t#Y"..index)
			
		end
		index = GetCountryParam( sceneId, 3, CD_YOULECHANG_CAIPIAO2)
		if index > 0 then
			AddQuestText(sceneId,"\n\t\t\t#Y"..index)
			
		end
		AddQuestText(sceneId,"#Y"..x310337_g_TitleInfo1)
	EndQuestEvent()
	DispatchQuestEventList(sceneId, selfId, NPCId)  
	end
end

--列举事件
function x310337_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)
	--local state = GetQuestStateNM( sceneId, selfId, NPCId, x310337_g_MissionId)
	AddQuestNumText(sceneId,x310337_g_ScriptId,x310337_g_ScriptName,3,0)
end

function x310337_ProcAcceptCheck( sceneId, selfId, NPCId )
    return 1
end

--点确定后
function x310337_ProcAccept( sceneId, selfId )
end