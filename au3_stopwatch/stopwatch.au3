#NoTrayIcon
$r = RandText(8) ;get random characters to identify new window
ProgressOn("Mini-Stopwatch — T.D. Stoneheart", "Alt+F4: Exit", $r, -1, -1, 2 + 16)
$w = WinWait("Mini-Stopwatch — T.D. Stoneheart", $r) ;get window handle
WinSetTrans($w, "", 200)
$t = TimerInit() ;start timer
Do
	Sleep(50)
	$s = TimerDiff($t) / 1000 ;get elapsed time in seconds
	;ProgressSet(Round(Mod($s, 60) / 60 * 100), StringFormat("%.1f", Round($s, 1)))
	ProgressSet(Progress($s, 1), Progress($s, 0), Time($s))
Until Not WinExists($w) ;close if progress window (given hwnd) is closed
MsgBox(0, Time($s), "Stopwatch stopped.") ;display time elapsed on exit
Func Progress($s, $f) ;time in seconds, flag (progress bar (1) or main text (0))
	Local $u ;unit used for progress bar: minute/hour/day
	If $s < 3600 Then ;less than 1 hour
		$u = $f ? 60 : "Minutes"
	ElseIf $s < 86400 Then ;less than 1 day
		$u = $f ? 3600 : "Hours"
	Else ;1 day and up
		$u = $f ? 86400 : "Days"
	EndIf
	Return $f ? Round(Mod($s, $u) / $u * 100) : _
			("Progress bar: " & $u & @CRLF & "Press Alt+F4 to stop" & @CRLF & _
			"Current time: " & StringFormat("%02i", @HOUR) & ":" & _
			StringFormat("%02i", @MIN) & ":" & StringFormat("%02i", @SEC))
EndFunc
Func Time($s) ;d:hh:mm:ss.t
	Return Floor($s / 86400) & ":" & StringFormat("%02i", Mod($s / 3600, 24)) & ":" _
			& StringFormat("%02i", Mod($s / 60, 60)) & ":" & _
			StringFormat("%02i", Mod($s, 60)) & "." & Mod(Round($s * 10), 10)
EndFunc
Func RandText($l) ;length
	$rt = ""
	For $i = 1 To $l
		$rt &= Chr(Random(97, 122, 1))
	Next
	Return $rt
EndFunc
