// Displays image with the source indicated in the current cell, be it from the web or data:image/png;
function showImage() {
  SpreadsheetApp.getUi().showModalDialog(
   HtmlService.createHtmlOutput('<img src="' + SpreadsheetApp.getCurrentCell().getValue() + '">'),
   'Image'
  );
}
