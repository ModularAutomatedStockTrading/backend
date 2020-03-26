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
    return fetchJSON(`${API_URL}?${queryParams}`);
}

module.exports = fetchFromAPI;