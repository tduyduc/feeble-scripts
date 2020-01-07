// Unlike your liked Facebook pages

// Before invoking this function, navigate to your likes list
// The URL should be in the form: facebook.com/<username>/likes

async function unlikePages() {
  const mouseoverEvent = new Event('mouseover');
  for (const element of document.getElementsByClassName('PageLikedButton')) {
    element.dispatchEvent(mouseoverEvent);
    while (!await new Promise(
      resolve => setTimeout(() => {
        let uiMenuInner = getUiMenuInner();
        if (uiMenuInner instanceof Object) {
          uiMenuInner.getElementsByTagName('a')[0].click();
          resolve(true);
        } else resolve(false);
      }, 50)
    )) {}
    while (!await new Promise(
      resolve => setTimeout(() => {
        resolve(!(getUiMenuInner() instanceof Object));
      }, 50)
    )) {}
    await new Promise(resolve => setTimeout(resolve, 500));
  }

  function getUiMenuInner() {
    return document.getElementsByClassName('uiMenuInner')[3];
  }
}
unlikePages();
