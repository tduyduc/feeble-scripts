// Open the first audio tag encountered in a page, isolated in another tab to facilitate downloads.
window.open(
  document.getElementsByTagName('audio')[0].src
);
