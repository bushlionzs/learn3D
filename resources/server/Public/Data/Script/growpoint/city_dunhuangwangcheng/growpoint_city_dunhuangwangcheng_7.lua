--������

x301008_g_GrowpointId = 9 --��Ӧ������ID
x301008_g_ItemIndex = 13010082 --��Ӧ�ռ���Ʒ��ID
x301008_g_ItemIndex2 ={11960001,11960002,11960003,11960004,11960005,11960006,11960007,11960008,11960009,11960010}


--���ɺ�����ʼ************************************************************************
function 	x301008_OnCreate(sceneId,growPointType,x,y)
	local ItemBoxId = ItemBoxEnterScene(x, y, x301008_g_GrowpointId, sceneId, 0, x301008_g_ItemIndex)
end
--���ɺ�������**********************************************************************


--��ǰ������ʼ&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
function	 x301008_OnOpen(sceneId,selfId,targetId)
	return 0
end
--��ǰ��������&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&


--���պ�����ʼ########################################################################
function	 x301008_OnRecycle(sceneId,selfId,targetId)
	local itemlevel =0
	if GetLevel(sceneId, selfId)<= 10 then
				itemlevel =1
	elseif GetLevel(sceneId, selfId)<= 20 then
				itemlevel =2
	elseif GetLevel(sceneId, selfId)<= 30 then
				itemlevel =3
	elseif GetLevel(sceneId, selfId)<= 40 then
				itemlevel =4
	elseif GetLevel(sceneId, selfId)<= 50 then
				itemlevel =5
	elseif GetLevel(sceneId, selfId)<= 60 then
				itemlevel =6
	elseif GetLevel(sceneId, selfId)<= 70 then
				itemlevel =7
	elseif GetLevel(sceneId, selfId)<= 80 then
				itemlevel =8
	elseif GetLevel(sceneId, selfId)<= 90 then
				itemlevel =8
	elseif GetLevel(sceneId, selfId)<= 100 then
				itemlevel =8
	end
	local randombuff =0
	BeginAddItem(sceneId)
	AddItem( sceneId, 13010082, 1 )
  local ret = EndAddItem(sceneId,selfId)
    if ret <= 0 then
        randombuff =random(1,7)
    else
    		randombuff =random(1,8)
    end
    if randombuff < 8 then
    		BeginAddItem(sceneId)
				AddItem( sceneId, x301008_g_ItemIndex2[itemlevel], 1 )
				EndAddItem(sceneId,selfId)
    		AddItemListToPlayer(sceneId,selfId)









    elseif randombuff == 8 then
    		AddItemListToPlayer(sceneId,selfId)
    		BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"�õ����߱�")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
    end
    SetGrowPointIntervalContainer(sceneId,x301008_g_GrowpointId,-1)
		return 1
end
--���պ�������########################################################################



--�򿪺�����ʼ@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
function	x301008_OnProcOver(sceneId,selfId,targetId)
	
end
--�򿪺�������@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@



function	x301008_OpenCheck(sceneId,selfId,AbilityId,AblityLevel)
	
end

