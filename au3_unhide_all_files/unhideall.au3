#RequireAdmin
#include <File.au3>
Global $recur, $dir = FileSelectFolder("Choose a folder", "")
If @error Then Exit
If DriveGetType($dir) <> "Removable" Then
	If MsgBox(260, "Local Disk Warning", _
			"You are about to process files " & _
			"on a non-removable drive! Continue?") = 7 Then Exit
EndIf
Switch MsgBox(35, "Hidden File Fixer — T.D. Stoneheart", _
		"Use recursion to process subfolders?")
	Case 6
		$recur = 1
	Case 7
		$recur = 0
	Case Else
		Exit
EndSwitch
Global $list = _FileListToArrayRec($dir, "*", 0, $recur, 0, 2)
If Not IsArray($list) Then Exit 1
Global Const $sysvol = "\System Volume Information"
Global Const $thumbs = "\thumbs.db"
Global Const $desktop = "\desktop.ini"
ProgressOn("Hidden File Fixer — T.D. Stoneheart", _
		"Processing files...", "0/" & $list[0], -1, -1, 18)
For $i = 1 To UBound($list) - 1
	If StringRight($list[$i], StringLen($sysvol)) = $sysvol Then
	ElseIf StringRight($list[$i], StringLen($thumbs)) = $thumbs Then
		FileDelete($list[$i])
	ElseIf StringRight($list[$i], StringLen($desktop)) = $desktop Then
		FileDelete($list[$i])
	Else
		FileSetAttrib($list[$i], "-SH")
	EndIf
	ProgressSet(Round($i / $list[0] * 100), $i & "/" & $list[0])
Next
ProgressOff()
MsgBox(0, "Completed", $list[0] & " item(s) processed.")
