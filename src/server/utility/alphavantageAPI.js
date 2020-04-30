const {buildQueryString, fetchJSON} = require("./request")
const Cache = require("src/server/middleware/cache")

const API_KEY = process.env.API_KEY;
const API_URL = "https://www.alphavantage.co/query";

const default_API_config = {
    datatype : "json",
    apikey : API_KEY
}

const fetchFromAPI = config => {
    const queryParams = buildQueryString({
        ...default_API_config,
        ...config
    });
    const url = `${API_URL}?${queryParams}`;
    return Cache.fetchExternal(url, () => fetchJSON(url));
}

module.exports = fetchFromAPI;