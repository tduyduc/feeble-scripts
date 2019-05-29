// Rebuild data validations (e.g. drop-down lists) from Template

function rebuildDropDown() {
  try {
    var ss = SpreadsheetApp.getActiveSpreadsheet(), curr = ss.getActiveSheet(), templ = ss.getSheetByName("Template");
    if (curr == null || templ == null) return false;
    curr.getRange(
      1, 1, curr.getMaxRows(), curr.getMaxColumns()
    ).setDataValidations(
      templ.getRange(
        1, 1, curr.getMaxRows(), curr.getMaxColumns()
      ).getDataValidations()
    );
  } catch (err) {}
}
