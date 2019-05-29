function to12h(s) {
    var source = String(s),
        hour = source.replace(/:.*$/, ''),
        minute = source.replace(/^.*:/, '');
    return (
        (hour % 12 ? hour % 12 : 12) + ':' + minute + ' ' + (hour < 12 ? 'AM' : 'PM')
    );
}
