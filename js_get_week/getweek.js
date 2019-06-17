// Returns the week containing the date, which starts on date index 0 and ends on date index 1
function getWeek(date) {
  var first = new Date(date), last = new Date(date);
  while (1 !== first.getDay()) { // Monday
    first.setDate(first.getDate() - 1);
  }
  first.setHours(0, 0, 0, 0);
  while (0 !== last.getDay()) { // Sunday
    last.setDate(last.getDate() + 1);
  }
  last.setHours(0, 0, 0, 0);
  return [first, last];
}
