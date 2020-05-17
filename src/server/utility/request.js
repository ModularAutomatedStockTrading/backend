const fetch = require("node-fetch");

// build query string to append to URL given an object, obj
const buildQueryString = obj => {
    const res = [];
    let cnt = Object.keys(obj).length;
    for(const key in obj){
        res.push(key);
        res.push("=");
        res.push(obj[key]);
        if((--cnt) != 0) res.push("&");
    }
    return res.join("");
}

// fetch JSON from url
const fetchJSON = async (url) => {
    return await(await fetch(url)).json();
}

module.exports = {
    fetchJSON,
    buildQueryString
}