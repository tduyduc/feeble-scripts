// Convert an integer to Vietnamese words, with a Boolean option to display as currency
function numberToVietnameseWords(number, currency) {
  var org = Math.floor(number), n = Math.abs(org), out = "", curr = "", llions = ['', 'nghìn ', 'triệu ', 'tỷ '], llion = 0;
  if (n == 0) return "không";
  while (n != 0) {
    if (n % 1000 != 0) {
      curr = "";
      switch (Math.floor(n / 100) % 10) { // hundreds
        case 0: if (n >= 1000 && Math.floor(n % 100) != 0) curr = "không trăm "; break;
        case 1: curr = "một trăm "; break;
        case 2: curr = "hai trăm "; break;
        case 3: curr = "ba trăm "; break;
        case 4: curr = "bốn trăm "; break;
        case 5: curr = "năm trăm "; break;
        case 6: curr = "sáu trăm "; break;
        case 7: curr = "bảy trăm "; break;
        case 8: curr = "tám trăm "; break;
        case 9: curr = "chín trăm "; break;
      }
      switch (Math.floor(n / 10) % 10) { // tens
        case 0: if (n % 10 != 0 && n >= 10) curr += "lẻ "; break;
        case 1: curr += "mười "; break;
        case 2: curr += "hai mươi "; break;
        case 3: curr += "ba mươi "; break;
        case 4: curr += "bốn mươi "; break;
        case 5: curr += "năm mươi "; break;
        case 6: curr += "sáu mươi "; break;
        case 7: curr += "bảy mươi "; break;
        case 8: curr += "tám mươi "; break;
        case 9: curr += "chín mươi "; break;
      }
      switch (n % 10) { // ones
        case 1:
          switch (Math.floor(n / 10) % 10) {
            case 0: case 1: curr += "một "; break;
            default: curr += "mốt "; break;
          }
          break;
        case 2: curr += "hai "; break;
        case 3: curr += "ba "; break;
        case 4: curr += "bốn "; break;
        case 5: curr += (Math.floor(n / 10) % 10 == 0) ? "năm " : "lăm "; break;
        case 6: curr += "sáu "; break;
        case 7: curr += "bảy "; break;
        case 8: curr += "tám "; break;
        case 9: curr += "chín "; break;
      }
      curr += llions[llion];
      out = curr + out;
    }
    llion++;
    n = Math.floor(n / 1000);
    if (llions.length - 1 == llion) {
      out = numberToVietnameseWords(Math.floor(n), false) + ' ' + llions[llion] + out;
      break;
    }
  }
  if (currency) {
    out += " đồng";
    if (org % 1000 == 0) out += " chẵn";
  }
  if (org < 0) out = "âm " + out;
  return out.replace(/(^\s+|\s+$)/g, '').replace(/  /g, ' '); // remove leading & trailing whitespaces
}
