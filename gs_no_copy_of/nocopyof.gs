// Remove "Copy of" prefix from file names in a Google Drive folder
function noCopyOf() {
  var files = DriveApp.getFolderById('0123456789abcdefghijklmnopqrstuvw').getFiles(), file;
  while (files.hasNext()) (file = files.next()).setName(file.getName().replace(/^Copy of /, ''));
}
