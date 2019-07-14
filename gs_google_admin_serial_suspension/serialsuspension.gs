// Suspends all accounts listed in a spreadsheet; requires user management privileges in Google Admin
function massacre() {
  var victims = SpreadsheetApp.openById('0123456789abcdefghijklmnopqrstuvw').getSheetByName('Account Check Results');
  victims = victims.getRange(2, 1, victims.getLastRow() - 1, 1).getValues();
  for (var i in victims)
    AdminDirectory.Users.update({suspended: true}, String(victims[i]).toLowerCase() + '@domain.com');
}
