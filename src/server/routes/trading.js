const express = require("express");
const {buildQueryString, fetchJSON} = require("utility/request")
const router = express.Router();

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

router.use("/trade", async (req, res) => {
    const config = {
        function : "TIME_SERIES_INTRADAY",
        symbol : "MSFT",
        interval : "1min"
    };
    const data = await fetchFromAPI(config);
    res.send(data);
})


module.exports = router;