x950003_g_ScriptId = 950003

--�����Ƕ�̬**************************************************************

--�����ı�����
x950003_g_MissionName="��ȡ��װ"


x950003_g_Items	=	{
										{
											{id=10202301, num=1},
											{id=10202302, num=1},
											{id=10202303, num=1},
											{id=10222301, num=1},
											{id=10222302, num=1},
											{id=10222303, num=1}
										},
										{
											{id=10232301, num=1},
											{id=10232302, num=1},
											{id=10232303, num=1},
											{id=10252301, num=1},
											{id=10252302, num=1},
											{id=10252303, num=1}
										},
										{
											{id=10272301, num=1},
											{id=10272302, num=1},
											{id=10272303, num=1}
										}
									}

--MisDescEnd
--**********************************
--������ں���
--**********************************
function x950003_ProcEventEntry( sceneId, selfId, targetId )	--����������ִ�д˽ű�

	local ret;
	local itemcount = 0;
	
	for i, items in x950003_g_Items do
		
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
function x950003_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	AddQuestNumText(sceneId,x950003_g_ScriptId,x950003_g_MissionName);
end