x950010_g_ScriptId = 950010

--�����Ƕ�̬**************************************************************

--�����ı�����
x950010_g_MissionName="��ȡ����"


x950010_g_Items	=	{
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
function x950010_ProcEventEntry( sceneId, selfId, targetId )	--����������ִ�д˽ű�

	local ret;
	local itemcount = 0;
	
	for i, items in x950010_g_Items do
		
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
function x950010_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	AddQuestNumText(sceneId,x950010_g_ScriptId,x950010_g_MissionName);
end