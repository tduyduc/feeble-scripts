#RequireAdmin

Func ExecuteDebug()
	Local $cmd = InputBox("Debug Mode", "Enter an expression to evaluate.")
	If @error Then Return
	Local $time = TimerInit(), $exec = Execute($cmd), $error = @error, $extended = @extended
	$time = Round(TimerDiff($time) / 1000, 9)
	Return MsgBox(65, "Result", $cmd & @CRLF & $exec & @CRLF & "Type: " & VarGetType($exec) & @CRLF & _
			"Error: " & $error & @CRLF & "Extended: " & $extended & @CRLF & "Time: " & $time & "s")
EndFunc

Func _If($if, $then, $else)
	Return $if ? $then : $else
EndFunc

Func _While($cond, $do)
	Local $last = False
	While $cond
		$last = $do
	WEnd
	Return $last
EndFunc

Func _Repeat($do, $cond)
	Local $last
	Do
		$last = $do
	Until $cond
	Return $last
EndFunc

Func _Comma($cmd1, $cmd2)
	Local $temp = $cmd1
	Return $cmd2
EndFunc

Do
Until ExecuteDebug() <> 1
