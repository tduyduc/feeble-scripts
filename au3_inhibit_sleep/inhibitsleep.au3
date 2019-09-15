AutoItSetOption('TrayAutoPause', 0)
ProcessSetPriority(@AutoItPID, 0)
Global $dll = DllOpen('kernel32.dll')
If $dll = -1 Then Exit 1
OnAutoItExitRegister('OnExit')

While Sleep(30000)
	DllCall($dll, 'long', 'SetThreadExecutionState', 'long', 0x80000003)
WEnd

Func OnExit()
	DllCall($dll, 'long', 'SetThreadExecutionState', 'long', 0x80000000)
	DllClose($dll)
EndFunc
