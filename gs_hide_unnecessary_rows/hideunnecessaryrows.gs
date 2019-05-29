function hideUnnecessaryRows() {
  var sheet = SpreadsheetApp.getActiveSpreadsheet().getActiveSheet(), len = sheet.getLastRow(), values = sheet.getRange(1, 1, len, 1).getValues();
  for (var i = 0; i < len; i++) {
    if ("" === values[i][0]) sheet.hideRows(i + 1); else sheet.showRows(i + 1);
  }
}
