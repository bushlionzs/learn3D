x950005_g_ScriptId = 950005

--�����Ƕ�̬**************************************************************

--�����ı�����
x950005_g_MissionName="��ȡ����װ��"


x950005_g_Items	=	{
										{
										},
										{
										},
										{
										}
									}

--MisDescEnd
--**********************************
--������ں���
--**********************************
function x950005_ProcEventEntry( sceneId, selfId, targetId )	--����������ִ�д˽ű�

	local ret;
	local itemcount = 0;
	
	for i, items in x950005_g_Items do
		
		BeginAddItem(sceneId);
		for j, item in items do
			AddItem( sceneId, item.id, item.num );
			itemcount = itemcount + 1;
		end
		ret = EndAddItem(sceneId,selfId);
		if ret > 0 and itemcount > 0 then
			AddItemListToPlayer(sceneId,selfId);
		end
	end
	
end

--**********************************
--�о��¼�
--**********************************
function x950005_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	AddQuestNumText(sceneId,x950005_g_ScriptId,x950005_g_MissionName);
end