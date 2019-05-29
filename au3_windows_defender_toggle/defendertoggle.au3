Switch MsgBox(35, "Windows Defender Toggle", _
		'Do you want to enable Windows Defender?' & @CRLF & 'Select "No" to disable.' & @CRLF & 'Select "Cancel" to exit.')
	Case 6
		RegDelete("HKLM\SOFTWARE\Policies\Microsoft\Windows Defender", "DisableAntiSpyware")
	Case 7
		RegWrite("HKLM\SOFTWARE\Policies\Microsoft\Windows Defender", "DisableAntiSpyware", "REG_DWORD", 1)
	Case Else
		Exit
EndSwitch
