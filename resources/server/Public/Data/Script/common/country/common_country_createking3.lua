--功能脚本
--国王弹劾和投票
--MisDescBegin
x300309_g_ScriptId = 300309
x300309_g_MissionId = 4100
x300309_g_Name	="祖兰德" 
x300309_g_MissionName="弹劾国王 -（全民参与）"

--**********************************


--任务入口函数

--**********************************

function x300309_ProcEventEntry(sceneId, selfId, targetId)	--点击该任务后执行此脚本
		BeginQuestEvent(sceneId);AddQuestText(sceneId,"#Y".."你是否确认要弹劾国王？");EndQuestEvent();DispatchQuestInfo(sceneId, selfId, targetId, x300309_g_ScriptId, x300309_g_MissionId);
end



--**********************************

--列举事件

--**********************************

function x300309_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
		AddQuestNumText(sceneId, x300309_g_ScriptId, x300309_g_MissionName)	
end



--**********************************

--检测接受条件

--**********************************

function x300309_ProcAcceptCheck(sceneId, selfId, targetId)
	CountryDeletaBegin( sceneId, selfId );
	CountryVoteBegin(sceneId, selfId);
	--添加触发函数
return 1
end


--**********************************

--检测查看条件

--**********************************

function x300309_CheckPushList(sceneId, selfId, targetId)
--	if (sceneId==15) then
--		if IsQuestHaveDone(sceneId, selfId, x300309_g_MissionIdPre) > 0 then
--       	    	return 1
--        	end
--        end
--        return 0
	
end

--**********************************

--接受

--**********************************

function x300309_ProcAccept(sceneId, selfId)
	  BeginQuestEvent(sceneId);AddQuestText(sceneId,"弹劾成功");EndQuestEvent();DispatchQuestTips(sceneId, selfId);   
end



--**********************************

--放弃

--**********************************

function x300309_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--检测是否可以提交

--**********************************

function x300309_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--提交

--**********************************

function x300309_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)

end



--**********************************

--杀死怪物或玩家

--**********************************

function x300309_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--进入区域事件

--**********************************

function x300309_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)
		AddQuestNumText(sceneId, x300309_g_ScriptId, "弹劾国王")
end



--**********************************

--道具改变

--**********************************

function x300309_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end

