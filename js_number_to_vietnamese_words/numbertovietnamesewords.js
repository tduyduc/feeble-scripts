// Convert an integer of arbitrary length to Vietnamese words, with a Boolean option to display as currency
function numberToVietnameseWords(number, currency) {
  var org = BigInt(number), n = BigInt(org), out = "", curr = "", llions = ['', 'nghìn ', 'triệu ', 'tỷ '], llion = 0;
  if (n < 0n) n = -n;
  if (n == 0n) return "không";
  while (true) {
    if (n % 1000n != 0n) {
      curr = "";
      switch ((n / 100n) % 10n) { // hundreds
        case 0n: if (n >= 1000n && n % 100n != 0n) curr = "không trăm "; break;
        case 1n: curr = "một trăm "; break;
        case 2n: curr = "hai trăm "; break;
        case 3n: curr = "ba trăm "; break;
        case 4n: curr = "bốn trăm "; break;
        case 5n: curr = "năm trăm "; break;
        case 6n: curr = "sáu trăm "; break;
        case 7n: curr = "bảy trăm "; break;
        case 8n: curr = "tám trăm "; break;
        case 9n: curr = "chín trăm "; break;
      }
      switch ((n / 10n) % 10n) { // tens
        case 0n: if (n % 10n != 0n && n >= 10n) curr += "lẻ "; break;
        case 1n: curr += "mười "; break;
        case 2n: curr += "hai mươi "; break;
        case 3n: curr += "ba mươi "; break;
        case 4n: curr += "bốn mươi "; break;
        case 5n: curr += "năm mươi "; break;
        case 6n: curr += "sáu mươi "; break;
        case 7n: curr += "bảy mươi "; break;
        case 8n: curr += "tám mươi "; break;
        case 9n: curr += "chín mươi "; break;
      }
      switch (n % 10n) { // ones
        case 1n:
          switch ((n / 10n) % 10n) {
            case 0n: case 1n: curr += "một "; break;
            default: curr += "mốt "; break;
          }
          break;
        case 2n: curr += "hai "; break;
        case 3n: curr += "ba "; break;
        case 4n: curr += "bốn "; break;
        case 5n: curr += ((n / 10n) % 10n == 0n) ? "năm " : "lăm "; break;
        case 6n: curr += "sáu "; break;
        case 7n: curr += "bảy "; break;
        case 8n: curr += "tám "; break;
        case 9n: curr += "chín "; break;
      }
      curr += llions[llion];
      out = curr + out;
    }
    llion++;
    n = n / 1000n;
    if (n == 0n) break;
    if (llions.length - 1 == llion) {
      out = numberToVietnameseWords(n) + ' ' + llions[llion] + out;
      break;
    }
  }
  if (currency) {
    out += " đồng";
    if (org % 1000n == 0n) out += " chẵn";
  }
  if (org < 0n) out = "âm " + out;
  return out.replace(/(^\s+|\s+$)/g, '').replace(/  /g, ' '); // remove leading, trailing, and redundant whitespaces
}
