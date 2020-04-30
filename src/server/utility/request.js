const fetch = require("node-fetch");

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

const fetchJSON = async (url) => {
    console.log("fetching:", url)
    return await(await fetch(url)).json();
}

module.exports = {
    fetchJSON,
    buildQueryString
}