/**
 * Performs an immutable object assignment.
 *
 * This function assists in assigning states in Redux.
 *
 * @param {object} originalObject
 * @param {(string | number)[]} path
 * @param {object} assignerObject
 * @returns {object}
 *
 * @example
 * const state = { a: 1, b: 2, c: [{ d: 1 }, { d: 2 }] };
 * immutableAssign(state, ['c', 0], { e: 2 }); // is equivalent to...
 * ({
 *   ...state,
 *   c: Object.assign(
 *     state.c.slice(),
 *     { 0: { ...state.c[0], e: 2 } }
 *   ),
 * })
 */
function immutableAssign(originalObject, path, assignerObject) {
  const result = shallowCopy(originalObject);
  let currentObject = result;
  for (const field of path) {
    currentObject[field] = shallowCopy(currentObject[field]);
    currentObject = currentObject[field];
  }
  Object.assign(currentObject, assignerObject);
  return result;

  function shallowCopy(object) {
    if (Array.isArray(object)) {
      return object.slice();
    }
    if (typeof object === 'object' && object) {
      return { ...object };
    }
    return object;
  }
}
