x950004_g_ScriptId = 950004

--�����Ƕ�̬**************************************************************

--�����ı�����
x950004_g_MissionName="��ȡ��װ"


x950004_g_Items	=	{
										{
										 {id=10231101, num=1},
										 {id=10251101, num=1},
										 {id=10271101, num=1}
											--�ؼ�����03
										},
										{
											{id=10231102, num=1},
											{id=10251102, num=1},
											{id=10271102, num=1},
											--�ؼ�����05
											{id=10231103, num=1},
											{id=10251103, num=1},
											{id=10271103, num=1}
										--�ؼ�����06
										},
										 {
											{id=10231104, num=1},
											{id=10251104, num=1},
											{id=10271104, num=1}
										--�ؼ�����07
										},
										{
											{id=10231106, num=1},
										  {id=10251106, num=1},
											{id=10271106, num=1}
										--�ؼ�����09
										},
									
										{
											{id=10231107, num=1},
											{id=10251107, num=1},
											{id=10271107, num=1}
										--�ؼ�����10
										},
										{											
										{id=10233003, num=1},
											{id=10253003, num=1},
											{id=10273003, num=1}
										--�ؼ�����07
										},
									        {
											{id=10232405, num=1},
											{id=10252405, num=1},
											{id=10272405, num=1}
										
										--�ؼ�����08
									        },
									        {
											{id=10232406, num=1},
											{id=10252406, num=1},
											{id=10272406, num=1}
										},
										--�ؼ�����09
										{
											{id=10232407, num=1},
											{id=10252407, num=1},
											{id=10272407, num=1}
										}
										--�ؼ�����10
									}
									
									
									

--MisDescEnd
--**********************************
--������ں���
--**********************************
function x950004_ProcEventEntry( sceneId, selfId, targetId )	--����������ִ�д˽ű�

	local ret;
	local itemcount = 0;
	
	for i, items in x950004_g_Items do
		
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
function x950004_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	AddQuestNumText(sceneId,x950004_g_ScriptId,x950004_g_MissionName);
end