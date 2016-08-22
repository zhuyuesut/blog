var line = 1;
code = code.replace(/^/gm, function() {
    return '<span class="line-number-position">&#x200b;<span class="line-number">' + line++ + '</span></span>';
});