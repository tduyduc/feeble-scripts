; Virtual Machine Periodic Control
AutoItSetOption("TrayAutoPause", 0)
AutoItSetOption("TrayIconDebug", 1)
Global Const $STATE_OFF = 'VMState="poweroff"', $STATE_ON = 'VMState="running"'
Global Const $EXE = '"C:\Program Files\Oracle\VirtualBox\VBoxManage.exe"', $VM = '"{086a410e-6e53-4db9-b55c-c16bee52f869}"'
Global Const $ON_MORNING_HOUR = 8, $ON_MORNING_MINUTE = 0, $OFF_MORNING_HOUR = 9, $OFF_MORNING_MINUTE = 0
Global Const $ON_EVENING_HOUR = 20, $ON_EVENING_MINUTE = 30, $OFF_EVENING_HOUR = 21, $OFF_EVENING_MINUTE = 30
While Sleep(1000)
	Switch @HOUR
		Case $ON_MORNING_HOUR
			RefreshVM($ON_MORNING_HOUR, $ON_MORNING_MINUTE, True)
		Case $ON_EVENING_HOUR
			RefreshVM($ON_EVENING_HOUR, $ON_EVENING_MINUTE, True)
		Case $OFF_MORNING_HOUR
			RefreshVM($OFF_MORNING_HOUR, $OFF_MORNING_MINUTE, False)
		Case $OFF_EVENING_HOUR
			RefreshVM($OFF_EVENING_HOUR, $OFF_EVENING_MINUTE, False)
	EndSwitch
WEnd

Func RefreshVM($argHour, $argMin, $on)
	While @HOUR = $argHour And @MIN < $argMin
		Sleep(1000)
	WEnd
	If Not $on Then
		RunWait($EXE & ' controlvm ' & $VM & ' acpipowerbutton', "", @SW_HIDE)
	Else
		Local $pid
		While Sleep(1000)
			$pid = Run($EXE & ' showvminfo --machinereadable ' & $VM, "", @SW_HIDE, 2)
			ProcessWaitClose($pid)
			If StringInStr(StdoutRead($pid), $STATE_OFF) Then ExitLoop
		WEnd
		RunWait($EXE & ' startvm --type headless ' & $VM, "", @SW_HIDE)
	EndIf
	While @HOUR = $argHour
		Sleep(1000)
	WEnd
EndFunc
