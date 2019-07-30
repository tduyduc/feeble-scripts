// Converts a string to an HTML string literal as escaped numeric character references.
// All characters are converted. CR (\r) is gracefully ignored. LF (\n) is distinctively handled.
function htmlEncode(s) {
  var r = '';
  for (var i = 0; i < s.length; i++) {
    r += ('\n' === s.charAt(i)) ? '<br />' : ('&#' + s.charCodeAt(i) + ';');
  }
  return r;
}
