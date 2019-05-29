Global $text = "", $disks[4], $step
Func TOH($n, $start, $goal, $temp)
	If $n = 0 Then Return
	TOH($n - 1, $start, $temp, $goal)
	Move($start, $goal)
	TOH($n - 1, $temp, $goal, $start)
EndFunc
Func Move($start, $goal)
	$disks[$start] -= 1
	$disks[$goal] += 1
	$step += 1
	$text &= $step & ". Move the top disk from pole " & _
			$start & " to pole " & $goal & _
			" (" & $disks[1] & ", " & $disks[2] & ", " & _
			$disks[3] & ")" & @CRLF
EndFunc
$disks[1] = 5
$disks[2] = 0
$disks[3] = 0
TOH(5, 1, 2, 3)
MsgBox(0, "Solution", $text)
