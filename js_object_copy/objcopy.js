function objCopy(obj) {
	if (obj instanceof Function || !(obj instanceof Object)) return obj;
	var ret = obj instanceof Array ? [] : {};
	for (var i in obj) ret[i] = objCopy(obj[i]);
	return ret;
}
