Global $file = FileOpenDialog("Browse for VCard file", Default, "(*.vcf)", 3)
If @error Then Exit
$f = FileOpen($file, 128)
If $f = -1 Then Exit 1
$l = StringSplit(FileRead($f), @CRLF, 3)
If @error Or Not IsArray($l) Then Exit 1
FileClose($f)
$f = FileOpen($file & ".swapped", 130)
If $f = -1 Then Exit 1
For $i = 0 To UBound($l) - 1
	If StringRegExp($l[$i], "N;CHARSET=UTF-8;ENCODING=QUOTED-PRINTABLE:(.*;)(.*;);;") Then
		$l[$i] = StringRegExpReplace($l[$i], "N;CHARSET=UTF-8;ENCODING=QUOTED-PRINTABLE:(.*;)(.*;);;", "N;CHARSET=UTF-8;ENCODING=QUOTED-PRINTABLE:\2\1;;")
	ElseIf StringRegExp($l[$i], "N:(.*;)(.*;);;") Then
		$l[$i] = StringRegExpReplace($l[$i], "N:(.*;)(.*;);;", "N:\2\1;;")
	EndIf
	FileWriteLine($f, $l[$i])
Next
If FileClose($f) Then MsgBox(0, "Completed!", "Modification complete.")
