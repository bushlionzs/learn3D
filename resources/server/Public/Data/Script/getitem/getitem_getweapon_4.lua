x950009_g_ScriptId = 950009

--以上是动态**************************************************************

--任务文本描述
x950009_g_MissionName="其他副手武器"


x950009_g_Items	=	{
										{
											{
												{id=10072203, num=1},
												{id=10072206, num=1},
												{id=10072209, num=1},
												{id=10072302, num=1},
												{id=10072305, num=1}
											
											}
										},
										{
											{
												{id=10082201, num=1},
												{id=10082204, num=1},
												{id=10082207, num=1},
												{id=10082210, num=1},
												{id=10084002, num=1}
											}
										},
										{
											{
												{id=10090202, num=1}
										
											}
										},
										{
											{
												{id=10101110, num=1}
											}
										},
										{
											{
												{id=10112201, num=1},
												{id=10112204, num=1},
												{id=10112207, num=1},
												{id=10113001, num=1},
												{id=10114002, num=1}
												
											}
										},
										{
											{
												{id=10122201, num=1},
												{id=10122204, num=1},
												{id=10122207, num=1},
												{id=10123001, num=1},
												{id=10123003, num=1}
												
											}
										}
									}


--MisDescEnd
--**********************************
--任务入口函数
--**********************************
function x950009_ProcEventEntry( sceneId, selfId, targetId )	--点击该任务后执行此脚本

	local ret;
	local zhiye = GetZhiye(sceneId, selfId);
	local itemcount = 0;
		
	BeginAddItem(sceneId);
	for i, items in x950009_g_Items[zhiye+1] do
		for j, item in items do
			AddItem( sceneId, item.id, item.num );
			itemcount = itemcount + 1;
		end
	end
	ret = EndAddItem(sceneId,selfId);
	if ret > 0 and itemcount > 0 then
		AddItemListToPlayer(sceneId,selfId);
	end
	
end

--**********************************
--列举事件
--**********************************
function x950009_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	AddQuestNumText(sceneId,x950009_g_ScriptId,x950009_g_MissionName);
end