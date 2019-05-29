#include <Crypt.au3>
$file = FileOpenDialog("Select an application file", Default, "(*.exe)", 2)
If @error Then Exit
MsgBox(0, IsFolderVirus($file), _Crypt_HashFile($file, $CALG_MD5))

Func IsFolderVirus($file)
	; Check if the file is a virus with a folder-like icon (I don't remember the malware name!)
	Return StringUpper(StringRight($file, 4)) == ".EXE" And FileGetSize($file) = 42687 And _
			_Crypt_HashFile($file, $CALG_MD5) = Binary("0x483FCF432217D71544246AA760D98CDC")
EndFunc
