x800068_g_ScriptId = 800068
x800068_g_ask ={"装备保值（跨级装备）说明"}
x800068_g_answer ={"\t跨级装备保值，可以将原有装备的升星，灵魂铭刻，麻将铭刻，打孔，紫色属性完美的复制到新装备上。\n\t只能将神字级装备的相关属性复制到天字级装备上，且神字级装备必须为紫色装备，所保值装备的品质，部件必须完全一致，保值后的装备会成为绑定装备。\n\t注意：原有装备的#G升星#W，#G灵魂铭刻#W，#G麻将铭刻#W，#G打孔#W，#G紫色属性#W五项属性，将会完全覆盖新装备的此五项属性，#R如果原有装备没有某项属性，新装备也将会没有。"}

function x800068_ProcEventEntry(sceneId, selfId, NPCId, MissionId,which)	--点击该任务后执行此脚本
		if which == 0 then
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,x800068_g_answer[1])
			--AddQuestNumText(sceneId, x800068_g_ScriptId, x800068_g_ask[5],0,4)
		  EndQuestEvent()
			DispatchQuestEventList(sceneId, selfId, NPCId)
		elseif which == 1 then
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,x800068_g_answer[2])
			--AddQuestNumText(sceneId, x800068_g_ScriptId, x800068_g_ask[5],0,4)
		  EndQuestEvent()
			DispatchQuestEventList(sceneId, selfId, NPCId)
		elseif which == 2 then
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,x800068_g_answer[3])
			--AddQuestNumText(sceneId, x800068_g_ScriptId, x800068_g_ask[5],0,4)
		  EndQuestEvent()
			DispatchQuestEventList(sceneId, selfId, NPCId)
		elseif which == 3 then
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,x800068_g_answer[4])
			--AddQuestNumText(sceneId, x800068_g_ScriptId, x800068_g_ask[5],0,4)
		  EndQuestEvent()
			DispatchQuestEventList(sceneId, selfId, NPCId)
		elseif which == 4 then
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,x800068_g_answer[5])
			AddQuestNumText(sceneId, x800068_g_ScriptId, x800068_g_ask[1],0,0)
      AddQuestNumText(sceneId, x800068_g_ScriptId, x800068_g_ask[2],0,1)
      AddQuestNumText(sceneId, x800068_g_ScriptId, x800068_g_ask[3],0,2)
      AddQuestNumText(sceneId, x800068_g_ScriptId, x800068_g_ask[4],0,3)
		  EndQuestEvent()
			DispatchQuestEventList(sceneId, selfId, NPCId)
		end

	
	
end


--**********************************

--列举事件

--**********************************

function x800068_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)
			AddQuestNumText(sceneId, x800068_g_ScriptId, x800068_g_ask[1],0,0)
end








