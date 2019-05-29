Global $a[1000]
SRandom(1)
For $i = 0 To UBound($a) - 1
	$a[$i] = Random(0, UBound($a) - 1, 1)
Next

Func BubbleSort(ByRef $A)
	Local $i, $j, $N = UBound($A) - 1
	For $i = 1 To $N - 1
		For $j = $N To $i Step -1
			If ($A[$j] < $A[$j - 1]) Then Swap($A[$j], $A[$j - 1])
		Next
	Next
EndFunc

Func SelectionSort(ByRef $A)
	Local $i, $j, $k, $N = UBound($A) - 1
	For $i = 1 To $N - 1
		$k = $i
		For $j = $i + 1 To $N
			If $A[$j] < $A[$k] Then $k = $j
		Next
		If $k <> $i Then Swap($A[$k], $A[$i])
	Next
EndFunc

Func QuickSort(ByRef $A, $L, $R)
	Local $i = $L, $j = $R, $x = $A[Int(($L + $R) / 2)]
	Do
		While $A[$i] < $x
			$i += 1
		WEnd
		While $A[$j] > $x
			$j -= 1
		WEnd
		If $i <= $j Then
			Swap($A[$i], $A[$j])
			$i += 1
			$j -= 1
		EndIf
	Until $i > $j
	If $L < $j Then QuickSort($A, $L, $j)
	If $i < $R Then QuickSort($A, $i, $R)
EndFunc

Func Swap(ByRef $x, ByRef $y)
	Local $t = $x
	$x = $y
	$y = $t
EndFunc

; Speed comparison: QuickSort > SelectionSort > BubbleSort
$time = TimerInit()
QuickSort($a, 0, UBound($a) - 1)
;BubbleSort($a)
;SelectionSort($a)
$time = TimerDiff($time) / 1000
$text = ""
For $i = 0 To UBound($a) - 1
	$text &= $a[$i] & " "
Next
MsgBox(0, $time / 1000, $text)
