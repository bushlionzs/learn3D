x800112_g_ScriptId = 800112
x800112_g_ask ={"【宝石回收说明】"}
x800112_g_answer ={"#Y【宝石回收说明】#W\n\t所有使用荣誉换购的多彩宝石，都可以在我这里回收成相对应的成本。\n#Y操作说明#W：\n\t1.与王国#G装备回收大师#W或大都#G装备回收大师#W对话。\n\t2.选择#G多彩宝石回收#W选项。\n\t3.将需要回收的多彩宝石放入到多彩宝石回收界面中间的格子内。\n\t4.点击界面下方回收按钮。\n#Y注意事项#W：\n\t所有多彩宝石都可以在我这里兑换出100%的成本。"}

function x800112_ProcEventEntry(sceneId, selfId, NPCId, MissionId,which)	--点击该任务后执行此脚本
		if which == 0 then
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,x800112_g_answer[1])
			--AddQuestNumText(sceneId, x800112_g_ScriptId, x800112_g_ask[5],0,4)
		  EndQuestEvent()
			DispatchQuestEventList(sceneId, selfId, NPCId)
		elseif which == 1 then
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,x800112_g_answer[2])
			--AddQuestNumText(sceneId, x800112_g_ScriptId, x800112_g_ask[5],0,4)
		  EndQuestEvent()
			DispatchQuestEventList(sceneId, selfId, NPCId)
		elseif which == 2 then
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,x800112_g_answer[3])
			--AddQuestNumText(sceneId, x800112_g_ScriptId, x800112_g_ask[5],0,4)
		  EndQuestEvent()
			DispatchQuestEventList(sceneId, selfId, NPCId)
		elseif which == 3 then
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,x800112_g_answer[4])
			--AddQuestNumText(sceneId, x800112_g_ScriptId, x800112_g_ask[5],0,4)
		  EndQuestEvent()
			DispatchQuestEventList(sceneId, selfId, NPCId)
		elseif which == 4 then
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,x800112_g_answer[5])
			AddQuestNumText(sceneId, x800112_g_ScriptId, x800112_g_ask[1],0,0)
      AddQuestNumText(sceneId, x800112_g_ScriptId, x800112_g_ask[2],0,1)
      AddQuestNumText(sceneId, x800112_g_ScriptId, x800112_g_ask[3],0,2)
      AddQuestNumText(sceneId, x800112_g_ScriptId, x800112_g_ask[4],0,3)
		  EndQuestEvent()
			DispatchQuestEventList(sceneId, selfId, NPCId)
		end

	
	
end


--**********************************

--列举事件

--**********************************

function x800112_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)
			AddQuestNumText(sceneId, x800112_g_ScriptId, x800112_g_ask[1],0,0)
end








