$n = 1E5
Global $r[$n]
$a = 0
$t = TimerInit()
For $i = 0 To $n - 1
	$x = Random()
	$func = '$x'
	$r[$i] = Execute($func)
	$a += $r[$i]
Next
$t = TimerDiff($t)
$a /= $n
ConsoleWrite("Time: " & $t / 1E3 & @CRLF)
ConsoleWrite("For one calculation: " & $t / 1E3 / $n & @CRLF)
ConsoleWrite("int(" & $func & ")dx from 0 to 1" _
		& " approximately equals to " & $a & @CRLF)
MsgBox(0, "Result", "int(" & $func & ")dx from 0 to 1" _
		& @CRLF & "approximately equals to" & @CRLF & $a)
