const {buildQueryString, fetchJSON} = require("./request")
const Cache = require("src/server/middleware/cache")

const API_KEY = process.env.API_KEY;
const API_URL = "https://www.alphavantage.co/query";

const default_API_config = {
    datatype : "json",
    apikey : API_KEY
}

// gets API URL based on config object
const getURL = config => {
    const queryParams = buildQueryString({
        ...default_API_config,
        ...config
    });
    const url = `${API_URL}?${queryParams}`;
    return url;
}

// fetches JSON data from API
const fetchFromAPI = input => {
    const url = typeof input == "object" ? getURL(input) : input;
    return Cache.fetchExternal(
        url,
        () => {
            console.info("lambda", url)
            return fetchJSON(url)
        }
    );
}

module.exports = {
    fetchFromAPI,
    getURL
};