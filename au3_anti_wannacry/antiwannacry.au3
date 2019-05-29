#RequireAdmin
RegWrite("HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows NT\CurrentVersion\Image File Execution Options\taskdl.exe", "Debugger", "REG_SZ", "taskkill /IM /F taskdl.exe")
If @error Then Exit 1
RegWrite("HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows NT\CurrentVersion\Image File Execution Options\taskse.exe", "Debugger", "REG_SZ", "taskkill /IM /F taskse.exe")
If @error Then Exit 1
RegWrite("HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows NT\CurrentVersion\Image File Execution Options\wannacry.exe", "Debugger", "REG_SZ", "taskkill.exe /IM /F wannacry.exe")
If @error Then Exit 1
RegWrite("HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows NT\CurrentVersion\Image File Execution Options\mssecsvc.exe", "Debugger", "REG_SZ", "taskkill.exe /IM /F mssecsvc.exe")
If @error Then Exit 1
RegWrite("HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows NT\CurrentVersion\Image File Execution Options\tasksche.exe", "Debugger", "REG_SZ", "taskkill.exe /IM /F tasksche.exe")
If @error Then Exit 1
RegWrite("HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows NT\CurrentVersion\Image File Execution Options\taskhsvc.exe", "Debugger", "REG_SZ", "taskkill.exe /IM /F taskhsvc.exe")
If @error Then Exit 1
MsgBox(0, "Completed", "Registry values against WannaCry created successfully.")
Exit 0
