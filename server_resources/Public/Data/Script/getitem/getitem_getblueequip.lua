x950002_g_ScriptId = 950002

--以上是动态**************************************************************

--任务文本描述
x950002_g_MissionName="领取蓝装"


x950002_g_Items	=	{
										{
											{id=10231002, num=1},
											{id=10251002, num=1},
											{id=10271002, num=1}
										},
										--迷宫装01
										{
										 {id=10231003, num=1},
										 {id=10251003, num=1},
										 {id=10271003, num=1}
										--迷宫装02
										},
										{
											{id=10237001, num=1},
											{id=10257001, num=1},
											{id=10277001, num=1}
										},
										--迷宫装03
										{
											{id=10230201, num=1},
											{id=10250201, num=1},
											{id=10270201, num=1}
										},
										--打造装01
										{
											{id=10230202, num=1},
											{id=10250202, num=1},
											{id=10270202, num=1}
										--打造装02
										},
										{
											{id=10230203, num=1},
											{id=10250203, num=1},
											{id=10270203, num=1}
										},
										--打造装03
										{
											{id=10230204, num=1},
											{id=10250204, num=1},
											{id=10270204, num=1}
									    },
									 --打造装04
										{
											{id=10230205, num=1},
											{id=10250205, num=1},
											{id=10270205, num=1}
										},
										--打造装05
								    {
									    {id=10236002, num=1},
									    {id=10256002, num=1},
									    {id=10276002, num=1}
										},
										--东海海眼
										{
											{id=10233001, num=1},
											{id=10253001, num=1},
											{id=10273001, num=1}
										},
									--荣誉装01
									{
											{id=10233002, num=1},
											{id=10253002, num=1},
											{id=10273002, num=1},
											{id=10233003, num=1},
											{id=10253003, num=1},
											{id=10273003, num=1}
									},
										--荣誉装03
									}

--MisDescEnd
--**********************************
--任务入口函数
--**********************************
function x950002_ProcEventEntry( sceneId, selfId, targetId )	--点击该任务后执行此脚本

	local ret;
	local itemcount = 0;
	
	for i, items in x950002_g_Items do
		
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
--列举事件
--**********************************
function x950002_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	AddQuestNumText(sceneId,x950002_g_ScriptId,x950002_g_MissionName);
end