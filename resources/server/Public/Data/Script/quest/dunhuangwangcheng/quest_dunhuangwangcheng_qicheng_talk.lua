x256001_g_ScriptId = 256001
x256001_g_ask ={"����˼���˵����"}
x256001_g_answer ={"#Y����˼���˵����\n\t#W��˿���ͨ��ʹ�ü����飬ѧϰ�µļ��ܣ��������������\n#Y����˵��#W��\n\t1.ѧϰ�¼�����Ҫ��˾�����Ӧ��ǰ�ü��ܣ�һ����������ǰ�ü��ܣ���\n\t2.���ѧϰ���ܵĹ����Ǻ�Σ�յģ����ǿ��ܻ���������ǰѧ��ļ��ܣ�ǰ�������ܲ��ᱻ��������ѧ�ļ���Խ�࣬�����ĸ���Խ��\n\t3.����һЩ���ܱ�Ȼ����ģ���ѧ��������ܣ���Ȼ����������һ������Щ���ܱ���Ϊͬ�鼼�ܡ�\n#Y\nͬ�鼼�ܵ���ϸ��Ϣ��\n\t#W1.�����鼼�ܣ����塢������׷Ӱ���ϻۡ�ȫ��\n\t2.�����鼼�ܣ����ܡ����С�������������ǿ�͡�ɱ�ˡ����ԡ�������ǿ������׼��ʩ��\n\t3.�����鼼�ܣ���ս���ƾ���ħ���ͻ���������͵Ϯ\n\t4.�ظ��鼼�ܣ��ش����ظ�\n\t5.�����༼�ܣ��񹥡���ȷ������\n\t6.�����鼼�ܣ��˽���Ρ���𡢳��š�����\n\t7.��ħ�鼼�ܣ�ŭ�������������ҡ���ҩ��������ʥ��"}

function x256001_ProcEventEntry(sceneId, selfId, NPCId, MissionId,which)	--����������ִ�д˽ű�
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

--�о��¼�

--**********************************

function x256001_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)
			AddQuestNumText(sceneId, x256001_g_ScriptId, x256001_g_ask[1],0,0)
end








