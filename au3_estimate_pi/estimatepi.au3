; Uses Monte Carlo method
Global $tries = 0, $success = 0, $x, $y
While $tries < 10000000
	$x = Random()
	$y = Random()
	If ($x * $x + $y * $y <= 1) Then $success += 1
	$tries += 1
WEnd
MsgBox(0, "", 4 * $success / $tries)
