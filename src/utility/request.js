const fetch = require("node-fetch");

module.exports.buildQueryString = obj => {
    const res = [];
    let cnt = Object.keys(obj).length;
    for(const key in obj){
        res.push(key);
        res.push("=");
        res.push(obj[key]);
        if((--cnt) != 0)  res.push("&");
    }
    return res.join("");
}

module.exports.fetchJSON = async (url) => {
    return await(await fetch(url)).json();
}