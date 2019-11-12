/*
  Emulates the safe navigation operator.
  This function accesses object member or array index sequentially and stops the evaluation chain when the next member in the chain is unavailable.

  Example:
    * safeNavigate(['123'], 0, 2) returns '3'
    * safeNavigate({ a: 1 }, 'a') returns 1
    * safeNavigate({ a: 1 }, 'a', 'b', 'c') returns undefined

  See also: https://en.wikipedia.org/wiki/Safe_navigation_operator
*/

function safeNavigate(obj, ...propertyChain) {
  let current = obj;
  try {
    for (property of propertyChain) current = current[property];
  } catch (error) { return undefined; }
  return current;
}
