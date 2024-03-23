--���Ӳֿ�ռ�
--MisDescBegin
--�ű���
x561005_g_ScriptId = 561005

--**************************************************************

--�����ı�����
x561005_g_MainName="������˲ֿ���չ�ռ�˵��"
x561005_g_MissionName="������˲ֿ���չ�ռ�"
x561005_g_Readme = "\t������˲ֿ���չ�ռ�Ļ������£�\n\t�ڶ���  #G200��#W����\n\t������  #G600��#W����\n\t���ĸ�  #G1.5��#W����\n\t�����  #G3��#W����\n"
x561005_g_Opt_Fail = "\t�������Ӳ��㣡�޷����������չ��˲ֿ������"
x561005_g_Opt_Succ = "\t�����ɹ�������������˲ֿ����չ�ռ䣡"

x561005_g_NeedMoney1 = 200000
x561005_g_NeedMoney2 = 600000
x561005_g_NeedMoney3 = 1500000
x561005_g_NeedMoney4 = 3000000


--MisDescEnd
--**********************************
--������ں���
--**********************************
function x561005_ProcEventEntry( sceneId, selfId, targetId,scriptid,extid )	--����������ִ�д˽ű�

		local activeBankPetSlot = LuaGetActiveBankPetSlot(sceneId,selfId)
		BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"#Y"..x561005_g_MainName)
			AddQuestText(sceneId,x561005_g_Readme);
			AddQuestText(sceneId,"\t����ǰ�ļ������Ϊ #G"..activeBankPetSlot)
			AddQuestText(sceneId,"\n\t#W��ȷ��Ҫ��չ��˲ֿ���")
		EndQuestEvent(sceneId)	
		DispatchQuestInfo(sceneId, selfId, targetId, scriptid, -1)
	
end

--**********************************
--�о��¼�
--**********************************
function x561005_ProcEnumEvent( sceneId, selfId, targetId, MissionId )

	AddQuestNumText(sceneId, x561005_g_ScriptId, x561005_g_MissionName,3,1)

end

--**********************************
--����������
--**********************************
function x561005_ProcAcceptCheck( sceneId, selfId, NPCId )
	return 1
end

---------------------------------------------------------------------------------------------------
--�õ���Ҹղ�ѡ��Ľ���ѡ��
---------------------------------------------------------------------------------------------------

function x561005_GetSelected(sceneId, selfId)
end

---------------------------------------------------------------------------------------------------
--������Ҹղ�ѡ��Ľ���ѡ��
---------------------------------------------------------------------------------------------------
function x561005_SetSelected(sceneId, selfId, flag)
end

function x561005_ActiveBankPetSlot( sceneId, selfId, needmoney )

		if IsEnoughMoney( sceneId, selfId, needmoney ) == 0  then
			BeginQuestEvent(sceneId,selfId)
				AddQuestText(sceneId,x561005_g_Opt_Fail)
			EndQuestEvent()
			DispatchQuestTips(sceneId,selfId)
		else
			--��������� 
			local bRet = LuaActiveBankPetSlot(sceneId,selfId)
			if 1 == bRet then
				SpendMoney( sceneId, selfId, needmoney )
				--BeginQuestEvent(sceneId,selfId)
				--	AddQuestText(sceneId,x561005_g_Opt_Succ)
				--EndQuestEvent()
				--DispatchQuestTips(sceneId,selfId)
			end
		end

end

--**********************************
--����
--**********************************
function x561005_ProcAccept( sceneId, selfId )

		local activeBankPetSlot = LuaGetActiveBankPetSlot(sceneId,selfId)
		if 1==activeBankPetSlot then
			x561005_ActiveBankPetSlot(sceneId,selfId,x561005_g_NeedMoney1)
		elseif 2==activeBankPetSlot then
			x561005_ActiveBankPetSlot(sceneId,selfId,x561005_g_NeedMoney2)
		elseif 3==activeBankPetSlot then
			x561005_ActiveBankPetSlot(sceneId,selfId,x561005_g_NeedMoney3)
		elseif 4==activeBankPetSlot then
			x561005_ActiveBankPetSlot(sceneId,selfId,x561005_g_NeedMoney4)
		elseif 5==activeBankPetSlot then
			BeginQuestEvent(sceneId,selfId)
				AddQuestText(sceneId,"��˲ֿ��Ѵ����ޣ��޷����")
			EndQuestEvent()
			DispatchQuestTips(sceneId,selfId)
		end
		
end

--**********************************
--����
--**********************************
function x561005_ProcQuestAbandon( sceneId, selfId, MissionId )

end

--**********************************
--����
--**********************************
function x561005_OnContinue( sceneId, selfId, targetId )

end

--**********************************
--����Ƿ�����ύ
--**********************************
function x561005_CheckSubmit( sceneId, selfId )

end

--**********************************
--�ύ
--**********************************
function x561005_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )

end

--**********************************
--ɱ����������
--**********************************
function x561005_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )

end

--**********************************
--���������¼�
--**********************************
function x561005_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

--**********************************
--���߸ı�
--**********************************
function x561005_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end
