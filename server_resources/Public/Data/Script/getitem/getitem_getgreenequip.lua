x950001_g_ScriptId = 950001

--�����Ƕ�̬**************************************************************

--�����ı�����
x950001_g_MissionName="��ȡ��װ"


x950001_g_Items	=	{
										{
											{id=10234001, num=1},
											{id=10254001, num=1},
											{id=10274001, num=1}
										},
										--��ԭ����1
										{
										 {id=10234002, num=1},
										 {id=10254002, num=1},
										 {id=10274002, num=1}
										--��ԭ����2
										},
										{
											{id=10234003, num=1},
											{id=10254003, num=1},
											{id=10274003, num=1}
										},
										--��ԭ����3
										{
											{id=10230000, num=1},
											{id=10250000, num=1},
											{id=10270000, num=1}
										},
										--��ԭ����04
										{
											{id=10234101, num=1},
											{id=10254101, num=1},
											{id=10274101, num=1}
										--��ŷ����װ01
										},
										{
											{id=10234102, num=1},
											{id=10254102, num=1},
											{id=10274102, num=1}
										},
										--��ŷ����װ02
										{
											{id=10234103, num=1},
											{id=10254103, num=1},
											{id=10274103, num=1}
									 },
									 --��ŷ����װ03
										{
											{id=10230001, num=1},
											{id=10250001, num=1},
											{id=10270001, num=1}
										},
										--��ŷ����װ04
								                {
									                 {id=10234201, num=1},
									                 {id=10254201, num=1},
									                 {id=10274201, num=1}
										},
										--��ԭ����װ01
										{
											{id=10234002, num=1},
											{id=10254002, num=1},
											{id=10274002, num=1}
										},
									--��ԭ����װ02
									{
											{id=10234203, num=1},
											{id=10254203, num=1},
											{id=10274203, num=1},
											{id=10230002, num=1},
											{id=10250002, num=1},
											{id=10270002, num=1}
											
									},
									
							
										--��ԭ����װ04
									}

--MisDescEnd
--**********************************
--������ں���
--**********************************
function x950001_ProcEventEntry( sceneId, selfId, targetId )	--����������ִ�д˽ű�

	local ret;
	local itemcount = 0;
	
	for i, items in x950001_g_Items do
		
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
function x950001_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	AddQuestNumText(sceneId,x950001_g_ScriptId,x950001_g_MissionName);
end