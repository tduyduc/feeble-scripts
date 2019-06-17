// Calculate number of days between date1 and date2, excluding Saturdays and Sundays
// The function is not really efficient because of O(n) execution time
function getBusinessDaysBetween(date1, date2) {
  if (date1 > date2) return -getBusinessDaysBetween(date2, date1);
  var curr = new Date(date1), last = new Date(date2);
  curr.setHours(0, 0, 0, 0);
  last.setHours(0, 0, 0, 0);
  for (var result = 0; curr <= last; curr.setDate(curr.getDate() + 1)) {
    switch (curr.getDay()) {
      case 0: case 6: break;
      default: result++;
    }
  }
  return result;
}
