#RequireAdmin
Opt("TrayAutoPause", 0)
ProcessSetPriority(@AutoItPID, 0)
While Sleep(1000)
	ProcessClose("BBTalk.exe")
	ProcessClose("CompatTelRunner.exe")
	ProcessClose("ConnectifyGopher.exe")
WEnd
