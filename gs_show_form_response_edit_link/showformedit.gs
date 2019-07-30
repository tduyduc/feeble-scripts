// Displays a link to edit the form response from one selected row (only one row) of a form responses sheet.
// Uses the timestamp field, which is assumed to be the first column.
// Requires "Edit after submit" option to be enabled in the corresponding form.

function showFormEdit() {
  function showFormEditHtml(link) {
    // As an HTML modal dialog
    SpreadsheetApp.getUi().showModalDialog(
      HtmlService.createHtmlOutput(
        '<a href="' + link + '">Click here to edit your response.</a>'
      ), 'Edit Form Response'
    );
  }
  
  function showFormEditMsg(link) {
    // As a message box
    Browser.msgBox(link);
  }
  
  var range = SpreadsheetApp.getActiveSheet().getSelection().getActiveRange(),
      form  = FormApp.openById('0123456789abcdefghijklmnopqrstuvwxyz-_');
  if (range.getHeight() != 1) return Browser.msgBox("Please select only one row!") && false;
  showFormEditHtml( // change the function name as needed!
    form.getResponses(new Date(
      SpreadsheetApp.getActiveSheet().getRange(range.getRow(), 1).getValue()
    ))[0].getEditResponseUrl()
  );
}
