// From different arrays, merges all objects with the same primary key
function mergeArraysOfObjects(primaryKey, ...arrays) {
  const concated = [].concat(...arrays);
  const result = [], traversed = [];

  for (let i = 0; i < concated.length; ++i) {
    if (traversed[i]) continue;
    traversed[i] = true;

    while (true) {
      const foundIndex = concated.findIndex((_item, itemIndex) =>
        (i !== itemIndex) &&
        !traversed[itemIndex] &&
        (concated[itemIndex][primaryKey] === concated[i][primaryKey])
      );
      if (-1 === foundIndex) {
        result.push(concated[i]);
        break;
      }

      traversed[foundIndex] = true;
      Object.assign(concated[i], concated[foundIndex]);
    }
  }
  return result;
}

const primaryKey = 'id',
  a = [{ id: 1, x: 2 }],
  b = [{ id: 1, y: 3 }, { id: 2, y: 5 }],
  c = [{ id: 1, z: 4 }, { id: 2, z: 6 }];

mergeArraysOfObjects(primaryKey, a, b, c);
// should return [{ id: 1, x: 2, y: 3, z: 4 }, { id: 2, y: 5, z: 6 }]
