// Set description for all Google Forms files in a Drive folder
function setFormDescriptions() {
  var files = DriveApp.getFolderById('0123456789abcdefghijklmnopqrstuvw').getFilesByType('application/vnd.google-apps.form');
  while (files.hasNext()) {
    FormApp.openById(files.next().getId()).setDescription('This form generates and collects subject teacher comments for Semester Two reports.');
  }
}
