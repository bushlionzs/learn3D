x950000_g_ScriptId = 950000

--�����Ƕ�̬**************************************************************

--�����ı�����
x950000_g_MissionName="��հ���"


--MisDescEnd
--**********************************
--������ں���
--**********************************
function x950000_ProcEventEntry( sceneId, selfId, targetId )	--����������ִ�д˽ű�

	for i = 0, 180 do
		local itemnum = GetItemCountInBagPos(sceneId, selfId, i);
		if itemnum ~= nil then
			if itemnum > 0 then
				EraseItem(sceneId, selfId, i);
			end
		end
	end
	
end

--**********************************
--�о��¼�
--**********************************
function x950000_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	AddQuestNumText(sceneId,x950000_g_ScriptId,x950000_g_MissionName);
end