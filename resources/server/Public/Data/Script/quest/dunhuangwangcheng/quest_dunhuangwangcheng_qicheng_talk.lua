x256001_g_ScriptId = 256001
x256001_g_ask ={"【骑乘技能说明】"}
x256001_g_answer ={"#Y【骑乘技能说明】\n\t#W骑乘可以通过使用技能书，学习新的技能，提升骑乘能力。\n#Y操作说明#W：\n\t1.学习新技能需要骑乘具有相应的前置技能（一级技能无需前置技能）。\n\t2.骑乘学习技能的过程是很危险的，它们可能会遗忘掉以前学会的技能（前两个技能不会被遗忘），学的技能越多，遗忘的概率越大。\n\t3.还有一些技能必然互斥的，即学会这个技能，必然会遗忘另外一个。这些技能被称为同组技能。\n#Y\n同组技能的详细信息：\n\t#W1.资质组技能：健体、蛮力、追影、聪慧、全能\n\t2.特殊组技能：闪避、命中、暴击、防御、强韧、杀伤、悟性、活力、强攻、瞄准、施法\n\t3.攻击组技能：乱战、破军、魔灭、猛击、连环、偷袭\n\t4.回复组技能：回春、回复\n\t5.辅攻类技能：狂攻、精确、精研\n\t6.控制组技能：伤筋、击晕、狂吼、沉寂、定身\n\t7.回魔组技能：怒气，精力、箭囊、弹药、法力、圣力"}

function x256001_ProcEventEntry(sceneId, selfId, NPCId, MissionId,which)	--点击该任务后执行此脚本
		if which == 0 then
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,x256001_g_answer[1])
			--AddQuestNumText(sceneId, x256001_g_ScriptId, x256001_g_ask[5],0,4)
		  EndQuestEvent()
			DispatchQuestEventList(sceneId, selfId, NPCId)
		elseif which == 1 then
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,x256001_g_answer[2])
			--AddQuestNumText(sceneId, x256001_g_ScriptId, x256001_g_ask[5],0,4)
		  EndQuestEvent()
			DispatchQuestEventList(sceneId, selfId, NPCId)
		elseif which == 2 then
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,x256001_g_answer[3])
			--AddQuestNumText(sceneId, x256001_g_ScriptId, x256001_g_ask[5],0,4)
		  EndQuestEvent()
			DispatchQuestEventList(sceneId, selfId, NPCId)
		elseif which == 3 then
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,x256001_g_answer[4])
			--AddQuestNumText(sceneId, x256001_g_ScriptId, x256001_g_ask[5],0,4)
		  EndQuestEvent()
			DispatchQuestEventList(sceneId, selfId, NPCId)
		elseif which == 4 then
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,x256001_g_answer[5])
			AddQuestNumText(sceneId, x256001_g_ScriptId, x256001_g_ask[1],0,0)
      AddQuestNumText(sceneId, x256001_g_ScriptId, x256001_g_ask[2],0,1)
      AddQuestNumText(sceneId, x256001_g_ScriptId, x256001_g_ask[3],0,2)
      AddQuestNumText(sceneId, x256001_g_ScriptId, x256001_g_ask[4],0,3)
		  EndQuestEvent()
			DispatchQuestEventList(sceneId, selfId, NPCId)
		end

	
	
end


--**********************************

--列举事件

--**********************************

function x256001_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)
			AddQuestNumText(sceneId, x256001_g_ScriptId, x256001_g_ask[1],0,0)
end








