function range(start, end = undefined, step = 1) {
  step -= 0;
  if ('undefined' === typeof end) {
    end = start;
    start = 0;
  }
  for (var i = start - 0, len = end - 0, value = [],
    continuing = (i, len) => {
      if (!step) return false;
      return (step > 0) ? (i < len) : (i > len);
    }; continuing(i, len); i += step
  ) value.push(i);
  return value;
}
