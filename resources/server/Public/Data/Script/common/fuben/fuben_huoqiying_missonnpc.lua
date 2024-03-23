-------------------------------------------------
-- 黄河坞： 范文虎对话
-------------------------------------------------
x700041_CSP_B_GETBUFF_START	=	234--x700007_CSP_B_GETBUFF_START
x700041_CSP_GUID_START              =   248
x700041_g_Buff2				=	13501

x700041_g_ScriptId = 700041


x700041_Fuben_ScriptId = 700007

x700041_g_TalkTitle = "#Y".."范文虎的指教"
x700041_g_TalkContent = "确定让范文虎指点一下你吗？"

function x700041_ProcEventEntry(sceneId, selfId, NPCId, MissionId,which)	--点击该任务后执行此脚本
	
	
	x700041_DispatchGetBuffInfo( sceneId, selfId, NPCId,which )
	
end


--**********************************

--列举事件

--**********************************

function x700041_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)
	
	AddQuestNumText(sceneId, x700041_g_ScriptId, "获得范文虎的指点",5,1)
			
end



function x700041_DispatchGetBuffInfo( sceneId, selfId, NPCId, nParam )

	BeginQuestEvent(sceneId)

		--任务信息
		AddQuestText(sceneId,x700041_g_TalkTitle)
		AddQuestText(sceneId,x700041_g_TalkContent)
		

	EndQuestEvent()





	DispatchQuestInfo(sceneId, selfId, NPCId, x700041_g_ScriptId, -1);
end


---------------------------------------------------------------------------------------------------
--申请进入副本
---------------------------------------------------------------------------------------------------
function x700041_ProcAcceptCheck( sceneId, selfId, NPCId )
    return 1
end

----------------------------------------------------------------------------------------------
--点确定后
----------------------------------------------------------------------------------------------
function x700041_ProcAccept( sceneId, selfId )

	
	--CallScriptFunction( x700041_Fuben_ScriptId, "OnNpcTalkGetBuff", sceneId, selfId) ;
	x700041_OnNpcTalkGetBuff( sceneId, selfId)
	
end


------------------------------------------------------------------------
-- 领取buff接口
----------------------------------------------------------------------

function x700041_OnNpcTalkGetBuff( sceneId, selfId)

	local myGuid = GetPlayerGUID( sceneId,selfId )
	myGuid = format("%u", myGuid)

	for i=0, 5 do
        local paramidx = x700041_CSP_GUID_START + i
        local nGUID = GetFubenData_Param(sceneId, paramidx  )
				nGUID = format("%u", nGUID)
        if nGUID == myGuid then

			local bGathered = GetFubenData_Param(sceneId, x700041_CSP_B_GETBUFF_START+i);
			
			local str = ""

			if bGathered<=0 then
				SetFubenData_Param(sceneId, x700041_CSP_B_GETBUFF_START+i,1);
				
				SendSpecificImpactToUnit(sceneId, selfId,selfId,selfId, x700041_g_Buff2,0 )

				str = "您得到了范文虎的指教"
				
				
			else
				str = "范文虎也只能教你一次"
			end

			BeginQuestEvent(sceneId);
				AddQuestText(sceneId,str);
			EndQuestEvent();
			DispatchQuestTips(sceneId, selfId);
			break;
           
        end
    end

	
end
