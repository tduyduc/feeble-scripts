Func BalancedParentheses($string)
	Local $paren = 0
	For $i = 1 To StringLen($string)
		Switch StringMid($string, $i, 1)
			Case "("
				$paren += 1
			Case ")"
				$paren -= 1
				If $paren < 0 Then ExitLoop
		EndSwitch
	Next
	Return ($paren = 0)
EndFunc
Func ImproperParentheses($string)
	Local $last = 0, $paren = 0
	For $i = 1 To StringLen($string)
		Switch StringMid($string, $i, 1)
			Case "("
				$paren += 1
				If $paren = 1 Then $last = $i
			Case ")"
				$paren -= 1
				If $paren < 0 Then
					$last = $i
					ExitLoop
				EndIf
		EndSwitch
	Next
	Return (($paren = 0) ? -1 : $last)
EndFunc
$string = InputBox("Enter a string", "The entered string will be checked for balanced parentheses.")
MsgBox(0, BalancedParentheses($string), ImproperParentheses($string))
