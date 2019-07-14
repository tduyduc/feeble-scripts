// Remove all diacritics in a string. This function removes Vietnamese accent marks.
function removeDiacritics(str) {
  str = str.toString();
  var out = "", len = str.length, id = -1,
      on_accent  = 'áàảãạăắằẳẵặâấầẩẫậÁÀẢÃẠĂẮẰẲẴẶÂẤẦẨẪẬđĐéèẻẽẹÉÈẺẼẸêếềểễệÊẾỀỂỄỆíìỉĩịÍÌỈĨỊóòỏõọÓÒỎÕỌôốồổỗộÔỐỒỔỖỘơớờởỡợƠỚỜỞỠỢúùủũụÚÙỦŨỤưứừửữựƯỨỪỬỮỰýỳỷỹỵÝỲỶỸỴ',
      off_accent = 'aaaaaaaaaaaaaaaaaAAAAAAAAAAAAAAAAAdDeeeeeEEEEEeeeeeeEEEEEEiiiiiIIIIIoooooOOOOOooooooOOOOOOooooooOOOOOOuuuuuUUUUUuuuuuuUUUUUUyyyyyYYYYY';
  for (var i = 0; i < len; i++) {
    id = on_accent.indexOf(str.charAt(i));
    out += (id == -1) ? str.charAt(i) : off_accent.charAt(id);
  }
  return out;
}
