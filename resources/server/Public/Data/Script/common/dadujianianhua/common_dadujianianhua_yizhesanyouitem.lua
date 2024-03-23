x310166_g_ScriptId = 310166
x310166_g_ScriptName = "�ύ��������"	

x310166_g_ScripText = "\t�͹�Ʒһ��ʧ�Ļ������ṱ�飬��������Ź�Ʒ�����ƺ�������\n\t#Y@myname#W������Ұ����ṱ���һ�������\n \n#G(��ɴ�NPC[��������]ȫ����#G������������м��ʵõ��������顣)"

x310166_g_Item = {12030080, 12030081, 12030082}

-- �淨����ʱ��(��0����ĵ�x����)
x310166_g_OpenTime                  = 1170
-- �淨�ر�ʱ��(��0����ĵ�x����)
x310166_g_EndTime                   = 1440

function x310166_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	AddQuestNumText(sceneId, x310166_g_ScriptId, x310166_g_ScriptName,3)
end

function x310166_ProcEventEntry( sceneId, selfId, targetId, MissionId )
	local exp = GetLevel( sceneId, selfId)*7000
	BeginQuestEvent( sceneId)
    AddQuestText( sceneId, "#Y"..x310166_g_ScriptName)
    AddQuestText(sceneId, x310166_g_ScripText)
    AddQuestText( sceneId, "\n#Y�������ݣ�#W")
    AddQuestText( sceneId, "����ֵ:"..exp )
    
    DispatchQuestInfo(sceneId, selfId, targetId, x310166_g_ScriptId, -1)
end


function x310166_CheckItem( sceneId, selfId)

	for i, item in x310166_g_Item do
		if HaveItemInBag( sceneId, selfId, item ) <= 0 then
			return 0
		end
	end
	return 1
end

function x310166_ProcAcceptCheck( sceneId, selfId, targetId)

	local nowTime = GetMinOfDay()
    if nowTime < x310166_g_OpenTime or nowTime >= x310166_g_EndTime then
		local msg = "ֻ����ÿ�յ�#G19��30--24��00#cffcf00�ڲſ��ύ�������顣"
        Msg2Player( sceneId, selfId, msg, 8, 2)
        Msg2Player( sceneId, selfId, msg, 8, 3)
		return
    end

	local lastDay = GetQuestData(sceneId, selfId, MD_YIZHESANYOU_ITEM_DAY[1], MD_YIZHESANYOU_ITEM_DAY[2], MD_YIZHESANYOU_ITEM_DAY[3])

	local today = GetDayOfYear()
	if today == lastDay then 
		local msg = "�������Ѿ��ύ�����������ˣ�������������"
        Msg2Player( sceneId, selfId, msg, 8, 2)
        Msg2Player( sceneId, selfId, msg, 8, 3)
        return
	end
		

    if x310166_CheckItem( sceneId, selfId) == 1 then
		for i, item in x310166_g_Item do
			DelItem( sceneId, selfId, item, 1 )
		end
		
		SetQuestData(sceneId, selfId, MD_YIZHESANYOU_ITEM_DAY[1], MD_YIZHESANYOU_ITEM_DAY[2], MD_YIZHESANYOU_ITEM_DAY[3], today)
		
		local exp = GetLevel( sceneId, selfId)*7000
		AddExp( sceneId, selfId, exp)
        Msg2Player( sceneId, selfId, format( "���#R����%d��#cffcf00�Ľ���", exp).."��", 8, 2)
        Msg2Player( sceneId, selfId, format( "���#R����%d��#cffcf00�Ľ���", exp), 8, 3)
    else
        Msg2Player( sceneId, selfId, "������û��ȫ�׵ĸ������飬�ύʧ��", 8, 2)
        Msg2Player( sceneId, selfId, "������û��ȫ�׵ĸ������飬�ύʧ��", 8, 3)
	end
end