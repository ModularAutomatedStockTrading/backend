const {buildQueryString, fetchJSON} = require("./request")
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
    //console.log(`${API_URL}?${queryParams}`)
    return fetchJSON(`${API_URL}?${queryParams}`);
}

module.exports = fetchFromAPI;