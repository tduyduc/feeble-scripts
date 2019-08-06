// This is a custom function for use in Google Sheets (with auto-complete). It creates CSV output for use with Google Admin user bulk upload feature.
// Undefined values are not handled, assuming that all parameters are either present (as they are required fields in the CSV file) or absent (to conveniently generate the header).
// When this function is implemented in a spreadsheet's script editor, it can be invoked by simply typing the function in a cell, e.g. GENERATECSV().

/**
 * Generates CSV output for use with Google Admin bulk upload feature. Specifying no parameters returns the CSV header.
 *
 * @param {First} fname First name.
 * @param {Last} lname Last name.
 * @param {someone@domain.com} email Email address.
 * @param {password} pwd Password.
 * @param {/} org Organization unit path (/orgname).
 * @param {False} changepwd Change password at next sign-in (True or False).
 * @return The CSV output, or the CSV header if no parameters are specified.
 * @customfunction
 */
function GENERATECSV(fname, lname, email, pwd, org, changepwd) {
  if (!fname && !lname && !email && !pwd && !org && !changepwd) return (
    'First Name [Required],Last Name [Required],Email Address [Required],Password [Required],Org Unit Path [Required],Change Password at Next Sign-In'
  );
  return (''
    + String(fname)
    + ','
    + String(lname)
    + ','
    + String(email).toLowerCase()
    + ','
    + String(pwd)
    + ','
    + String(org)
    + ','
    + (('undefined' === typeof changepwd) ? 'False' : String(changepwd))
  );
}
